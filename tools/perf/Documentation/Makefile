OUTPUT := ./
ifeq ("$(origin O)", "command line")
  ifneq ($(O),)
	OUTPUT := $(O)/
  endif
endif

MAN1_TXT= \
	$(filter-out $(addsuffix .txt, $(ARTICLES) $(SP_ARTICLES)), \
		$(wildcard perf-*.txt)) \
	perf.txt
MAN5_TXT=
MAN7_TXT=

MAN_TXT = $(MAN1_TXT) $(MAN5_TXT) $(MAN7_TXT)
_MAN_XML=$(patsubst %.txt,%.xml,$(MAN_TXT))
_MAN_HTML=$(patsubst %.txt,%.html,$(MAN_TXT))

MAN_XML=$(addprefix $(OUTPUT),$(_MAN_XML))
MAN_HTML=$(addprefix $(OUTPUT),$(_MAN_HTML))

ARTICLES =
# with their own formatting rules.
SP_ARTICLES =
API_DOCS = $(patsubst %.txt,%,$(filter-out technical/api-index-skel.txt technical/api-index.txt, $(wildcard technical/api-*.txt)))
SP_ARTICLES += $(API_DOCS)
SP_ARTICLES += technical/api-index

_DOC_HTML = $(_MAN_HTML)
_DOC_HTML+=$(patsubst %,%.html,$(ARTICLES) $(SP_ARTICLES))
DOC_HTML=$(addprefix $(OUTPUT),$(_DOC_HTML))

_DOC_MAN1=$(patsubst %.txt,%.1,$(MAN1_TXT))
_DOC_MAN5=$(patsubst %.txt,%.5,$(MAN5_TXT))
_DOC_MAN7=$(patsubst %.txt,%.7,$(MAN7_TXT))

DOC_MAN1=$(addprefix $(OUTPUT),$(_DOC_MAN1))
DOC_MAN5=$(addprefix $(OUTPUT),$(_DOC_MAN5))
DOC_MAN7=$(addprefix $(OUTPUT),$(_DOC_MAN7))

# Make the path relative to DESTDIR, not prefix
ifndef DESTDIR
prefix?=$(HOME)
endif
bindir?=$(prefix)/bin
htmldir?=$(prefix)/share/doc/perf-doc
pdfdir?=$(prefix)/share/doc/perf-doc
mandir?=$(prefix)/share/man
man1dir=$(mandir)/man1
man5dir=$(mandir)/man5
man7dir=$(mandir)/man7

ASCIIDOC=asciidoc
ASCIIDOC_EXTRA = --unsafe
MANPAGE_XSL = manpage-normal.xsl
XMLTO_EXTRA =
INSTALL?=install
RM ?= rm -f
DOC_REF = origin/man
HTML_REF = origin/html

infodir?=$(prefix)/share/info
MAKEINFO=makeinfo
INSTALL_INFO=install-info
DOCBOOK2X_TEXI=docbook2x-texi
DBLATEX=dblatex
ifndef PERL_PATH
	PERL_PATH = /usr/bin/perl
endif

-include ../config.mak.autogen
-include ../config.mak

#
# For asciidoc ...
#	-7.1.2,	no extra settings are needed.
#	8.0-,	set ASCIIDOC8.
#

#
# For docbook-xsl ...
#	-1.68.1,	set ASCIIDOC_NO_ROFF? (based on changelog from 1.73.0)
#	1.69.0,		no extra settings are needed?
#	1.69.1-1.71.0,	set DOCBOOK_SUPPRESS_SP?
#	1.71.1,		no extra settings are needed?
#	1.72.0,		set DOCBOOK_XSL_172.
#	1.73.0-,	set ASCIIDOC_NO_ROFF
#

#
# If you had been using DOCBOOK_XSL_172 in an attempt to get rid
# of 'the ".ft C" problem' in your generated manpages, and you
# instead ended up with weird characters around callouts, try
# using ASCIIDOC_NO_ROFF instead (it works fine with ASCIIDOC8).
#

