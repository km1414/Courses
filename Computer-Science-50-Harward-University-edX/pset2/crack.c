#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>


int main(int argc, string argv[])
{

    // checking whether number of arguments is correct
    if (argc != 2)
    {
        // if incorrect, quits the program with error code '1'
        printf("Wrong number of arguments!\n");
        return 1;
    }

    // saving key from input
    string hashed = argv[1];

    // getting "salt"
    char salt[3];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = hashed[i];
    }

    // string of possible characters
    string chars = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    int chars_len = strlen(chars);

    // guesing password of 1 character
    char pass_try1[2];

    for (int i = 0; i < chars_len; i++)
    {
        pass_try1[0] = chars[i];

        string hashed_new = crypt(pass_try1, salt);

        // if hashed fits
        if (strcmp(hashed, hashed_new) == 0)
        {
            printf("%s\n", pass_try1);
            return 0;
        }
    }


    // guesing password of 2 characters
    char pass_try2[3];

    for (int i = 0; i < chars_len; i++)
    {
        for (int k = 0; k < chars_len; k++)
        {
            pass_try2[0] = chars[i];
            pass_try2[1] = chars[k];

            string hashed_new = crypt(pass_try2, salt);

            // if hashed fits
            if (strcmp(hashed, hashed_new) == 0)
            {
                printf("%s\n", pass_try2);
                return 0;
            }
        }
    }


    // guesing password of 3 characters
    char pass_try3[4];

    for (int i = 0; i < chars_len; i++)
    {
        for (int k = 0; k < chars_len; k++)
        {
            for (int l = 0; l < chars_len; l++)
            {
                pass_try3[0] = chars[i];
                pass_try3[1] = chars[k];
                pass_try3[2] = chars[l];

                string hashed_new = crypt(pass_try3, salt);

                // if hashed fits
                if (strcmp(hashed, hashed_new) == 0)
                {
                    printf("%s\n", pass_try3);
                    return 0;
                }
            }
        }
    }


    // guesing password of 4 characters
    char pass_try4[5];

    for (int i = 0; i < chars_len; i++)
    {
        for (int k = 0; k < chars_len; k++)
        {
            for (int l = 0; l < chars_len; l++)
            {
                for (int m = 0; m < chars_len; m++)
                {
                    pass_try4[0] = chars[i];
                    pass_try4[1] = chars[k];
                    pass_try4[2] = chars[l];
                    pass_try4[3] = chars[m];

                    string hashed_new = crypt(pass_try4, salt);

                    // if hashed fits
                    if (strcmp(hashed, hashed_new) == 0)
                    {
                        printf("%s\n", pass_try4);
                        return 0;
                    }
                }
            }
        }
    }
}
