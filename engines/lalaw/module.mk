MODULE := engines/lalaw

MODULE_OBJS := \
	debugger.o \
	detection.o \
	lalaw.o \
	lalaw_game.o

# This module can be built as a plugin
ifeq ($(ENABLE_LALAW), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
