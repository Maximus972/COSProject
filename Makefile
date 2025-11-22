# BASE
NAME = ContraOS

# C
CC = gcc
CC_FLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nostdinc -c

#ASM
ASM = nasm
FLAGS_NASM = -f elf32 -o
DEBUG_FLAGS_NASM = -g -O0

#LD
LD = ld
LD_FLAGS = -m elf_i386 -T link.ld -o

#QEMU
QEMU = qemu-system-x86_64
NAME_FLAG = -name $(NAME)

#OTHER_UTILITIES
GRUB_MKRESCUE = grub-mkrescue

#DIR
OBJ_DIR = obj
SRC_DIR = src
BOOT_DIR = $(SRC_DIR)/boot
KERNEL_DIR = $(SRC_DIR)/kernel
ISO_DIR = isodir
ISO_BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(ISO_BOOT_DIR)/grub
LIBS_DIR = $(SRC_DIR)/libs

#SRC
MULTIBOOT_SRC = $(BOOT_DIR)/multiboot.asm
GDT_SRC = $(SRC_DIR)/gdt.asm
KERNEL_SRC = $(KERNEL_DIR)/kernel.c
ASM_BASE_FUNCTIONS_SRC = $(LIBS_DIR)/base_functions.asm

#OBJ
MULTIBOOT_OBJ = $(OBJ_DIR)/multiboot.o
GDT_OBJ = $(OBJ_DIR)/gdt.o
KERNEL_OBJ = $(OBJ_DIR)/kernel.o
ASM_BASE_FUNCTIONS_OBJ = $(OBJ_DIR)/base_functions.o

#OTHER_FILES
KERNEL_ELF = $(OBJ_DIR)/kernel.elf
ISO_IMAGE = ContraOS.iso

all: $(ISO_IMAGE)

build: $(KERNEL_ELF)

run: $(ISO_IMAGE)
	$(QEMU) -cdrom $^ $(NAME_FLAG)

clean:
	rm -rf $(OBJ_DIR) $(ISO_DIR) $(ISO_IMAGE)

$(OBJ_DIR):
	mkdir $@

$(MULTIBOOT_OBJ): $(OBJ_DIR)
	$(ASM) $(FLAGS_NASM) $@ $(MULTIBOOT_SRC)

$(GDT_OBJ): $(OBJ_DIR)
	$(ASM) $(FLAGS_NASM) $@ $(GDT_SRC)

$(ASM_BASE_FUNCTIONS_OBJ):
	$(ASM) $(FLAGS_NASM) $@ $(ASM_BASE_FUNCTIONS_SRC)

$(KERNEL_OBJ): $(OBJ_DIR)
	$(CC) $(CC_FLAGS) $(KERNEL_SRC) -o $@

$(GRUB_DIR): 
	mkdir -p $@

$(KERNEL_ELF): $(MULTIBOOT_OBJ) $(KERNEL_OBJ) $(GDT_OBJ) $(ASM_BASE_FUNCTIONS_OBJ) $(GRUB_DIR) 
	$(LD) $(LD_FLAGS) $@ $(word 1, $^) $(word 2, $^) $(word 3, $^) $(word 4, $^)

$(ISO_IMAGE): $(KERNEL_ELF) | $(GRUB_DIR)
	cp $(KERNEL_ELF) $(ISO_BOOT_DIR)/kernel.elf
	@echo 'menuentry "$(NAME)" {' > $(GRUB_DIR)/grub.cfg
	@echo '    multiboot /boot/kernel.elf' >> $(GRUB_DIR)/grub.cfg
	@echo '}' >> $(GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)