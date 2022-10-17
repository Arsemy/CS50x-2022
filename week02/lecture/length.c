#include <stdio.h>
#include <cs50.h>

int string_length(string na);

int main(void)
{
    string name = get_string("What's your name? ");
    int length = string_length(name);
    printf("Length: %i\n", length);
}

int string_length(string na)
{
    int i = 0;
    while (na[i] != '\0')
    {
        i++;
    }
    return i;
}