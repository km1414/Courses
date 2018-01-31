#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>


int main(int argc, string argv[])
{

    // checking whether number of arguments is correct
    if (argc != 2)
    {
        printf("Wrong number of arguments!\n");
        // if number incorrect, quits the program with error code '1'
        return 1;
    }
    int number = atoi(argv[1]);

    // text input from user
    string text = get_string("plaintext:  ");

    printf("ciphertext: ");

    // iterating over all characters in string
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char character = text[i];

        // if character is alphabetical:
        if (isalpha(character))
        {

            // if character is uppercase:
            if (isupper(character))
            {
                printf("%c", (character - 'A' + number) % 26 + 'A');
            }

            // if character is lowercase:
            else
            {
                printf("%c", (character - 'a' + number) % 26 + 'a');
            }
        }
        // if character is non-alphabetical:
        else
        {
            printf("%c", character);
        }

    }
    printf("\n");

    // quits the program with no error code
    return 0;
}
