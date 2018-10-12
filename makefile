#kernel objects that need cc
KERNEL_C_Objects = ./kernel/kernel.o ./kernel/uilts.o ./drivers/screen.o
KERNEL_ASM_Objects = ./kernel/kernel_entry.o

DISK_IMG=./disk.img
BOOT_LOADER_BIN=./bootloader/bootloader.bin
KERNEL=./kernel/kernel.bin

CC =gcc -ffreestanding -c -m32
LD = ld -Ttext 0x1000 --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_ -m elf_i386

.PHONY:all kernel bootloader

disk: disk.img

#------------------BOOTLOADER
$(BOOT_LOADER_BIN):./bootloader/bootloader.asm
	nasm -f bin ./bootloader/bootloader.asm -o $(BOOT_LOADER_BIN)

#------------------KERNEL
$(KERNEL): $(KERNEL_ASM_Objects)  $(KERNEL_C_Objects)
	$(LD) -o $(KERNEL) $(KERNEL_ASM_Objects)  $(KERNEL_C_Objects)
	#linker respects the order of the ﬁles we gave to it 

#kernel c objects
$(KERNEL_C_Objects):%.o:%.c
	$(CC) $< -o $@
#kernel asm objects
$(KERNEL_ASM_Objects):%.o:%.asm
	nasm -f ELF -o $@ $<

#-----------------DISK
disk.img: $(KERNEL) $(BOOT_LOADER_BIN)
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880 
	dd conv=notrunc if=$(BOOT_LOADER_BIN) of=$(DISK_IMG) bs=512 count=2 seek=0 #conv=onturnc tells dd not to change the size of 'of'
	dd conv=notrunc if=$(KERNEL) of=$(DISK_IMG) bs=512 count=30 seek=1

clean:
	-rm -f $(BOOT_LOADER_BIN) $(DISK_IMG) $(KERNEL) $(KERNEL_ASM_Objects)  $(KERNEL_C_Objects)