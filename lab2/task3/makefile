task3: task3.o task2a.o task2b.o task2c.o
	gcc -g -m32 -Wall -o task3 task3.o task2a.o task2b.o task2c.o
	rm task3.o task2a.o task2b.o task2c.o

task3.o: task3.c task2a.o task2b.o task2c.o
	gcc -g -m32 -Wall -c -o task3.o task3.c

task2a.o: ../task2/task2a.c
	gcc -g -m32 -Wall -c -o task2a.o ../task2/task2a.c

task2b.o: ../task2/task2b.c
	gcc -g -m32 -Wall -c -o task2b.o ../task2/task2b.c

task2c.o: ../task2/task2c.c task2a.o
	gcc -g -m32 -Wall -c -o task2c.o ../task2/task2c.c

.PHONY: clean

clean:
	rm *.o addresses