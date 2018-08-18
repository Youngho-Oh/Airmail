# -*- includePost.mk -*-
include $(PROJ_ROOT)/includeEnv.mk

TARGET_OBJS = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%.asm)

.SUFFIXES: .c .asm .ihx
.PHONY: all depend clean

#all: $(HEX)
all: subdirs $(TARGET_OBJS) copy

subdirs :
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

#$(HEX): $(OBJS)
#	packihx $^ > $@

$(OBJS_DIR)/%.asm: %.c
	@echo "===================================================="
	@echo "= Compiling $@ "
	@echo "===================================================="
	@`[ -d $(PROJ_ROOT)/$(OBJS_DIR) ] || $(MKDIR) $(PROJ_ROOT)/$(OBJS_DIR)`
	$(CC) $(CFLAGS) $(COMPILER_DEFINE) $(SPECIFIC_COMPILE_OPTION) -c $^ -I$(STD_HEADER_PATH) -I$(USER_HEADER_PATH) \
	 -I$(STD_ASM_HEADER_PATH) -I$(STD_C_HEADER_PATH) \
	 $(USER_DEFINE)

copy:
	@for files in $(OUTPUT_FILES); do \
		if [ -f $$files ]; \
			then $(MV) $(OUTPUT_FILES) $(PROJ_ROOT)/$(OBJS_DIR); fi; \
	done

#depend:
#	gcc -M $(SOURCE)

clean: delsubdirs removed

delsubdirs:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

removed:
	@if [ -d $(PROJ_ROOT)/$(OBJS_DIR) ]; \
		then $(RM) -fr $(PROJ_ROOT)/$(OBJS_DIR); fi; \
	done
	$(RM) -fr $(OBJS_DIR)
	$(RM) $(OUTPUT_FILES)

#defines dependency part
$(HEX): $(SOURCE) $(OBJS)

#UIP_CONF_IPV6=1

# �������� ���� 
#hello.o: $($@:.o=.c) $($@:.o=.h) Makefile 
#test.o: $($@:.o=.c) hello.h Makefile