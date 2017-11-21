#include <stdio.h>
#include <stdlib.h>

int main(void)

{
	/* opening/creatign the txt file that the data is getting printeted to*/
    FILE* fptr = fopen("Exported_Data.txt", "w");
    /*if the file can't open/create the txt file this error vil be printed, meybe create possiblileti for looping */
    if(fptr == NULL)
    {
        printf("Error: could not open 'Exported_Data.txt'\n");
        return EXIT_FAILURE;
    }
    /* printing/creatingthe finale file, with the given info*/
    fprintf(fptr, "Put the output here\n");
    /*close the created fiel */
  	fclose(fptr);

      return 0;
}
/*libxlsxwriter er et bibliotek man kan downloade til c, som gør man kan lave xlsx filer*/


/* help for diffrent ways to add things to txt file*/
	/* print some text */
	/*const char *text = "Write this to the file";
	fprintf(f, "Some text: %s\n", text);

	/* print integers and floats */
	/*int i = 1;
	float py = 3.1415927;
	fprintf(f, "Integer: %d, float: %f\n", i, py);

	/* printing single chatacters */
	/* char c = 'A';*/
	 /* fprintf(f, "A character: %c\n", c);	*/
