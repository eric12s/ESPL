%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

all: task2a

task2a: task2a.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o task2a
