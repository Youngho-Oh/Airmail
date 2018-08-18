# -*- includeMakebinary.mk -*-
include $(PROJ_ROOT)/includeEnv.mk


#all: $(PROJ_ROOT)/$(OBJS_DIR)/%.rel
all: $(PROJECT_NAME).hex

$(PROJECT_NAME).hex : $(PROJECT_NAME).ihx
	@echo "\nPack hex file"
	@echo "==============="
	srec_cat -disable_sequence_warnings $< -intel -crop 0x10000 0x1FFFF -offset -0x10000 -o bank1.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x00000 0x0FFFF -o home.ihx -intel
	srec_cat home.ihx -intel bank1.hex -intel -o $@ -intel
	rm -fr home.ihx bank1.hex

$(PROJECT_NAME).ihx: 
	cp -a $(SUB_DIRS)/$(BINARY_FILE_NAME).c $(PROJ_ROOT)/$(OBJS_DIR)/
	rm -fr $(PROJ_ROOT)/$(OBJS_DIR)/$(BINARY_FILE_NAME).rel
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(PROJ_ROOT)/$(OBJS_DIR)/$(BINARY_FILE_NAME).c $(PROJ_ROOT)/$(OBJS_DIR)/*.rel \
      -I$(STD_HEADER_PATH) -I$(USER_HEADER_PATH) -I$(STD_ASM_HEADER_PATH) -I$(STD_C_HEADER_PATH) \
      $(LIBRARY_LIST) -L$(STD_LIBRARY_PATH)