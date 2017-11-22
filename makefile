#makefile

CFLAGS = -Wall -ansi

program.exe: read.o utility.o genetic.o visual.o datastructs.o main.c
	gcc $(CFLAGS) -o program read.o utility.o genetic.o visual.o datastructs.o main.c

read.o: read.c read.h datastructs.c
	gcc $(CFLAGS) -c read.c

utility.o: utility.c utility.h datastructs.c
	gcc $(CFLAGS) -c utility.c

genetic.o: genetic.c genetic.h datastructs.c
	gcc $(CFLAGS) -c genetic.c

visual.o: visual.c visual.h datastructs.c
	gcc $(CFLAGS) -c visual.c

datastructs.o: datastructs.c
	gcc $(CFLAGS) -c datastructs.c

clean:
	rm *.o program.exe