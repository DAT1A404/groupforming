#makefile

CFLAGS = -Wall -ansi -lm

groupforming: datastructs.h read.o utility.o genetic.o visual.o commands.o export.o ctest.o main.c
	gcc $(CFLAGS) -o groupforming read.o utility.o genetic.o visual.o commands.o export.o ctest.o main.c

read.o: read.c read.h datastructs.h
	gcc $(CFLAGS) -c read.c

utility.o: utility.c utility.h datastructs.h
	gcc $(CFLAGS) -c utility.c

genetic.o: genetic.c genetic.h datastructs.h
	gcc $(CFLAGS) -c genetic.c

visual.o: visual.c visual.h datastructs.h
	gcc $(CFLAGS) -c visual.c

commands.o: commands.c commands.h datastructs.h
	gcc $(CFLAGS) -c commands.c

export.o: export.c export.h datastructs.h
	gcc $(CFLAGS) -c export.c

ctest.o: ctest.c datastructs.h
	gcc $(CFLAGS) -c ctest.c

clean:
	rm *.o groupforming*
