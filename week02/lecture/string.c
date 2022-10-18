#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string word = get_string("Input:  ");
    printf("Output: ");
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        printf("%c", word[i]);
    }
    printf("\n");
}