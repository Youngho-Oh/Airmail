# -*- includeBinary.mk -*-

SDCC_CMD_ROOT_PATH = /mnt/c/sdcc/bin
CC = $(SDCC_CMD_ROOT_PATH)/sdcc
PACKIHX = $(SDCC_CMD_ROOT_PATH)/packihx

#CFLAGS = --model-huge --stack-auto --xstack --std-c99 --debug
CFLAGS = --model-huge --stack-auto --xstack --std-c99 --debug
#LDFLAGS = --code-loc 0x0000 --xram-loc 0x0000 --xram-size 0x2000 --stack-size 16
LDFLAGS = --code-loc 0x0000 --xram-loc 0x0000 --xram-size 0x2000 --stack-size 16 -Wl-r -Wl-bBANK1=0x018000 -Wl-bBANK2=0x028000
#LDFLAGS = --code-loc 0x0000 --xram-loc 0x0000 --xram-size 0x2000 --stack-size 16 -Wl-r -Wl-bBANK1=0x018000
MV = mv
RM = rm -f
MKDIR = mkdir
MAKE = make

# Header Path
SDCC_ROOT_PATH = /mnt/c/sdcc/device
STD_HEADER_PATH = $(SDCC_ROOT_PATH)/include
STD_ASM_HEADER_PATH = $(STD_HEADER_PATH)/asm/mcs51
STD_C_HEADER_PATH = $(STD_HEADER_PATH)/mcs51
USER_HEADER_PATH = $(PROJ_ROOT)

#define options
COMPILER_DEFINE = -DSDCC -Dchip=2530

# Library Path
STD_LIBRARY_PATH = $(SDCC_ROOT_PATH)/lib/build/huge-xstack-auto
LIBRARY_LIST = libfloat.lib libint.lib liblong.lib liblonglong.lib libsdcc.lib mcs51.lib

#output files
OUTPUT_FILES = *.asm *.lst *.rel *.sym *.lk *.mem *.ihx *.map *.rst *.hex *.adb *.cdb *.omf

ifeq ($(RELEASE), 1)
OBJS_DIR = Release
DBG_FLAGS = -DNDEBUG
else
OBJS_DIR = Debug
DBG_FLAGS = -DDEBUG
endif