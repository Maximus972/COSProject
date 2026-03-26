NAME = ContraOS
NAME_FLAG = -name $(NAME)

OBJS = $(shell mkdir -p obj; find obj -name '*.o')

ISO_IMAGE = ContraOS.iso
QEMU = qemu-system-x86_64
CC = gcc
CFLAGS = -w -ffreestanding -m32 -fno-pie -nostdlib -nostartfiles -nostdinc -c
NS = nasm
NSFLAGS = -f elf32
LD = ld

GRUB_MKRESCUE = grub-mkrescue
ISO_DIR = isodir
ISO_BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(ISO_BOOT_DIR)/grub

BOOT_C = $(shell find src/boot -type f -name '*.c')
BOOT_ASM = $(shell find src/boot -type f -name '*.asm')
LIBS_C = $(shell find src/libs -type f -name '*.c')
LIBS_ASM = $(shell find src/libs -type f -name '*.asm')
KERNEL_C = $(shell find src/kernel -type f -name '*.c')
KERNEL_ASM = $(shell find src/kernel -type f -name '*.asm')

define build-rule
	for src in $(1); do \
		obj=$$(echo $$src | sed 's|$(2)|$(3)|' | sed 's|$(4)$$|$(5)|'); \
        echo "Building $$src -> $$obj"; \
        mkdir -p $$(dirname $$obj); \
        if echo $$src | grep -q "\.c$$"; then \
            $(6) $(7) -c $$src -o $$obj; \
        else \
            $(6) $(7) $$src -o $$obj; \
        fi; \
    done
endef

boot:
	mkdir -p obj/multiboot
	$(call build-rule,$(BOOT_C),src/boot,obj/boot,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(BOOT_ASM),src/boot,obj/boot,.asm,.o,$(NS),$(NSFLAGS))

libs:
	mkdir -p obj/libs
	$(call build-rule,$(LIBS_C),src/libs,obj/libs,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(LIBS_ASM),src/libs,obj/libs,.asm,.o,$(NS),$(NSFLAGS))

kernel:
	mkdir -p obj/kernel
	$(call build-rule,$(KERNEL_C),src/kernel,obj/kernel,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(KERNEL_ASM),src/kernel,obj/kernel,.asm,.o,$(NS),$(NSFLAGS))

link: kernel boot libs
	ld -m elf_i386 -T link.ld -o obj/kernel.elf $(OBJS)

make_iso: link
	mkdir -p isodir/boot/grub
	cp obj/kernel.elf isodir/boot/kernel.elf
	@echo 'menuentry "ContraOS" {' > isodir/boot/grub/grub.cfg
	@echo '    multiboot /boot/kernel.elf' >> isodir/boot/grub/grub.cfg
	@echo '}' >> isodir/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o ContraOS.iso isodir

run: make_iso
	$(QEMU) -cdrom $(ISO_IMAGE) $(NAME_FLAG) # -s -S $(ASYNC_FLAG)

clean:
	rm -rf isodir obj ContraOS.iso
