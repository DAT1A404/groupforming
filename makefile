#makefile

CFLAGS = -Wall -ansi -lm

program: read.o utility.o genetic.o visual.o datastructs.o commands.o ctest.o main.c
	gcc $(CFLAGS) -o program read.o utility.o genetic.o visual.o datastructs.o commands.o ctest.o main.c

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

commands.o: commands.c commands.h
	gcc $(CFLAGS) -c commands.c

ctest.o: ctest.c
	gcc $(CFLAGS) -c ctest.c

clean:
	rm *.o program*
