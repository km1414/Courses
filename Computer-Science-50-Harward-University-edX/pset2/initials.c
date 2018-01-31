#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // gets full namegrom user
    string name = get_string();

    // prints first letter of first name
    if (isalpha(name[0]))
    {
        printf("%c", toupper(name[0]));
    }


    // iteartes over whole name
    for (int i = 1, l = strlen(name); i < l; i ++)
    {

        // prints first letter after spaces
        if (isspace(name[i - 1]) && isalpha(name[i]))
        {
            printf("%c", toupper(name[i]));
        }
    }

    printf("\n");
}