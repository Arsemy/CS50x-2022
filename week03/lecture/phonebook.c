#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Ashley";
    people[0].number = "+9-999-999-9999";

    people[1].name = "Leon";
    people[1].number = "+8-888-888-8888";

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "Leon") == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    return 1;
}