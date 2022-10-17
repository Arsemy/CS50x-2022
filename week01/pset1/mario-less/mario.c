#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    int n = 1;
    for (int i = 0; i < h; i++)
    {
        for (int i = 0; i < h - n; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < n; i++)
        {
            printf("#");
        }
        printf("\n");
        n++;
    }
}