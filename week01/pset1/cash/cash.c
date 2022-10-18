#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int n;
    do
    {
        n = get_int("How many cents the custom has owed? ");
    }
    while (n < 0);
    return n;
}

int calculate_quarters(int cents)
{
    int quarters = 25;
    int n = 0;
    while (quarters <= cents)
    {
        quarters += 25;
        n++;
    }
    return n;
}

int calculate_dimes(int cents)
{
    int dimes = 10;
    int n = 0;
    while (dimes <= cents)
    {
        dimes += 10;
        n++;
    }
    return n;
}

int calculate_nickels(int cents)
{
    int nickels = 5;
    int n = 0;
    while (nickels <= cents)
    {
        nickels += 5;
        n++;
    }
    return n;
}

int calculate_pennies(int cents)
{
    int pennies = 1;
    int n = 0;
    while (pennies <= cents)
    {
        pennies += 1;
        n++;
    }
    return n;
}