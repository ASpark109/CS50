#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define blockSize 512

int main(int argc, char *argv[])
{   
    //Checking the correctness of the input data
    if(argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //Open the file for reading
    FILE* fileCard = fopen("card.raw", "rb");
    if(fileCard == NULL)
    {
        printf("file not open\n");
        return 1;
    }

    //initialize a new file
    FILE* newFile = NULL;

    //allocate memory to store the read unit from the memory card
    uint8_t *box = malloc(sizeof(uint8_t) * blockSize);


    unsigned char fourBitControl = 0b1110;

    bool writePermision = false;

    char name[8];

    int counter = 0;

    /*  
    *    read data at 512 bytes at a time
    *    the loop runs as long as the fread() function returns
    *    the number of bytes read - 512
    */
    while(fread(box, sizeof(uint8_t), blockSize, fileCard) == blockSize)
    {
        //If the first 3 bytes of the read block match
        if(*box == 0xff && *(box+1) == 0xd8 && *(box+2) == 0xff)
        {
            //if the first four bits are 0b1110 or #e
            if(*(box+3) >> 4 == fourBitControl)
            {
                //if record data is found, write permission is obtained
                writePermision = true;

                //closes the previous file if it was open
                if(newFile != NULL) fclose(newFile);

                //create a name for the file based on its order (counter)
                sprintf(name, "%03d.jpg", counter);
                
                //incrementing the number of files
                counter++;

                //open a file to record data
                newFile = fopen(name, "wb");
            }
        }
        if(writePermision)
        {
            //write data to a file
            fwrite(box, blockSize, 1, newFile);
        }
    }

    //close the file for reading
    fclose(fileCard);

    //freeing the memory of the unit to analyze the read data
    free(box);

    return 0;
}