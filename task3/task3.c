#include <stdlib.h>   
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fileIn, *fileOut;
    
    if ((fileIn = fopen(argv[1], "r")) == NULL)
    {
        printf("Can't open the input file.\n");
        
        exit(1);
    }
    
    if ((fileOut = fopen(argv[2], "w")) == NULL)
    {
        printf("Can't open the output file.\n");
        
        exit(1);
    }

    char sym;
    int esym = -1;

    while ((sym = getc(fileIn)) != EOF)
    {
    	esym = fputc(sym, fileOut);
    	
    	if (esym == EOF)
    	{
    	   printf("Can't write to file.\n");    	   
    	   break;
    	}
    }

    if (fclose(fileIn) == EOF)
    {
        printf("An error occured while closing the input file.\n");
        
        exit(1);
    }
    
    if (fclose(fileOut) == EOF)
    {
        printf("An error occured while closing the output file.\n");
        
        exit(1);
    }
    
    printf("Success.\n");

    exit(0);
}
