#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // create variables
    BYTE block[512];
    BYTE block_next[512];
    int jpg_num = 0;
    char jpg_name[8];
    int not_EOF = 1;


    // looping over data file
    while (0 < 1)
    {
        // reads block form file if no pics found yet
        if (jpg_num == 0)
        {
            fread(&block, 512, 1, inptr);
        }

        // if begginig of JPEG found:
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff)
        {

            // creates new output file
            sprintf(jpg_name, "%03i.jpg", jpg_num);
            FILE *outptr = fopen(jpg_name, "w");

            // filling output file until:
            while (0 < 1)
            {
                not_EOF = fread(&block_next, 512, 1, inptr);
                fwrite(&block, 512, 1, outptr);
                memcpy(&block, &block_next, 512);

                // break, if new begginig of JPEG found
                if (block[0] == 0xff &&
                    block[1] == 0xd8 &&
                    block[2] == 0xff)
                {
                    break;
                }

                // close the program, if EOF reached
                if (not_EOF == 0)
                {
                    fclose(outptr);
                    fclose(inptr);
                    return 0;

                }

            }

            // close output file
            fclose(outptr);
            jpg_num++;
        }
    }
}