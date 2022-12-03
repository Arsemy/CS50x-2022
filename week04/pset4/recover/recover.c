#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

void writeJpg(BYTE *buffer, char head_or_body);
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw (card path)\n");
        return 1;
    }

    BYTE *buffer = malloc(512);
    char *filename = malloc(8);
    FILE *card = fopen(argv[1], "r");
    if (buffer == NULL || filename == NULL || card == NULL)
    {
        return 1;
    }
    FILE *restored_jpg;
    bool first_header = true;
    int filename_number = 0;
    int block_length = 512;
    while (fread(buffer, 1, block_length, card) == block_length)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_header == true)
            {
                sprintf(filename, "%03i.jpg", filename_number);
                filename_number++;

                restored_jpg = fopen(filename, "w");
                if (restored_jpg == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 1, block_length, restored_jpg);

                first_header = false;
            }
            else
            {
                fclose(restored_jpg);

                sprintf(filename, "%03i.jpg", filename_number);
                filename_number++;

                restored_jpg = fopen(filename, "w");
                if (restored_jpg == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 1, block_length, restored_jpg);
            }
        }
        else if (first_header == false)
        {
            fwrite(buffer, 1, block_length, restored_jpg);
        }
    }
    fclose(restored_jpg);
    fclose(card);
    free(buffer);
    free(filename);
    return 0;
}