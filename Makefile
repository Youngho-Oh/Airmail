# This make file is main of make file
include $(PROJ_ROOT)/includeEnv.mk

# write below path you want to compile
SUB_DIRS = $(PROJ_ROOT)/src
PROJECT_NAME = Airmail
BINARY_FILE_NAME = main

# compile C files and output asm files
include $(PROJ_ROOT)/includePost.mk

# make bianry file
include $(PROJ_ROOT)/includeMakebinary.mk