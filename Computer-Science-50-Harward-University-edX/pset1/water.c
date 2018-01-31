#include <stdio.h>
#include <cs50.h>


int main(void)
{
    // gets input from user
    int minutes = get_int("Minutes: ");

    // prints the answer
    printf("Bottles: %i\n", minutes * 12);
}