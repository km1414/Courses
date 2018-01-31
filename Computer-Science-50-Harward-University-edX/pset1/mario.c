#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int number, spaces, hashes;

    // gets suitable input from user
    do
    {
        number = get_int("Height: ");
    }
    while (number < 0 || number > 23);

    // for every line
    for (int i = 0; i < number; i++)
    {
        // counts spaces and hashes for every line
        spaces = number - (i + 1);
        hashes = number - spaces;

        // prints left spaces
        for (int s = 0; s < spaces; s++)
        {
            printf(" ");
        }

        // prints left hashes
        for (int h = 0; h < hashes; h++)
        {
            printf("#");
        }


        // separator between sides
        printf("  ");


        // prints right spaces
        for (int h = 0; h < hashes; h++)
        {
            printf("#");
        }

        // new line
        printf("\n");
    }

}
