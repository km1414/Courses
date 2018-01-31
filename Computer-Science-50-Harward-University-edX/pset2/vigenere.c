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
        printf("Wrong number of arguments!");
        // if number incorrect, quits the program with error code '1'
        return 1;
    }

    // saving key from input
    string key = argv[1];

    // checking whether key is only alphabetical
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // checking whether all character in  key are alphabetical
        if (!isalpha(key[i]))
        {
            printf("Wrong key!");
            // if any non-alphabetical character, quits the program with error code '1'
            return 1;
        }
    }


    // text input from user
    string text = get_string("plaintext:  ");

    printf("ciphertext: ");

    // iterating over all characters in string
    for (int i = 0, n = strlen(text), j = 0; i < n; i++)
    {
        char character = text[i];
        int number;


        // if character is uppercase:
        if (isupper(character))
        {
            // getting cipher number from key word
            number = toupper(key[j % strlen(key)]) - 'A';
            j += 1;
            printf("%c", (character - 'A' + number) % 26 + 'A');
        }

        // if character is lowercase:
        else if (islower(character))
        {
            // getting cipher number from key word
            number = toupper(key[j % strlen(key)]) - 'A';
            j += 1;
            printf("%c", (character - 'a' + number) % 26 + 'a');
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
