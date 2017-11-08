cc = gcc
CC = gcc
CFLAGS = -g -g3 -ggdb -Wall -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wstrict-prototypes -Wmissing-declarations -ansi -fbounds-check -fstrict-aliasing
OFLAGS = -O3 -Wall -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wstrict-prototypes -Wmissing-declarations -ansi -fbounds-check -fstrict-aliasing 
HOME = /ehome/gphani

process: process.o alloclib.o 
	$(cc) $(CFLAGS) process.o alloclib.o -lm -o process.e

main.o: process.c 
	$(cc) $(CFLAGS) -c main.c -o main.o

alloclib.o: alloclib.c alloclib.h
	$(cc) $(CFLAGS) -c alloclib.c -o alloclib.o

clean:
	/bin/rm -f *.o *.O *.e *.gnu *.dat nohup.out core *.m

nr:
	/bin/rm -f *.gnu *.dat *.m

tar:
	tar -cvf cfdcodebackup.tar *.c *.h *.in Makefile

