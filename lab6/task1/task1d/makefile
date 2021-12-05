all: myshell

myshell: LineParser.o myshell.o
	gcc -m32 -g -Wall -o myshell LineParser.o myshell.o
	rm -rf *.o

LineParser.o : LineParser.c
	gcc -g -Wall -m32 -ansi -c -o LineParser.o LineParser.c

myshell.o : myshell.c
	gcc -g -Wall -m32 -ansi -c -o myshell.o myshell.c

.PHONY: clean

clean:
	rm -ff *.o myshell