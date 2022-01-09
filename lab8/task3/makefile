all: fibonacci patch task3

task3: task3.o
	gcc -g -m32 task3.o -o task3

task3.o: task3.c
	gcc -g -m32 -fno-pie -c -o task3.o task3.c

fibonacci: fibonacci.o
	gcc -g -m32 fibonacci.o -o fibonacci

fibonacci.o: fibonacci.c
	gcc -g -m32 -fno-pie -c -o fibonacci.o fibonacci.c

patch: patch.o
	gcc -g -m32 patch.o -o patch

patch.o: patch.c
	gcc -g -m32 -fno-pie -c -o patch.o patch.c

.PHONY: clean

clean:
	rm -f *.o