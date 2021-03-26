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

.PHONY: plugins
