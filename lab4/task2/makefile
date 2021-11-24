all: scmp1 scmp2

scmp2: scmp.o cmpstr2.o
	gcc -m32 -o scmp2 scmp.o cmpstr2.o

cmpstr2.o: cmpstr.c
	nasm -g -f elf -w+all -o cmpstr2.o cmpstr.s

scmp1: scmp.o cmpstr1.o
	gcc -m32 -o scmp1 scmp.o cmpstr1.o

cmpstr1.o: cmpstr.c
	gcc -m32 -c -o cmpstr1.o cmpstr.c

scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c
	
.PHONY: clean clean-o

clean:
	rm -rf *.o scmp1 scmp2

clean-o:
	rm -rf *.o