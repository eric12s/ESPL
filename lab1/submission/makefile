task1a: task1a.o
	gcc -g -m32 -Wall -o task1a task1a.o
	rm task1a.o

task1a.o: task1a.c
	gcc -g -m32 -Wall -c -o task1a.o task1a.c

task1b: task1b.o
	gcc -g -m32 -Wall -o task1b task1b.o
	rm task1b.o

task1b.o: task1b.c
	gcc -g -m32 -Wall -c -o task1b.o task1b.c

task1c: task1c.o
	gcc -g -m32 -Wall -o task1c task1c.o
	rm task1c.o

task1c.o: task1c.c
	gcc -g -m32 -Wall -c -o task1c.o task1c.c

task2: task2.o
	gcc -g -m32 -Wall -o task2 task2.o
	rm task2.o

task2.o: task2.c
	gcc -g -m32 -Wall -c -o task2.o task2.c

.PHONY: clean
	rm -rf ./*.o main