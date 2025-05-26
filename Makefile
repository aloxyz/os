OBJS = kernel.o video.o kbd.o types.o

all: os

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

kernel.o: kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o

video.o: video.c
	gcc -m32 -ffreestanding -c video.c -o video.o

kbd.o: kbd.c
	gcc -m32 -ffreestanding -c kbd.c -o kbd.o

types.o: types.c
	gcc -m32 -ffreestanding -c types.c -o types.o

kernel.elf: $(OBJS)
	ld -m elf_i386 -T linker.ld -o kernel.elf $(OBJS)

kernel.bin: kernel.elf
	objcopy -O binary kernel.elf kernel.bin
	truncate -s %512 kernel.bin

os: boot.bin kernel.bin
	cat boot.bin kernel.bin > os.bin

run: os
	qemu-system-i386 -drive format=raw,file=os.bin

clean:
	rm -f *bin *.elf *.o
