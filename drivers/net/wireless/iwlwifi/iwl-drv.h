/******************************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may do so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2012 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * Contact Information:
 *  Intel Linux Wireless <ilw@linux.intel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * BSD LICENSE
 *
 * Copyright(c) 2005 - 2012 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef __iwl_drv_h__
#define __iwl_drv_h__

#include "iwl-shared.h"

/**
 * DOC: Driver system flows - drv component
 *
 * This component implements the system flows such as bus enumeration, bus
 * removal. Bus dependent parts of system flows (such as iwl_pci_probe) are in
 * bus specific files (transport files). This is the code that is common among
 * different buses.
 *
 * This component is also in charge of managing the several implementations of
 * the wifi flows: it will allow to have several fw API implementation. These
 * different implementations will differ in the way they implement mac80211's
 * handlers too.

 * The init flow wrt to the drv component looks like this:
 * 1) The bus specific component is called from module_init
 * 2) The bus specific component registers the bus driver
 * 3) The bus driver calls the probe function
 * 4) The bus specific component configures the bus
 * 5) The bus specific component calls to the drv bus agnostic part
 *    (iwl_drv_start)
 * 6) iwl_drv_start fetches the fw ASYNC, iwl_ucode_callback
 * 7) iwl_ucode_callback parses the fw file
 * 8) iwl_ucode_callback starts the wifi implementation to matches the fw
 */

/**
 * iwl_drv_start - start the drv
 *
 * @shrd: the shrd area
 * @trans_ops: the ops of the transport
 * @cfg: device specific constants / virtual functions
 *
 * TODO: review the parameters given to this function
 *
 * starts the driver: fetches the firmware. This should be called by bus
 * specific system flows implementations. For example, the bus specific probe
 * function should do bus related operations only, and then call to this
 * function.
 */
int iwl_drv_start(struct iwl_shared *shrd,
		  struct iwl_trans *trans, const struct iwl_cfg *cfg);

/**
 * iwl_drv_stop - stop the drv
 *
 * @shrd: the shrd area
 *
 * TODO: review the parameters given to this function
 *
 * Stop the driver. This should be called by bus specific system flows
 * implementations. For example, the bus specific remove function should first
 * call this function and then do the bus related operations only.
 */
void iwl_drv_stop(struct iwl_shared *shrd);

#endif /* __iwl_drv_h__ */
