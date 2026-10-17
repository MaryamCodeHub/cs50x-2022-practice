#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed
                               + image[i][j].rgbtGreen
                               + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;                                                  //Setting all three colors to the calculated average
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;                                          //Save the original color values
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * originalRed                                        //Calculates new sepia colors
                               + 0.769 * originalGreen
                               + 0.189 * originalBlue);

            int sepiaGreen = round(0.349 * originalRed
                                 + 0.686 * originalGreen
                                 + 0.168 * originalBlue);

            int sepiaBlue = round(0.272 * originalRed
                                + 0.534 * originalGreen
                                + 0.131 * originalBlue);

            if (sepiaRed > 255)                                                             //Keeping color values within valid range of 255
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;                                                 // Update the pixel with the new colors
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int opposite = width - 1 - j;                                                   // Find the pixel on the opposite side
            RGBTRIPLE temp = image[i][j];                                                   // Save the current pixel temporarily
            image[i][j] = image[i][opposite];                                               // Swap the two pixels
            image[i][opposite] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];                                                         //Preserve original pixels before applying blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)                                                     //Visits every pixel
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)                                            //Visit the surrounding 3-by-3 area
            {
                for (int dj = -1; dj <= 1; dj++)                                        //Check the neighboring columns
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni < 0 || ni >= height ||                                      //Skip positions outside the image
                        nj < 0 || nj >= width)
                    {
                        continue;
                    }
                    red += copy[ni][nj].rgbtRed;                                       //Add the original color values
                    green += copy[ni][nj].rgbtGreen;
                    blue += copy[ni][nj].rgbtBlue;
                    count++;
                }
            }
            image[i][j].rgbtRed = round((float) red / count);                          //Average the valid neighbors for each color channel
            image[i][j].rgbtGreen = round((float) green / count);
            image[i][j].rgbtBlue = round((float) blue / count);
        }
    }
}

