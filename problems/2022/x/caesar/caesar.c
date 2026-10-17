#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);                                               //checks whether key contains only digits
char rotate(char c, int n);                                                 //rotates a character by the given key

int main(int argc, string argv[])
{
    if (argc != 2)                                                          //need exactly one key from the command line
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (only_digits(argv[1]) == false)                                      //checks whether the key contains only digits
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);                                               //converts the string key into an integer

    string plain_text = get_string("plaintext:  ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plain_text); i++)                          //loops through every character in the plaintext
    {
        printf("%c", rotate(plain_text[i], key));                         //rotates each character and prints it
    }

    printf("\n");
    return 0;
}

char rotate(char c, int n)                                             //rotates a letter and keeps non-letters unchanged
{
    n = n % 26;                                                       //limits the rotation to 0–25

    if (isupper(c))                                                   //checks if the character is uppercase
    {
        return (c - 'A' + n) % 26 + 'A';                              //rotates uppercase letters
    }
    else if (islower(c))                                              //checks if the character is lowercase
    {
        return (c - 'a' + n) % 26 + 'a';                              //rotates lowercase letters
    }
    else
    {
        return c;                                                     //leaves spaces, punctuation, and other characters unchanged
    }
}

bool only_digits(string key)                                              //checks every character in the key
{
    if (strlen(key) == 0)
    {
        return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]))                                             //if the character is a digit, continue checking
        {
        }
        else
        {
            return false;
        }
    }

    return true;
}


