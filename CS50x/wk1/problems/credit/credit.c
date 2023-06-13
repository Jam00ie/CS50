#include <cs50.h>
#include <stdio.h>
#include <string.h>

long askNumber(void);
string testResults(long n);
bool isCorrectLength(int l);
bool passedLuhn(char *b, int l);
string cardType(char *b, int l);

int main(void)
{
    long n = askNumber();
    printf("%s\n", testResults(n));
}

long askNumber(void)
{
    long n = get_long("Number: ");
    return n;
}

string testResults(long n)
{
    char b[20];
    int l = sprintf(b, "%li", n);

    if (!isCorrectLength(l))
    {
        return "INVALID";
    }
    else if (!passedLuhn(b, l))
    {
        return "INVALID";
    }
    else
    {
        return cardType(b, l);
    }
}

bool isCorrectLength(int l)
{
    if (l == 13 || l == 15 || l == 16)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool passedLuhn(char *b, int l)
{
    int x = 0;
    int y = 0;
    for (int i = l; i > -1; i = i - 2)
    {
        // if every other digit starting with second to last digit
        if ((b[i] - '0') > 0)
        {
            // multiply by two and add digits of the product
            char arr[3];
            int digits = sprintf(arr, "%i", ((b[i] - '0') * 2));
            if (digits > 1)
            {
                x = x + ((arr[0] - '0') + (arr[1] - '0'));
            }
            else
            {
                x = x + (arr[0] - '0');
            }
        }
        // for digits not multiplied by two
        if ((b[i - 1] - '0') > 0)
        {
            y = y + (b[i - 1] - '0');
        }
    }
    if ((x + y) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string cardType(char *b, int l)
{
    if (l == 15 && (b[0] - '0') == 3)
    {
        if ((b[1] - '0') == 4 || (b[1] - '0') == 7)
        {
            return "AMEX";
        }
        else
        {
            return "INVALID";
        }
    }
    else if ((b[0] - '0') == 4)
    {
        if (l == 13 || l == 16)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (l == 16 && (b[0] - '0') == 5)
    {
        if ((b[1] - '0') > 0 && (b[1] - '0') < 6)
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}