prog: prog.o openAndClose.o
	gcc -m32 -g -Wall -o prog prog.o openAndClose.o
	rm -f *.o

prog.o: prog.c
	gcc -g -m32 -ansi -Wall -c -o prog.o prog.c

openAndClose.o: openAndClose.asm
	nasm -g -f elf -w+all -o openAndClose.o openAndClose.asm


.PHONY: clean

clean:
	rm -f *o prog