#!/usr/bin/make -f
# Makefile for WSTD Plugins #
# ---------------------------- #
# Created by dreamer
#

include dpf/Makefile.base.mk

all: plugins gen

PREFIX  ?= /usr/local
DESTDIR ?=

plugins:
	# arp-delay-env
	$(MAKE) all -C plugins/arp-delay-env

gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator

clean:
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/arp-delay-env

install:
	install -d $(DESTDIR)$(PREFIX)/lib/lv2/
	install -d $(DESTDIR)$(PREFIX)/lib/vst/
	install -d $(DESTDIR)$(PREFIX)/bin/

	cp bin/*-vst.*    $(DESTDIR)$(PREFIX)/lib/vst/
	cp -r bin/*.lv2   $(DESTDIR)$(PREFIX)/lib/lv2/

ifeq ($(HAVE_JACK),true)
	cp -r bin/arp-delay-env  $(DESTDIR)$(PREFIX)/bin/
endif

.PHONY: plugins
