DISK_IMG=./disk.img
BOOT_LOADER_BIN=./bootloader/bootloader.bin

all : bootlader bootdisk

bootdisk : bootlader
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880 
	dd conv=notrunc if=$(BOOT_LOADER_BIN) of=$(DISK_IMG) bs=512 count=1 seek=0 #conv=onturnc tells dd not to change the size of 'of'
#dd conv=notrunc if=$(OS) of=$(DISK_IMG) bs=512 count=1 seek=1

bootlader : 
	nasm -f bin ./bootloader/bootloader.asm -o $(BOOT_LOADER_BIN)

clean : 
	rm -f $(BOOT_LOADER_BIN) $(DISK_IMG)

