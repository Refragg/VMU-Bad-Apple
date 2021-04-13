all: rm-elf bapple.elf

include $(KOS_BASE)/Makefile.rules

OBJS = bapple.o

KOS_LOCAL_CFLAGS = -I$(KOS_BASE)/addons/zlib
	
clean:
	-rm -f bapple.elf $(OBJS)
	-rm -f romdisk_boot.*

dist:
	-rm -f $(OBJS)
	-rm -f romdisk_boot.*
	$(KOS_STRIP) bapple.elf
	
rm-elf:
	-rm -f bapple.elf
	-rm -f romdisk_boot.*

bapple.elf: $(OBJS) romdisk_boot.o 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $@ $(KOS_START) $^ -ltremor -lz -lm $(KOS_LIBS)

wfont.o: wfont.bin
	$(KOS_BASE)/utils/bin2o/bin2o $< wfont $@

romdisk_boot.img:
	$(KOS_GENROMFS) -f $@ -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk_boot $@

run: bapple.elf
	$(KOS_LOADER) $<


