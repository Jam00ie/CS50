#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    int year;
    int new;
    int dead;
    for (year = 0; start < end; year++)
    {
        new = start / 3;
        dead = start / 4;
        start = start + new - dead;
    }
    // TODO: Print number of years
    printf("Years: %i\n", year);
}
