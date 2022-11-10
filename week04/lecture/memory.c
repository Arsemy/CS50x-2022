#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3*sizeof(int));
    x[0] = 70;
    x[1] = 71;
    x[2] = 72;
    free(x);
}