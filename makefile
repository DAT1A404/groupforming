#makefile

CFLAGS = -Wall -ansi

program.exe: read.o utility.o genetic.o visual.o datastructs.o
	gcc $(CFLAGS) -o program read.o utility.o genetic.o visual.o datastructs.o

read.o: read.c read.h
	gcc $(CFLAGS) -c read.c

utility.o: utility.c utility.h
	gcc $(CFLAGS) -c utility.c

genetic.o: genetic.c genetic.h
	gcc $(CFLAGS) -c genetic.c

visual.o: visual.c visual.h
	gcc $(CFLAGS) -c visual.c

datastructs.o: datastructs.c
	gcc $(CFLAGS) -c datastructs.c

clean:
	rm *.o program.exe