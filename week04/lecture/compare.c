#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *s = get_string("string 1: ");
    char *t = get_string("string 2: ");

    printf("%p\n", s);
    printf("%p\n", t);
}