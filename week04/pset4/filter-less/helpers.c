#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = ((float)image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            int integer = average;
            float decimal = average - integer;
            if (decimal > 0.5)
            {
                average += 1 - decimal;
                image[i][j].rgbtBlue = average;
                image[i][j].rgbtGreen = average;
                image[i][j].rgbtRed = average;
            }
            else
            {
                image[i][j].rgbtBlue = integer;
                image[i][j].rgbtGreen = integer;
                image[i][j].rgbtRed = integer;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageTmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue = roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            int sepiaGreen = roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaRed = roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            imageTmp[i][j].rgbtBlue = sepiaBlue;
            imageTmp[i][j].rgbtGreen = sepiaGreen;
            imageTmp[i][j].rgbtRed = sepiaRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imageTmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imageTmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imageTmp[i][j].rgbtRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int j = 0;
        RGBTRIPLE tmp;
        while (j < width - j - 1)
        {
            tmp.rgbtBlue = image[i][j].rgbtBlue;
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            tmp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = tmp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = tmp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = tmp.rgbtRed;
            j++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageTmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageBlue = 0;
            int averageGreen = 0;
            int averageRed = 0;
            int number = 0;
            for (int k = 0; k < 3; k++)
            {
                int a = i - 1 + k;
                for (int l = 0; l < 3; l++)
                {
                    int b = j - 1 + l;
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        averageBlue += image[a][b].rgbtBlue;
                        averageGreen += image[a][b].rgbtGreen;
                        averageRed += image[a][b].rgbtRed;
                        number++;
                    }
                }
            }
            averageBlue = roundf((float)averageBlue / number);
            averageGreen = roundf((float)averageGreen / number);
            averageRed = roundf((float)averageRed / number);
            imageTmp[i][j].rgbtBlue = averageBlue;
            imageTmp[i][j].rgbtGreen = averageGreen;
            imageTmp[i][j].rgbtRed = averageRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imageTmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imageTmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imageTmp[i][j].rgbtRed;
        }
    }
    return;
}
