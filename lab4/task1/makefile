task1: task1.o funcA.o
	gcc -m32 -g -Wall -o task1 task1.o funcA.o

task1.o: task1.c
	gcc -g -m32 -ansi -Wall -c -o task1.o task1.c

funcA.o: funcA.asm
	nasm -g -f elf -w+all -o funcA.o funcA.asm


.PHONY: clean

clean:
	rm -f *o