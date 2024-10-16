#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Create a buffer for a block of data
    uint8_t buffer[512];

    // Create filename
    char filename[8];

    // counter
    int counter = 0;

    FILE *img = NULL; //fopen(filename, "w");
    while (fread(buffer, 1, 512, card) == 512) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            if (img != NULL) {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }
        if (img != NULL) {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img != NULL) {
        fclose(img);
    }
    fclose(card);
}
