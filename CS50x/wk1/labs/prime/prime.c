#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    // check if number is 0 or 1
    if (number <= 1)
    {
        return false;
    }
    // check if number is 2, 3, or divisible by either
    else if (number % 2 == 0 || number % 3 == 0)
    {
        // return true if number is 2 or 3
        if (number == 2 || number == 3)
        {
            return true;
        }
        // return false if divisible by 2 or 3
        else
        {
            return false;
        }
    }
    else
    {
        // iterate from 5 to sqrt(number) and check if i or i+2 divides number
        for (int i = 5; i * i <= number; i = i + 6)
        {
            if (number % i == 0 || number % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }
}
