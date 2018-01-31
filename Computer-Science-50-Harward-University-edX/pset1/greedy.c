#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int cents, coins = 0;

    // gets input from user until input fits
    do
    {
        dollars = get_float("O hai! How much change is owed? ");
    }
    while (dollars < 0);

    // converting dollars to cents
    cents = round(dollars * 100);

    // checking whether is possible to give quarters
    while (cents - 25 >= 0)
    {
        cents -= 25;
        coins += 1;
    }

    // checking whether is possible to give dimes
    while (cents - 10 >= 0)
    {
        cents -= 10;
        coins += 1;
    }

    // checking whether is possible to give nickels
    while (cents - 5 >= 0)
    {
        cents -= 5;
        coins += 1;
    }

    // checking whether is possible to give pennies
    while (cents - 1 >= 0)
    {
        cents -= 1;
        coins += 1;
    }

    // prints whole amount of coins
    printf("%i\n", coins);

}
