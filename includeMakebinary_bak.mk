# -*- includeMakebinary.mk -*-
include $(PROJ_ROOT)/includeEnv.mk


#all: $(PROJ_ROOT)/$(OBJS_DIR)/%.rel
all: $(PROJECT_NAME).hex

$(PROJECT_NAME).hex : $(PROJECT_NAME).ihx
	@echo "\nPack hex file"
	@echo "==============="
	srec_cat -disable_sequence_warnings $< -intel -crop 0x18000 0x1FFFF -offset -65536 -o bank1.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x28000 0x2FFFF -offset -98304 -o bank2.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x38000 0x3FFFF -offset -131072 -o bank3.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x48000 0x4FFFF -offset -163840 -o bank4.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x58000 0x5FFFF -offset -196608 -o bank5.hex -intel
	srec_cat -disable_sequence_warnings $< -intel -crop 0x00000 0x07FFF -o home.ihx -intel
	srec_cat home.ihx -intel bank1.hex -intel bank2.hex bank3.hex bank4.hex -intel -o $@ -intel
	rm -fr home.ihx bank1.hex bank2.hex

$(PROJECT_NAME).ihx: 
	cp -a $(SUB_DIRS)/$(BINARY_FILE_NAME).c $(PROJ_ROOT)/$(OBJS_DIR)/
	rm -fr $(PROJ_ROOT)/$(OBJS_DIR)/$(BINARY_FILE_NAME).rel
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(PROJ_ROOT)/$(OBJS_DIR)/$(BINARY_FILE_NAME).c $(PROJ_ROOT)/$(OBJS_DIR)/*.rel \
      -I$(STD_HEADER_PATH) -I$(USER_HEADER_PATH) -I$(STD_ASM_HEADER_PATH) -I$(STD_C_HEADER_PATH) \
      $(LIBRARY_LIST) -L$(STD_LIBRARY_PATH)