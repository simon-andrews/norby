AR=i686-elf-ar
BUILD_DIR=build
CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -nostdlib -Wall -Wextra
NASM=nasm -felf32

LIBNORBYC_FLAGS=-Ilibc/include -Lbuild -lnorbyc

KERNEL_SOURCE_DIR=kernel
KERNEL_SOURCE_FILES=$(wildcard $(KERNEL_SOURCE_DIR)/*.c $(KERNEL_SOURCE_DIR)/*.asm)
KERNEL_OBJECT_FILES=$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(KERNEL_SOURCE_FILES)))

run: kernel
	qemu-system-i386 -kernel $(BUILD_DIR)/norby.bin

$(BUILD_DIR)/norby.bin: $(KERNEL_OBJECT_FILES) libc
	$(CC) -T $(KERNEL_SOURCE_DIR)/linker.ld -o $(BUILD_DIR)/norby.bin $(CFLAGS) $(KERNEL_OBJECT_FILES) $(LIBNORBYC_FLAGS)

$(BUILD_DIR)/$(KERNEL_SOURCE_DIR)/%.c.o: $(KERNEL_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $(LIBNORBYC_FLAGS) -Ikernel/include -c $< -o $@

$(BUILD_DIR)/$(KERNEL_SOURCE_DIR)/%.asm.o: $(KERNEL_SOURCE_DIR)/%.asm
	$(NASM) $< -o $@

LIBC_SOURCE_DIR=libc
LIBC_SOURCE_FILES=$(wildcard $(LIBC_SOURCE_DIR)/*.c)
LIBC_OBJECT_FILES=$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(LIBC_SOURCE_FILES)))

$(BUILD_DIR)/libnorbyc.a: $(LIBC_OBJECT_FILES)
	$(AR) rcs $(BUILD_DIR)/libnorbyc.a $(LIBC_OBJECT_FILES)

$(BUILD_DIR)/$(LIBC_SOURCE_DIR)/%.c.o: $(LIBC_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -Ilibc/include -Ikernel/include -c $< -o $@

kernel: $(BUILD_DIR)/norby.bin
libc: $(BUILD_DIR)/libnorbyc.a

clean:
	rm $(wildcard */*/*.o */*.bin */*.a)

.PHONY: clean
