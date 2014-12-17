#------------------------------------------------------------------------------
# MAEVARM M4 STM32F373
# version: 1.0
# date: March 25, 2013
# author: Neel Shah (neels@seas.upenn.edu)
# description: Makefile for compilation of main code
#			   Auto detection of OS, tested with OSX, Ubuntu and Windows
#			   Auto find and addition of source files for compilation
#			   Multi Thread compilation by default for faster compilation
#
# edited: Chao Liu (chao.liu0307@gmail.com)
# date: 8/06/2013
# Added support for assembly code.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# --> DON'T EDIT THIS FILE <--  
#------------------------------------------------------------------------------

MAKEFLAGS = -j --no-print-directory

PROJNAME  = main
BUILDDIR  = obj
INCDIR    = inc
LIBDIR    = lib
SOURCEDIR = src

ARMDIR   = arm
CPALDIR  = cpal
DSPDIR   = dsp
STDIR    = st
USBDIR   = usb

ifeq ($(OS),Windows_NT)
	UNAME := Windows
	SHELL=c:/windows/system32/cmd.exe
else
    UNAME := $(shell uname -s)
endif

ARCH = arm-none-eabi
CC = $(ARCH)-gcc
LD = $(ARCH)-ld
AS = $(ARCH)-as
SZ = $(ARCH)-size
OBJCPY = $(ARCH)-objcopy
OBJDMP = $(ARCH)-objdump

LDSCRIPT = $(LIBDIR)/$(STDIR)/STM32_FLASH.ld
STARTUP  = $(LIBDIR)/$(STDIR)/startup_stm32f37x.s 

CFLAGS  = -g -Os -std=c99
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -ffunction-sections -fdata-sections -nostartfiles
CFLAGS += -specs=nano.specs
CFLAGS += -I$(INCDIR) -I$(LIBDIR)/$(ARMDIR) -I$(LIBDIR)/$(CPALDIR)/$(INCDIR)
CFLAGS += -I$(LIBDIR)/$(STDIR)/$(INCDIR) -I$(LIBDIR)/$(USBDIR)/$(INCDIR)
CFLAGS += -DARM_MATH_CM4 -D'__FPU_PRESENT=1' -DM4 -DM4_WHITE
CFLAGS += -Wa,-mimplicit-it=thumb
#CFLAGS += -DUSE_STDPERIPH_DRIVER
#CFLAGS += -mthumb-interwork

LDFLAGS  = $(CFLAGS)
LDFLAGS += --static -Wl,--gc-sections
LDFLAGS += -Wl,-Map,$(BUILDDIR)/$(PROJNAME).map
LDFLAGS += -nostartfiles -T$(LDSCRIPT)

AFLAGS  = -mlittle-endian -mthumb -mcpu=cortex-m4 
ODFLAGS	= -x --syms
CPFLAGS = --output-target=binary

_SRCS = $(wildcard $(SOURCEDIR)/*.c)
_SRCS += $(wildcard *.c)
SRCS = $(notdir $(_SRCS))
SRCS += startup_stm32f37x.s

_OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))
OBJS = $(patsubst %.s,$(BUILDDIR)/%.o,$(_OBJS))

ifeq ($(UNAME),Windows)
_OBJSW = $(patsubst %.c,%.o,$(SRCS))
OBJSW = $(patsubst %.s,%.o,$(_OBJSW))
endif
#------------------------------------------------------------------------------

.PHONY: $(LIBDIR)/$(BUILDDIR)/libstm32f37x.a all clean disassemble flash cleanlib run proj

all: proj
ifeq ($(UNAME),Windows)
	@$(SZ) $(BUILDDIR)/$(PROJNAME).elf
else	
	@$(SZ) $(BUILDDIR)/$(PROJNAME).elf | tail -n 1 | awk '{print "Flash:\t", $$1+$$2, "\t[",($$1+$$2)*100/(256*1024),"% ]", "\nRAM:\t", $$2+$$3, "\t[",($$2+$$3)*100/(32*1024),"% ]"}'
endif
	@echo "[>------BinaryGenerated------<]" 
	
$(LIBDIR)/$(BUILDDIR)/libstm32f37x.a:
	@echo "[>----Library Compilation----<]"
	@$(MAKE) -C $(LIBDIR)
ifeq ($(UNAME),Windows)
	@If Not Exist "$(CURDIR)/$(BUILDDIR)" (mkdir "$(CURDIR)/$(BUILDDIR)")
else
	@mkdir -p $(BUILDDIR)
endif
	@echo "[>------CodeCompilation------<]"

proj: $(BUILDDIR)/$(PROJNAME).elf
	

$(BUILDDIR)/$(PROJNAME).elf: $(LIBDIR)/$(BUILDDIR)/libstm32f37x.a $(OBJS)
	@$(CC) $(LDFLAGS) $^ -o $@ -L$(LIBDIR)/$(BUILDDIR) -lstm32f37x
	@$(OBJCPY) $(CPFLAGS) $(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).bin
ifeq ($(UNAME),Windows)
	@$(OBJCPY) --output-target=ihex $(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).hex
endif

disassemble: all
	@$(OBJDMP) $(ODFLAGS) $(BUILDDIR)/$(PROJNAME).elf > $(BUILDDIR)/$(PROJNAME).dmp
	@$(OBJDMP) -dS $(BUILDDIR)/$(PROJNAME).elf > $(BUILDDIR)/$(PROJNAME).dis

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
$(BUILDDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/startup_stm32f37x.o: $(STARTUP)
ifeq ($(UNAME),Windows)
	@$(AS) $(AFLAGS) "$(CURDIR)/$(STARTUP)" -o "$(CURDIR)/$@"
else
	@$(AS) $(AFLAGS) $(STARTUP) -o $@
endif
	
flash: all
	@echo "[>-----Downloading to M4-----<]"
ifeq ($(UNAME),Windows)
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D "$(CURDIR)/$(BUILDDIR)/$(PROJNAME).bin"
endif
ifeq ($(UNAME),Linux)
	@sudo dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D $(BUILDDIR)/$(PROJNAME).bin
endif
ifeq ($(UNAME),Darwin)
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D $(BUILDDIR)/$(PROJNAME).bin
endif
	@echo "[>---------M4 Loaded---------<]"  

run: all
	@echo "[>-----Downloading to M4-----<]"
ifeq ($(UNAME),Windows)
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D "$(CURDIR)/$(BUILDDIR)/$(PROJNAME).bin"
endif
ifeq ($(UNAME),Linux)
	@sudo dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D $(BUILDDIR)/$(PROJNAME).bin
endif
ifeq ($(UNAME),Darwin)
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D $(BUILDDIR)/$(PROJNAME).bin
endif
	@echo "[>---------M4 Loaded---------<]"

clean:
ifeq ($(UNAME),Windows)
	@erase $(OBJSW) /s 
	@erase $(PROJNAME).dmp $(PROJNAME).dis $(PROJNAME).elf $(PROJNAME).hex $(PROJNAME).bin /s
else
	@rm -f $(BUILDDIR)/*.o $(BUILDDIR)/*.lst $(BUILDDIR)/*.map $(BUILDDIR)/*.dmp $(BUILDDIR)/*.dis \
	$(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).hex $(BUILDDIR)/$(PROJNAME).bin
endif
	
cleanlib: clean
	@$(MAKE) clean -C lib 

#------------------------------------------------------------------------------
