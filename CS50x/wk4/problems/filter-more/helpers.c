#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp;
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        printf("Not enough memory to store temp.\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            LONG tempBlue = 0;
            LONG tempGreen = 0;
            LONG tempRed = 0;
            BYTE validPixels = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int hPosition = i - (1 - k);
                    int wPosition = j - (1 - l);
                    if (hPosition > -1 && wPosition > -1 && hPosition < height && wPosition < width)
                    {
                        tempBlue += image[hPosition][wPosition].rgbtBlue;
                        tempGreen += image[hPosition][wPosition].rgbtGreen;
                        tempRed += image[hPosition][wPosition].rgbtRed;
                        validPixels++;
                    }
                }
            }
            if (validPixels > 0)
            {
                temp[i][j].rgbtBlue = round(tempBlue / (float) validPixels);
                temp[i][j].rgbtGreen = round(tempGreen / (float) validPixels);
                temp[i][j].rgbtRed = round(tempRed / (float) validPixels);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    free(temp);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        printf("Not enough memory to store temp.\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            LONG GyBlue = 0;
            LONG GyGreen = 0;
            LONG GyRed = 0;
            LONG GxBlue = 0;
            LONG GxGreen = 0;
            LONG GxRed = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int hPosition = i - (1 - k);
                    int wPosition = j - (1 - l);
                    if (hPosition > -1 && wPosition > -1 && hPosition < height && wPosition < width)
                    {
                        LONG tempBlue = image[hPosition][wPosition].rgbtBlue;
                        LONG tempGreen = image[hPosition][wPosition].rgbtGreen;
                        LONG tempRed = image[hPosition][wPosition].rgbtRed;

                        if (l == 1)
                        {
                            GyBlue += tempBlue * (-1 + k) * 2;
                            GyGreen += tempGreen * (-1 + k) * 2;
                            GyRed += tempRed * (-1 + k) * 2;
                        }
                        else
                        {
                            GyBlue += tempBlue * (-1 + k);
                            GyGreen += tempGreen * (-1 + k);
                            GyRed += tempRed * (-1 + k);
                        }
                        if (k == 1)
                        {
                            GxBlue += tempBlue * (-1 + l) * 2;
                            GxGreen += tempGreen * (-1 + l) * 2;
                            GxRed += tempRed * (-1 + l) * 2;
                        }
                        else
                        {
                            GxBlue += tempBlue * (-1 + l);
                            GxGreen += tempGreen * (-1 + l);
                            GxRed += tempRed * (-1 + l);
                        }
                    }
                }
            }
            LONG blue = round(sqrt(pow(((float) GxBlue), 2) + pow(GyBlue, 2)));
            LONG green = round(sqrt(pow(((float) GxGreen), 2) + pow(GyGreen, 2)));
            LONG red = round(sqrt(pow(((float) GxRed), 2) + pow(GyRed, 2)));
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtRed = red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    free(temp);
    return;
}