#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int n = get_int("int: ");

    printf("%i\n", collatz(n));
}

int collatz(int n)
{
    //recursion base case
    if (n == 1)
        return 0;

    //even
    if (n % 2 == 0)
    {
        return 1 + collatz(n / 2);
    }
    //odd
    else
    {
        return 1 + collatz(3 * n + 1);
    }
}