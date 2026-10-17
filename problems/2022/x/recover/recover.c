#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)                                                                      //Validate the input argument
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    
    FILE *card_file = fopen(argv[1], "r");                                              //Open the memory card file

    if (card_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE block[BLOCK_SIZE];                                                             //Initialize one block of data(512) at a time

    FILE *image_file = NULL;
    char image_name[8];
    int image_count = 0;

    while (fread(block, 1, BLOCK_SIZE, card_file) == BLOCK_SIZE)                       //Reading the one block of card at a time
    {
        if (block[0] == 0xff &&                                                        //Detect the starts of a JPEG
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0)
        {
            if (image_file != NULL)                                                    //Close the previous image
            {
                fclose(image_file);
            }

            sprintf(image_name, "%03i.jpg", image_count);                              //Open the next JPEG
            image_file = fopen(image_name, "w");

            image_count++;
        }

        if (image_file != NULL)                                                        //Write blocks belonging to a JPEG
        {
            fwrite(block, 1, BLOCK_SIZE, image_file);
        }
    }

    if (image_file != NULL)                                                            //Close the output file, if one was opened
    {
        fclose(image_file);
    }

    fclose(card_file);

    return 0;
}
