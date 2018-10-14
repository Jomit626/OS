#kernel objects that need cc
KERNEL_C_Objects = ./kernel/kernel.o ./kernel/uilts.o ./cpu/IDT.o ./cpu/ISR.o ./cpu/timer.o ./drivers/ports.o ./drivers/screen.o ./drivers/keyboard.o 
KERNEL_ASM_Objects = ./kernel/kernel_entry.o ./cpu/ISR_handler.o

DISK_IMG=./disk.img
BOOT_LOADER_BIN=./bootloader/bootloader.bin
KERNEL=./kernel/kernel.bin

CC =/home/jomit/opt/cross/bin/i686-elf-gcc -ffreestanding -c
LD =/home/jomit/opt/cross/bin/i686-elf-ld -Ttext 0x1000 --oformat binary

.PHONY:all kernel bootloader debug

disk: disk.img
debug:./kernel/kernel.elf

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
	nasm -f elf -o $@ $<

#-----------------DISK
disk.img: $(BOOT_LOADER_BIN) $(KERNEL) 
	#dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880 
	#dd conv=notrunc if=$(BOOT_LOADER_BIN) of=$(DISK_IMG) bs=512 count=2 seek=0 #conv=onturnc tells dd not to change the size of 'of'
	#dd conv=notrunc if=$(KERNEL) of=$(DISK_IMG) bs=512 count=512 seek=1
	cat $^ > os-image.bin
#----------------DEBUG
./kernel/kernel.elf:$(KERNEL_C_Objects) $(KERNEL_ASM_Objects)
	$(LD_DEBUG) -o ./kernel/kernel.elf $(KERNEL_ASM_Objects)  $(KERNEL_C_Objects)	


clean:
	-rm -f $(BOOT_LOADER_BIN) $(DISK_IMG) $(KERNEL) $(KERNEL_ASM_Objects)  $(KERNEL_C_Objects) ./kernel/kernel.elf