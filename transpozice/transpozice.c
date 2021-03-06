#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //error handling
    if (argc == 1)
    {
        fprintf(stderr, "Chybi cesta ke vstupnimu a vystupnimu souboru.\n");
    } else if (argc == 2)
    {
        fprintf(stderr, "Chybi cesta k vystupnimu souboru.\n");
    } else
    {
        char* input = argv[1];
        char* output = argv[2];
        FILE * inputf = fopen(input,"r");
        if (!inputf)
        {
            fprintf(stderr, "Vstupni soubor \"%s\" neexistuje\n", input);
            return 0;
        }
        int radky;
        int sloupce;
        fscanf(inputf, "%d %d", &radky, &sloupce);
        //printf("Radky: %d, sloupce: %d\n", radky, sloupce);
        int *array = malloc(radky * sloupce * sizeof(int));
        int reading;
        for (int i = 0; i < radky*sloupce; i++)        
        {  
            fscanf (inputf, "%d", &reading);
            array[i] = reading;
            //printf ("%d ", array[i]);
        }
        fclose(inputf);

        FILE * outputf = fopen(output,"w");
        for (int i = 0; i < sloupce; i++)
        {
            for (int j = 0; j < radky; j++)
            {
                //printf("%d ", array[i+j*sloupce]);
                fprintf(outputf, "%d ", array[i+j*sloupce]);
            }
            //printf("\n");
            fprintf(outputf, "\n");
        }
        fclose(outputf);
        free(array);
    }    
    return 0;
}