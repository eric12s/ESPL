%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

all: task1a task1b task2a

task1b: lwc.o task1b.o
	ld -melf_i386 -o $@ $^

task1a: lwc.o task1a.o
	ld -melf_i386 -o $@ $^

task2a: task2a.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o lwca
