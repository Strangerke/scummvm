MODULE := engines/robin

MODULE_OBJS = \
  console.o \
  detection.o \
  robin.o \
  script.o \
  sound.o

# This module can be built as a plugin
ifdef BUILD_PLUGINS
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
