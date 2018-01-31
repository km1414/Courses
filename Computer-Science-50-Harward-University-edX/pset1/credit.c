#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long number;
    int digit, digit_prev, iter = 0, sum = 0;

    // getting card number

    number = get_long_long("Number: ");

    // adding digits acording to the rules
    while (number > 0)
    {
        digit_prev = digit;
        digit = number % 10;

        // every other digit by 2, starting with the number’s last digit
        if (iter % 2 == 0)
        {
            sum = sum + digit;
        }

        // every other digit by 2, starting with the number’s second-to-last digit
        if (iter % 2 == 1)
        {
            // first digit of the product
            sum = sum + 2 * digit % 10;
            // second digit of the product
            sum = sum + (2 * digit - 2 * digit % 10) / 10;
        }

        // shortening the number
        number = (number - digit) / 10;
        iter += 1;
    }

    // checking all conditions
    if (sum % 10 == 0 && digit == 3 && (digit_prev == 4 || digit_prev == 7) && iter == 15)
    {
        printf("AMEX\n");
    }

    else if (sum % 10 == 0 && digit == 5 && digit_prev >= 1 && digit_prev <= 5 && iter == 16)
    {
        printf("MASTERCARD\n");
    }

    else if (sum % 10 == 0 && digit == 4 && (iter == 13 || iter == 16))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }

}
