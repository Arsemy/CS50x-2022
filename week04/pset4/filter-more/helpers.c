#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //get every
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageTmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0, gxGreen = 0, gxRed = 0;
            int gyBlue = 0, gyGreen = 0, gyRed = 0;

            for (int k = 0; k < 3; k++)
            {
                int a = i - 1 + k;
                for (int l = 0; l < 3; l++)
                {
                    int b = j - 1 + l;
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        if (k == 0)
                        {
                            gxBlue += image[a][b].rgbtBlue * 1 * (l - 1);
                            gxGreen += image[a][b].rgbtGreen * 1 * (l - 1);
                            gxRed += image[a][b].rgbtRed * 1 * (l - 1);
                            
                            if (l == 1)
                            {
                                gyBlue += image[a][b].rgbtBlue * -2;
                                gyGreen += image[a][b].rgbtGreen * -2;
                                gyRed += image[a][b].rgbtRed * -2;
                            }
                            else
                            {
                                gyBlue += image[a][b].rgbtBlue * -1;
                                gyGreen += image[a][b].rgbtGreen * -1;
                                gyRed += image[a][b].rgbtRed * -1;
                            }
                        }
                        else if (k == 1)
                        {
                            gxBlue += image[a][b].rgbtBlue * 2 * (l - 1);
                            gxGreen += image[a][b].rgbtGreen * 2 * (l - 1);
                            gxRed += image[a][b].rgbtRed * 2 * (l - 1);
                            
                        }
                        else if (k == 2)
                        {
                            gxBlue += image[a][b].rgbtBlue * 1 * (l - 1);
                            gxGreen += image[a][b].rgbtGreen * 1 * (l - 1);
                            gxRed += image[a][b].rgbtRed * 1 * (l - 1);
                            
                            if (l == 1)
                            {
                                gyBlue += image[a][b].rgbtBlue * 2;
                                gyGreen += image[a][b].rgbtGreen * 2;
                                gyRed += image[a][b].rgbtRed * 2;
                            }
                            else
                            {
                                gyBlue += image[a][b].rgbtBlue * 1;
                                gyGreen += image[a][b].rgbtGreen * 1;
                                gyRed += image[a][b].rgbtRed * 1;
                            }
                        }
                    }
                }
            }
            int resultBlue = roundf(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
            if(resultBlue > 255)
            {
                resultBlue = 255;
            }
            int resultGreen = roundf(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
            if(resultGreen > 255)
            {
                resultGreen = 255;
            }
            int resultRed = roundf(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
            if(resultRed > 255)
            {
                resultRed = 255;
            }

            imageTmp[i][j].rgbtBlue = resultBlue;
            imageTmp[i][j].rgbtGreen = resultGreen;
            imageTmp[i][j].rgbtRed = resultRed;
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