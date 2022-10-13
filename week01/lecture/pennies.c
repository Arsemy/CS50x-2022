#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float amount = get_float("Dollar amount: ");
    int pennies = round(amount * 100);
    printf("%i\n", pennies);
}