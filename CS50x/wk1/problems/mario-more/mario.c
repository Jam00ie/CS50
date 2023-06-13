#include <cs50.h>
#include <stdio.h>

int getHeight(void);
int printPyramid(int height);

int main(void)
{
    printPyramid(getHeight());
}

// Asks for height from user until input is between 1 or 8
int getHeight(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

//prints pyramid
int printPyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        //print whitespaces
        for (int j = 1; j < (height - i); j++)
        {
            printf(" ");
        }
        //print hashtags
        for (int j = -1; j < i; j++)
        {
            printf("#");
        }
        //blank space in the middle
        printf("  ");
        for (int j = -1; j < i; j++)
        {
            printf("#");
        }
        //hastags after space
        printf("\n");
    }
    return 1;
}