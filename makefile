TARGET = eboot
OBJS = eboot.o
OBJS += kernel\kernel.o

INCDIR = inc_lib
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS) -c

LIBDIR = inc_lib
LIBS = -lpspreg
LDFLAGS = -L.

PSP_FW_VERSION = 570
PSP_FW_VERSION_SFO = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSPgo Fake-Pair Tool v0.4 by Yoti
#PSP_EBOOT_ICON = 

#ENCRYPT = 1
BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
