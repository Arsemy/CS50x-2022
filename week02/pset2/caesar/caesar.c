#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int keyverify(string key);

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //key validation
    string key = argv[1];
    int keyvalid = keyverify(key);

    if (keyvalid == 1)
    {
        printf("Your key is invalid! (try a key with just numbers)");
        return 1;
    }

    //converter
    string text = get_string("plaintext: ");
    int text_length = strlen(text);
    int key_int = atoi(key);
    
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            int letter_th = text[i] - 'a';
            int letter_crypted_th = (letter_th + key_int) % 26;
            text[i] = 'a' + letter_crypted_th;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            int letter_th = text[i] - 'A';
            int letter_crypted_th = (letter_th + key_int) % 26;
            text[i] = 'A' + letter_crypted_th;
        }
    }

    printf("ciphertext: %s\n", text);
    return 0;
}

int keyverify(string key)
{
    int key_strlength = strlen(key);
    for (int i = 0; i < key_strlength; i++)
    {
        if (key[i] < '0' || key[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}