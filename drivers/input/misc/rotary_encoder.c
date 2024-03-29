/*
 * rotary_encoder.c
 *
 * (c) 2009 Daniel Mack <daniel@caiaq.de>
 * Copyright (C) 2011 Johan Hovold <jhovold@gmail.com>
 *
 * state machine code inspired by code from Tim Ruetz
 *
 * A generic driver for rotary encoders connected to GPIO lines.
 * See file:Documentation/input/rotary-encoder.txt for more information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/rotary_encoder.h>
#include <linux/slab.h>

#define DRV_NAME "rotary-encoder"

struct rotary_encoder {
	struct input_dev *input;
	struct rotary_encoder_platform_data *pdata;

	unsigned int axis;
	unsigned int pos;

	unsigned int irq_a;
	unsigned int irq_b;

	bool armed;
	unsigned char dir;	/* 0 - clockwise, 1 - CCW */

	char last_stable;
};

static int rotary_encoder_get_state(struct rotary_encoder_platform_data *pdata)
{
	int a = !!gpio_get_value(pdata->gpio_a);
	int b = !!gpio_get_value(pdata->gpio_b);

	a ^= pdata->inverted_a;
	b ^= pdata->inverted_b;

	return ((a << 1) | b);
}

static void rotary_encoder_report_event(struct rotary_encoder *encoder)
{
	struct rotary_encoder_platform_data *pdata = encoder->pdata;

	if (pdata->relative_axis) {
		input_report_rel(encoder->input,
				 pdata->axis, encoder->dir ? -1 : 1);
	} else {
		unsigned int pos = encoder->pos;

		if (encoder->dir) {
			/* turning counter-clockwise */
			if (pdata->rollover)
				pos += pdata->steps;
			if (pos)
				pos--;
		} else {
			/* turning clockwise */
			if (pdata->rollover || pos < pdata->steps)
				pos++;
		}

		if (pdata->rollover)
			pos %= pdata->steps;

		encoder->pos = pos;
		input_report_abs(encoder->input, pdata->axis, encoder->pos);
	}

	input_sync(encoder->input);
}

static irqreturn_t rotary_encoder_irq(int irq, void *dev_id)
{
	struct rotary_encoder *encoder = dev_id;
	int state;

	state = rotary_encoder_get_state(encoder->pdata);

	switch (state) {
	case 0x0:
		if (encoder->armed) {
			rotary_encoder_report_event(encoder);
			encoder->armed = false;
		}
		break;

	case 0x1:
	case 0x2:
		if (encoder->armed)
			encoder->dir = state - 1;
		break;

	case 0x3:
		encoder->armed = true;
		break;
	}

	return IRQ_HANDLED;
}

static irqreturn_t rotary_encoder_half_period_irq(int irq, void *dev_id)
{
	struct rotary_encoder *encoder = dev_id;
	int state;

	state = rotary_encoder_get_state(encoder->pdata);

	switch (state) {
	case 0x00:
	case 0x03:
		if (state != encoder->last_stable) {
			rotary_encoder_report_event(encoder);
			encoder->last_stable = state;
		}
		break;

	case 0x01:
	case 0x02:
		encoder->dir = (encoder->last_stable + state) & 0x01;
		break;
	}

	return IRQ_HANDLED;
}

