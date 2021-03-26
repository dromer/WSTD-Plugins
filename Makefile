#!/usr/bin/make -f
# Makefile for WSTD Plugins #
# ---------------------------- #
# Created by dreamer
#

include dpf/Makefile.base.mk

all: plugins gen

PREFIX  ?= /usr/local
DESTDIR ?=

ifneq ($(CROSS_COMPILING),true)
CAN_GENERATE_TTL = true
else ifneq ($(EXE_WRAPPER),)
CAN_GENERATE_TTL = true
endif

plugins:
	# arp-delay-env
	$(MAKE) all -C plugins/arp-delay-env

gen: plugins dpf/utils/lv2_ttl_generator
ifeq ($(CAN_GENERATE_TTL),true)
	@$(CURDIR)/dpf/utils/generate-ttl.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator

.PHONY: plugins
