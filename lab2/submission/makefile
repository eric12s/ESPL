task3: task3.o task2a.o task2b.o task2c.o
	gcc -g -m32 -Wall -o task3 task3.o task2a.o task2b.o task2c.o
	rm task3.o task2a.o task2b.o task2c.o

task3.o: task3.c task2a.o task2b.o task2c.o
	gcc -g -m32 -Wall -c -o task3.o task3.c

task2a: task2a.o
	gcc -g -m32 -Wall -o task2a task2a.o

task2a.o: task2a.c
	gcc -g -m32 -Wall -c -o task2a.o task2a.c

task2b: task2b.o
	gcc -g -m32 -Wall -o task2b task2b.o

task2b.o: task2b.c
	gcc -g -m32 -Wall -c -o task2b.o task2b.c

task2c: task2c.o task2a.o
	gcc -g -m32 -Wall -o task2c task2c.o task2a.o

task2c.o: task2c.c
	gcc -g -m32 -Wall -c -o task2c.o task2c.c

.PHONY: clean

clean:
	rm *.o