ifdef ASCIIDOC8
ASCIIDOC_EXTRA += -a asciidoc7compatible
endif
ifdef DOCBOOK_XSL_172
ASCIIDOC_EXTRA += -a perf-asciidoc-no-roff
MANPAGE_XSL = manpage-1.72.xsl
else
	ifdef ASCIIDOC_NO_ROFF
	# docbook-xsl after 1.72 needs the regular XSL, but will not
	# pass-thru raw roff codes from asciidoc.conf, so turn them off.
	ASCIIDOC_EXTRA += -a perf-asciidoc-no-roff
	endif
endif
ifdef MAN_BOLD_LITERAL
XMLTO_EXTRA += -m manpage-bold-literal.xsl
endif
ifdef DOCBOOK_SUPPRESS_SP
XMLTO_EXTRA += -m manpage-suppress-sp.xsl
endif

SHELL_PATH ?= $(SHELL)
# Shell quote;
SHELL_PATH_SQ = $(subst ','\'',$(SHELL_PATH))

#
# Please note that there is a minor bug in asciidoc.
# The version after 6.0.3 _will_ include the patch found here:
#   http://marc.theaimsgroup.com/?l=perf&m=111558757202243&w=2
#
# Until that version is released you may have to apply the patch
# yourself - yes, all 6 characters of it!
#

QUIET_SUBDIR0  = +$(MAKE) -C # space to separate -C and subdir
QUIET_SUBDIR1  =

ifneq ($(findstring $(MAKEFLAGS),w),w)
PRINT_DIR = --no-print-directory
else # "make -w"
NO_SUBDIR = :
endif

ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
	QUIET_ASCIIDOC	= @echo '   ' ASCIIDOC $@;
	QUIET_XMLTO	= @echo '   ' XMLTO $@;
	QUIET_DB2TEXI	= @echo '   ' DB2TEXI $@;
	QUIET_MAKEINFO	= @echo '   ' MAKEINFO $@;
	QUIET_DBLATEX	= @echo '   ' DBLATEX $@;
	QUIET_XSLTPROC	= @echo '   ' XSLTPROC $@;
	QUIET_GEN	= @echo '   ' GEN $@;
	QUIET_STDERR	= 2> /dev/null
	QUIET_SUBDIR0	= +@subdir=
	QUIET_SUBDIR1	= ;$(NO_SUBDIR) echo '   ' SUBDIR $$subdir; \
			  $(MAKE) $(PRINT_DIR) -C $$subdir
	export V
endif
endif

all: html man

html: $(DOC_HTML)

$(DOC_HTML) $(DOC_MAN1) $(DOC_MAN5) $(DOC_MAN7): asciidoc.conf

man: man1 man5 man7
man1: $(DOC_MAN1)
man5: $(DOC_MAN5)
man7: $(DOC_MAN7)

info: $(OUTPUT)perf.info $(OUTPUT)perfman.info

pdf: $(OUTPUT)user-manual.pdf

install: install-man

install-man: man
	$(INSTALL) -d -m 755 $(DESTDIR)$(man1dir)
#	$(INSTALL) -d -m 755 $(DESTDIR)$(man5dir)
#	$(INSTALL) -d -m 755 $(DESTDIR)$(man7dir)
	$(INSTALL) -m 644 $(DOC_MAN1) $(DESTDIR)$(man1dir)
#	$(INSTALL) -m 644 $(DOC_MAN5) $(DESTDIR)$(man5dir)
#	$(INSTALL) -m 644 $(DOC_MAN7) $(DESTDIR)$(man7dir)

