DISK_IMG=./disk.img
BOOT_LOADER_BIN=./bootloader/bootloader.bin
KERNEL=./kernel/kernel.bin
CC =gcc -ffreestanding -c -m32
LD = ld -Ttext 0x1000 --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_ -m elf_i386

all :kernel bootlader bootdisk 



bootdisk : bootlader kernel
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880 
	dd conv=notrunc if=$(BOOT_LOADER_BIN) of=$(DISK_IMG) bs=512 count=2 seek=0 #conv=onturnc tells dd not to change the size of 'of'
	dd conv=notrunc if=$(KERNEL) of=$(DISK_IMG) bs=512 count=1 seek=1

bootlader : ./bootloader/bootloader.asm
	nasm -f bin ./bootloader/bootloader.asm -o $(BOOT_LOADER_BIN)



kernel: ./kernel/kernel.o $(KERNEL) 

$(KERNEL) :./kernel/kernel.o ./kernel/kernel_entry.o
	
	$(LD) -o $(KERNEL) ./kernel/kernel_entry.o  ./kernel/kernel.o 
	#linker respects the order of the ﬁles we gave to it 

./kernel/kernel.o: ./kernel/kernel.c
	$(CC) ./kernel/kernel.c -o ./kernel/kernel.o

./kernel/kernel_entry.o: ./kernel/kernel_entry.asm
	nasm ./kernel/kernel_entry.asm -f ELF -o ./kernel/kernel_entry.o



clean : 
	rm -f $(BOOT_LOADER_BIN) $(DISK_IMG) $(KERNEL) ./kernel/kernel.o ./kernel/kernel_entry.o

