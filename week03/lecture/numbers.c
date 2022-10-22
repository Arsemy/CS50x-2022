#include <stdio.h>

int main(void)
{
    int numbers[] = {4, 5, 8, 2, 7, 5, 0};

    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == -1)
        {
            printf("Found\n");
            return 1;
        }
    }
    printf("Not found\n");
    return 0;
}