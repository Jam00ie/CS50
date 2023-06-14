#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool readingLevel(int length, string text);

int main(void)
{
    string text = get_string("Text: \n");
    int length = strlen(text);
    readingLevel(length, text);
}

bool readingLevel(int length, string text)
{
    int words = 0;
    int letters = 0;
    int sentences = 0;
    for (int i = 0; i < length; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            letters++;
        }
        else if (isspace(c))
        {
            words++;
        }
        else if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }
    words++;
    float L = letters / ((float) words / 100);
    float S = sentences / ((float) words / 100);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return false;
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
        return false;
    }
    else
    {
        printf("Grade %i\n", index);
        return true;
    }
}