install-info: info
	$(INSTALL) -d -m 755 $(DESTDIR)$(infodir)
	$(INSTALL) -m 644 $(OUTPUT)perf.info $(OUTPUT)perfman.info $(DESTDIR)$(infodir)
	if test -r $(DESTDIR)$(infodir)/dir; then \
	  $(INSTALL_INFO) --info-dir=$(DESTDIR)$(infodir) perf.info ;\
	  $(INSTALL_INFO) --info-dir=$(DESTDIR)$(infodir) perfman.info ;\
	else \
	  echo "No directory found in $(DESTDIR)$(infodir)" >&2 ; \
	fi

install-pdf: pdf
	$(INSTALL) -d -m 755 $(DESTDIR)$(pdfdir)
	$(INSTALL) -m 644 $(OUTPUT)user-manual.pdf $(DESTDIR)$(pdfdir)

#install-html: html
#	'$(SHELL_PATH_SQ)' ./install-webdoc.sh $(DESTDIR)$(htmldir)

../PERF-VERSION-FILE: .FORCE-PERF-VERSION-FILE
	$(QUIET_SUBDIR0)../ $(QUIET_SUBDIR1) PERF-VERSION-FILE

-include ../PERF-VERSION-FILE

#
# Determine "include::" file references in asciidoc files.
#
$(OUTPUT)doc.dep : $(wildcard *.txt) build-docdep.perl
	$(QUIET_GEN)$(RM) $@+ $@ && \
	$(PERL_PATH) ./build-docdep.perl >$@+ $(QUIET_STDERR) && \
	mv $@+ $@

-include $(OUPTUT)doc.dep

_cmds_txt = cmds-ancillaryinterrogators.txt \
	cmds-ancillarymanipulators.txt \
	cmds-mainporcelain.txt \
	cmds-plumbinginterrogators.txt \
	cmds-plumbingmanipulators.txt \
	cmds-synchingrepositories.txt \
	cmds-synchelpers.txt \
	cmds-purehelpers.txt \
	cmds-foreignscminterface.txt
cmds_txt=$(addprefix $(OUTPUT),$(_cmds_txt))

$(cmds_txt): $(OUTPUT)cmd-list.made

$(OUTPUT)cmd-list.made: cmd-list.perl ../command-list.txt $(MAN1_TXT)
	$(QUIET_GEN)$(RM) $@ && \
	$(PERL_PATH) ./cmd-list.perl ../command-list.txt $(QUIET_STDERR) && \
	date >$@

