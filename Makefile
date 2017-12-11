all: mainTest
mainTest: mainTest.o buffer.o
	gcc -o mainTest mainTest.c buffer.c -I

buffer.o: buffer.c 
	gcc -o buffer.o -c buffer.c
mainTest.o: mainTest.c API1.h
	gcc -o mainTest.o -c mainTest.c