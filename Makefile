CC = gcc
ASM = nasm
LD = ld
GRUB_MKRESCUE = grub-mkrescue
QEMU = qemu-system-x86_64

NAME = ContraOS
NAME_FLAG = -name $(NAME)

FLAGS_NASM = -f elf32 -o
DEBUG_FLAGS_NASM = -g -O0

OBJ_DIR = obj
SRC_DIR = src
BOOT_DIR = $(SRC_DIR)/boot
KERNEL_DIR = $(SRC_DIR)/kernel
ISO_DIR = isodir
ISO_BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(ISO_BOOT_DIR)/grub

MULTIBOOT_SRC = $(BOOT_DIR)/multiboot.asm
GDT_SRC = $(SRC_DIR)/gdt.asm
KERNEL_SRC = $(KERNEL_DIR)/kernel.c

MULTIBOOT_OBJ = $(OBJ_DIR)/multiboot.o
GDT_OBJ = $(OBJ_DIR)/gdt.o
KERNEL_OBJ = $(OBJ_DIR)/kernel.o

KERNEL_ELF = $(OBJ_DIR)/kernel.elf
ISO_IMAGE = my_os.iso

CC_FLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nostdinc -c
LD_FLAGS = -m elf_i386 -T link.ld -o

all: $(ISO_IMAGE)

build: $(KERNEL_ELF)

$(OBJ_DIR):
	mkdir $@

$(MULTIBOOT_OBJ): $(OBJ_DIR)
	$(ASM) $(FLAGS_NASM) $@ $(MULTIBOOT_SRC)

$(GDT_OBJ): $(OBJ_DIR)
	$(ASM) $(FLAGS_NASM) $@ $(GDT_SRC)

$(KERNEL_OBJ): $(OBJ_DIR)
	$(CC) $(CC_FLAGS) $(KERNEL_SRC) -o $@

$(GRUB_DIR): 
	mkdir -p $@

$(KERNEL_ELF): $(MULTIBOOT_OBJ) $(KERNEL_OBJ) $(GDT_OBJ) $(GRUB_DIR)
	$(LD) $(LD_FLAGS) $@ $(word 1, $^) $(word 2, $^) $(word 3, $^)

$(ISO_IMAGE): $(KERNEL_ELF) | $(GRUB_DIR)
	cp $(KERNEL_ELF) $(ISO_BOOT_DIR)/kernel.elf
	@echo 'menuentry "my_os" {' > $(GRUB_DIR)/grub.cfg
	@echo '    multiboot /boot/kernel.elf' >> $(GRUB_DIR)/grub.cfg
	@echo '}' >> $(GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)

run: $(ISO_IMAGE)
	$(QEMU) -cdrom $^ $(NAME_FLAG)

clean:
	rm -rf $(OBJ_DIR) $(ISO_DIR) $(ISO_IMAGE)