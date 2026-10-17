#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = get_int("Enter the pyramid height: ");                     //Input logic

    while(h < 1 || h > 8)                                              // Implementing input checks
    {
        h = get_int("Enter the pyramid height between 1 and 8 inclusive: ");
    }

    for (int i = 0; i < h; i++)                                        // Outer loop for rows
    {
        for (int j = 0; j < h - 1 - i; j++)                            // first inner loop for spaces
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)                                // this loop is for printing hashes
        {
            printf("#");
        }

        printf("\n");
    }
}
