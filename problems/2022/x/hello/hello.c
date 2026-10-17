#include <stdio.h>                                           // This give access to input/output func
#include <cs50.h>                                           // This give access to string type and pre-build get_string function

int main(void)                                                   // This is where the program starts
{
    string name = get_string("Please enter your name: ");       // A string typed variable "name" is defined which stores the value entered by the user.
    printf("Hello, %s!\n", name);                              // Here iam using %s as a placeholderand for the value stored in the "name" variable fo printing
}
