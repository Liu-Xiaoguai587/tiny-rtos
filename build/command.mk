CROSS_COMPILE = riscv64-unknown-elf-
#CROSS_COMPILE = riscv64-linux-gnu-
CFLAGS = -specs=picolibc.specs -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall
#			^ can not include stdlib, must use picolibc-riscv64-unknown-elf
#			origin: https://linux.debian.bugs.dist.narkive.com/OZN3UdMP/bug-979542-gcc-riscv64-unknown-elf-unable-to-use-stdint-h

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
