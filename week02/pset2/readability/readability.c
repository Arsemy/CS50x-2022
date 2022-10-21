#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int text_length;

int main(void) 
{
    string text = get_string("Text: ");
    text_length = strlen(text);

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    float grade = 0.0588 * L - 0.296 * S - 15.8;

    if (grade > (int) grade + 0.5)
    {
        grade = (int) grade + 1; 
    }
    else
    {
        grade = (int) grade; 
    }

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) grade);
    }
}

int count_letters(string text)
{
    int n = 0;
    for (int i = 0; i < text_length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    int n = 1;
    for (int i = 0; i <  text_length; i++)
    {
        if (text[i] == ' ')
        {
            n++;
        }
    }
    return n;
}

int count_sentences(string text)
{
    int n = 0;
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }
    return n;
}