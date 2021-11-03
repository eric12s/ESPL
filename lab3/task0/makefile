hexaPrint: hexaPrint.o
	gcc -g -m32 -Wall -o hexaPrint hexaPrint.o
	rm hexaPrint.o

hexaPrint.o: hexaPrint.c
	gcc -g -m32 -Wall -c -o hexaPrint.o hexaPrint.c

bubblesort: bubblesort.o
	gcc -g -m32 -Wall -o bubblesort bubblesort.o
	rm bubblesort.o

bubblesort.o: bubblesort.c
	gcc -g -m32 -Wall -c -o bubblesort.o bubblesort.c

.PHONY: clean

clean:
	rm *.o bubblesort hexaPrint