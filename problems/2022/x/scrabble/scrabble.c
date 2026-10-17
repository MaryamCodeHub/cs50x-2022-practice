#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++)                      //Go through every character in the word
    {
        if (isalpha(word[i]))                                   //This checks if the current character is a letter
        {
            word[i] = toupper(word[i]);                         //Converts all the characters in uppercase

            switch (word[i])                                    // Check the letter and add its points
            {
                case 'A':                                       // Checking all the letters worth 1 point together
                case 'E':
                case 'I':
                case 'L':
                case 'N':
                case 'O':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                    score += 1;
                    break;

                case 'D':                                      // These letters are worth 2 point
                case 'G':
                    score += 2;
                    break;

                case 'B':                                     // These letters are worth 3 point
                case 'C':
                case 'M':
                case 'P':
                    score += 3;
                    break;

                case 'F':                                      // These letters are worth 4 point
                case 'H':
                case 'V':
                case 'W':
                case 'Y':
                    score += 4;
                    break;

                case 'K':                                       // This letter is worth 5 point
                    score += 5;
                    break;

                case 'J':                                       // These letters are worth 8 point
                case 'X':
                    score += 8;
                    break;

                case 'Q':                                       // These letters are worth 1o point
                case 'Z':
                    score += 10;
                    break;
            }
        }
    }

    return score;
}
