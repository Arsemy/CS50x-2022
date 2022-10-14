#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    int hash = 1;

    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n - hash; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < hash; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < hash; i++)
        {
            printf("#");
        }
        printf("\n");
        hash++; 
    }

}