clean:
	$(RM) $(MAN_XML) $(addsuffix +,$(MAN_XML))
	$(RM) $(MAN_HTML) $(addsuffix +,$(MAN_HTML))
	$(RM) $(DOC_HTML) $(DOC_MAN1) $(DOC_MAN5) $(DOC_MAN7)
	$(RM) $(OUTPUT)*.texi $(OUTPUT)*.texi+ $(OUTPUT)*.texi++
	$(RM) $(OUTPUT)perf.info $(OUTPUT)perfman.info
	$(RM) $(OUTPUT)howto-index.txt $(OUTPUT)howto/*.html $(OUTPUT)doc.dep
	$(RM) $(OUTPUT)technical/api-*.html $(OUTPUT)technical/api-index.txt
	$(RM) $(cmds_txt) $(OUTPUT)*.made

$(MAN_HTML): $(OUTPUT)%.html : %.txt
	$(QUIET_ASCIIDOC)$(RM) $@+ $@ && \
	$(ASCIIDOC) -b xhtml11 -d manpage -f asciidoc.conf \
		$(ASCIIDOC_EXTRA) -aperf_version=$(PERF_VERSION) -o $@+ $< && \
	mv $@+ $@

$(OUTPUT)%.1 $(OUTPUT)%.5 $(OUTPUT)%.7 : $(OUTPUT)%.xml
	$(QUIET_XMLTO)$(RM) $@ && \
	xmlto -o $(OUTPUT) -m $(MANPAGE_XSL) $(XMLTO_EXTRA) man $<

$(OUTPUT)%.xml : %.txt
	$(QUIET_ASCIIDOC)$(RM) $@+ $@ && \
	$(ASCIIDOC) -b docbook -d manpage -f asciidoc.conf \
		$(ASCIIDOC_EXTRA) -aperf_version=$(PERF_VERSION) -o $@+ $< && \
	mv $@+ $@

XSLT = docbook.xsl
XSLTOPTS = --xinclude --stringparam html.stylesheet docbook-xsl.css

$(OUTPUT)user-manual.html: $(OUTPUT)user-manual.xml
	$(QUIET_XSLTPROC)xsltproc $(XSLTOPTS) -o $@ $(XSLT) $<

$(OUTPUT)perf.info: $(OUTPUT)user-manual.texi
	$(QUIET_MAKEINFO)$(MAKEINFO) --no-split -o $@ $(OUTPUT)user-manual.texi

$(OUTPUT)user-manual.texi: $(OUTPUT)user-manual.xml
	$(QUIET_DB2TEXI)$(RM) $@+ $@ && \
	$(DOCBOOK2X_TEXI) $(OUTPUT)user-manual.xml --encoding=UTF-8 --to-stdout >$@++ && \
	$(PERL_PATH) fix-texi.perl <$@++ >$@+ && \
	rm $@++ && \
	mv $@+ $@

$(OUTPUT)user-manual.pdf: $(OUTPUT)user-manual.xml
	$(QUIET_DBLATEX)$(RM) $@+ $@ && \
	$(DBLATEX) -o $@+ -p /etc/asciidoc/dblatex/asciidoc-dblatex.xsl -s /etc/asciidoc/dblatex/asciidoc-dblatex.sty $< && \
	mv $@+ $@

$(OUTPUT)perfman.texi: $(MAN_XML) cat-texi.perl
	$(QUIET_DB2TEXI)$(RM) $@+ $@ && \
	($(foreach xml,$(MAN_XML),$(DOCBOOK2X_TEXI) --encoding=UTF-8 \
		--to-stdout $(xml) &&) true) > $@++ && \
	$(PERL_PATH) cat-texi.perl $@ <$@++ >$@+ && \
	rm $@++ && \
	mv $@+ $@

$(OUTPUT)perfman.info: $(OUTPUT)perfman.texi
	$(QUIET_MAKEINFO)$(MAKEINFO) --no-split --no-validate $*.texi

$(patsubst %.txt,%.texi,$(MAN_TXT)): %.texi : %.xml
	$(QUIET_DB2TEXI)$(RM) $@+ $@ && \
	$(DOCBOOK2X_TEXI) --to-stdout $*.xml >$@+ && \
	mv $@+ $@

howto-index.txt: howto-index.sh $(wildcard howto/*.txt)
	$(QUIET_GEN)$(RM) $@+ $@ && \
	'$(SHELL_PATH_SQ)' ./howto-index.sh $(wildcard howto/*.txt) >$@+ && \
	mv $@+ $@

$(patsubst %,%.html,$(ARTICLES)) : %.html : %.txt
	$(QUIET_ASCIIDOC)$(ASCIIDOC) -b xhtml11 $*.txt

WEBDOC_DEST = /pub/software/tools/perf/docs

$(patsubst %.txt,%.html,$(wildcard howto/*.txt)): %.html : %.txt
	$(QUIET_ASCIIDOC)$(RM) $@+ $@ && \
	sed -e '1,/^$$/d' $< | $(ASCIIDOC) -b xhtml11 - >$@+ && \
	mv $@+ $@

# UNIMPLEMENTED
#install-webdoc : html
#	'$(SHELL_PATH_SQ)' ./install-webdoc.sh $(WEBDOC_DEST)

# quick-install: quick-install-man

# quick-install-man:
#	'$(SHELL_PATH_SQ)' ./install-doc-quick.sh $(DOC_REF) $(DESTDIR)$(mandir)

#quick-install-html:
#	'$(SHELL_PATH_SQ)' ./install-doc-quick.sh $(HTML_REF) $(DESTDIR)$(htmldir)

.PHONY: .FORCE-PERF-VERSION-FILE
