/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
#include <stdio.h>
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if n is non-possitive, returns "false"
    if (n <= 0)
    {
        return false;
    }

    // sets indices for searching
    int first = 0, last = n - 1, middle = (first + last) / 2;


    // implements binary search
    while (first <= last)
    {

        // if values match, returns true
        if (values[middle] == value)
        {
            return true;
        }


        else if (value < values[middle])
        {
            last = middle - 1;
        }

        else
        {
            first = middle + 1;
        }

        // resets middle index
        middle = (first + last) / 2;
    }


    // otherwise returns "false"
    return false;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // setting the bigest value of "values"
    int max_value = 65535;

    // making empty list of size "max_value"
    int list[max_value];

    // setting all "list" values to 0
    for (int i = 0; i < max_value; i++)
    {
        list[i] = 0;
    }

    // filling "list" (how many times every value in "values" is repeated
    for (int i = 0; i < n; i++)
    {
        list[values[i]]++;
    }

    // filling "values" with sorted numbers
    for (int i = 0, counter = 0; i < max_value; i++)
    {
        // if "list[i]" > 0, repeats "i" value "list[i]" times in "values"
        for (int j = list[i]; j > 0; j--)
        {
            values[counter] = i;
            counter++;
        }
    }

    return;
}
