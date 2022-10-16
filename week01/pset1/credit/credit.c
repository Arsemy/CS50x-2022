#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long sixteen_decimal = 1000000000000000;
    long fifteen_decimal = 100000000000000;
    long thirteen_decimal = 1000000000000;

    long n = get_long("Number: ");

    int d[16];
    d[0] = n % 10;
    d[1] = (n % 100) / 10 * 2;
    d[2] = (n % 1000) / 100;
    d[3] = (n % 10000) / 1000 * 2;
    d[4] = (n % 100000) / 10000;
    d[5] = (n % 1000000) / 100000 * 2;
    d[6] = (n % 10000000) / 1000000;
    d[7] = (n % 100000000) / 10000000 * 2;
    d[8] = (n % 1000000000) / 100000000;
    d[9] = (n % 10000000000) / 1000000000 * 2;
    d[10] = (n % 100000000000) / 10000000000;
    d[11] = (n % 1000000000000) / 100000000000 * 2;
    d[12] = (n % 10000000000000) / 1000000000000;
    d[13] = (n % 100000000000000) / 10000000000000 * 2;
    d[14] = (n % 1000000000000000) / 100000000000000;
    d[15] = (n % 10000000000000000) / 1000000000000000 * 2;

    int d1_1 = d[1] % 10;
    int d1_2 = d[1] / 10;
    int d3_1 = d[3] % 10;
    int d3_2 = d[3] / 10;
    int d5_1 = d[5] % 10;
    int d5_2 = d[5] / 10;
    int d7_1 = d[7] % 10;
    int d7_2 = d[7] / 10;
    int d9_1 = d[9] % 10;
    int d9_2 = d[9] / 10;
    int d11_1 = d[11] % 10;
    int d11_2 = d[11] / 10;
    int d13_1 = d[13] % 10;
    int d13_2 = d[13] / 10;
    int d15_1 = d[15] % 10;
    int d15_2 = d[15] / 10;
    
    int validation = (d[0] + d1_1 + d1_2 + d[2] + d3_1 + d3_2 + d[4] + d5_1 + d5_2 + d[6] + d7_1 + d7_2 + d[8] + d9_1 + d9_2 + d[10]
                      + d11_1 + d11_2 + d[12] + d13_1 + d13_2 + d[14] + d15_1 + d15_2);
    printf("%i\n", validation); 
    
    if (validation % 10 == 0)
    {
        if (n >= sixteen_decimal && n < sixteen_decimal * 10)
        {
            int result = n / (sixteen_decimal / 10);

            if (result == 51 || result == 52 || result == 53 || result == 54 || result == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (result / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (n >= fifteen_decimal && n < fifteen_decimal * 10)
        {
            int result = n / (fifteen_decimal / 10);

            if (result == 34 || result == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (n >= thirteen_decimal && n < thirteen_decimal * 10)
        {
            int result = n / thirteen_decimal;

            if (result == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}