static int __devinit rotary_encoder_probe(struct platform_device *pdev)
{
	struct rotary_encoder_platform_data *pdata = pdev->dev.platform_data;
	struct rotary_encoder *encoder;
	struct input_dev *input;
	irq_handler_t handler;
	int err;

	if (!pdata) {
		dev_err(&pdev->dev, "missing platform data\n");
		return -ENOENT;
	}

	encoder = kzalloc(sizeof(struct rotary_encoder), GFP_KERNEL);
	input = input_allocate_device();
	if (!encoder || !input) {
		dev_err(&pdev->dev, "failed to allocate memory for device\n");
		err = -ENOMEM;
		goto exit_free_mem;
	}

	encoder->input = input;
	encoder->pdata = pdata;
	encoder->irq_a = gpio_to_irq(pdata->gpio_a);
	encoder->irq_b = gpio_to_irq(pdata->gpio_b);

	/* create and register the input driver */
	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;

	if (pdata->relative_axis) {
		input->evbit[0] = BIT_MASK(EV_REL);
		input->relbit[0] = BIT_MASK(pdata->axis);
	} else {
		input->evbit[0] = BIT_MASK(EV_ABS);
		input_set_abs_params(encoder->input,
				     pdata->axis, 0, pdata->steps, 0, 1);
	}

	err = input_register_device(input);
	if (err) {
		dev_err(&pdev->dev, "failed to register input device\n");
		goto exit_free_mem;
	}

	/* request the GPIOs */
	err = gpio_request(pdata->gpio_a, DRV_NAME);
	if (err) {
		dev_err(&pdev->dev, "unable to request GPIO %d\n",
			pdata->gpio_a);
		goto exit_unregister_input;
	}

	err = gpio_direction_input(pdata->gpio_a);
	if (err) {
		dev_err(&pdev->dev, "unable to set GPIO %d for input\n",
			pdata->gpio_a);
		goto exit_unregister_input;
	}

	err = gpio_request(pdata->gpio_b, DRV_NAME);
	if (err) {
		dev_err(&pdev->dev, "unable to request GPIO %d\n",
			pdata->gpio_b);
		goto exit_free_gpio_a;
	}

	err = gpio_direction_input(pdata->gpio_b);
	if (err) {
		dev_err(&pdev->dev, "unable to set GPIO %d for input\n",
			pdata->gpio_b);
		goto exit_free_gpio_a;
	}

	/* request the IRQs */
	if (pdata->half_period) {
		handler = &rotary_encoder_half_period_irq;
		encoder->last_stable = rotary_encoder_get_state(pdata);
	} else {
		handler = &rotary_encoder_irq;
	}

	err = request_irq(encoder->irq_a, handler,
			  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			  DRV_NAME, encoder);
	if (err) {
		dev_err(&pdev->dev, "unable to request IRQ %d\n",
			encoder->irq_a);
		goto exit_free_gpio_b;
	}

	err = request_irq(encoder->irq_b, handler,
			  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			  DRV_NAME, encoder);
	if (err) {
		dev_err(&pdev->dev, "unable to request IRQ %d\n",
			encoder->irq_b);
		goto exit_free_irq_a;
	}

	platform_set_drvdata(pdev, encoder);

	return 0;

exit_free_irq_a:
	free_irq(encoder->irq_a, encoder);
exit_free_gpio_b:
	gpio_free(pdata->gpio_b);
exit_free_gpio_a:
	gpio_free(pdata->gpio_a);
exit_unregister_input:
	input_unregister_device(input);
	input = NULL; /* so we don't try to free it */
exit_free_mem:
	input_free_device(input);
	kfree(encoder);
	return err;
}

static int __devexit rotary_encoder_remove(struct platform_device *pdev)
{
	struct rotary_encoder *encoder = platform_get_drvdata(pdev);
	struct rotary_encoder_platform_data *pdata = pdev->dev.platform_data;

	free_irq(encoder->irq_a, encoder);
	free_irq(encoder->irq_b, encoder);
	gpio_free(pdata->gpio_a);
	gpio_free(pdata->gpio_b);
	input_unregister_device(encoder->input);
	platform_set_drvdata(pdev, NULL);
	kfree(encoder);

	return 0;
}

static struct platform_driver rotary_encoder_driver = {
	.probe		= rotary_encoder_probe,
	.remove		= __devexit_p(rotary_encoder_remove),
	.driver		= {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
	}
};
module_platform_driver(rotary_encoder_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DESCRIPTION("GPIO rotary encoder driver");
MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>, Johan Hovold");
MODULE_LICENSE("GPL v2");
