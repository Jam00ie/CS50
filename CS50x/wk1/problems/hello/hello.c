#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask for name
    string name = get_string("What's your name? ");
    // Print name
    printf("hello, %s\n", name);
}