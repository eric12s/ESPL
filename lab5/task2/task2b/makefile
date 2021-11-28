%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

all: task2b

task2b: task2b.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o task2b
