#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// catch a key by a command line argument
// any command line or more than one... error message
// invalid key... error message 
// prompt a "plaintext:" to the user text to be encrypted
// change every letter with the key
int key_length = 26;

int invalidchar(string key);
int duplicatedchar(string key); 
string stringtolower(string key_mix);
string encrypt_text(string text, string key);

int main(int argc, string argv[]) 
{
    if (argc == 2)
    {
        string key = stringtolower(argv[1]);
        int user_key_length = strlen(argv[1]);

        if (user_key_length != key_length || invalidchar(key) == 1 || duplicatedchar(key) == 1)
        {
            printf("Invalid key (needs to be a key with exactly 26 characters and mustn't have numbers, special characters or duplicated characters)\n");
            return 1;
        }

        string text = get_string("plaintext: ");
        string encrypted_text = encrypt_text(text, key);
        printf("ciphertext: %s\n", encrypted_text);
        return 0;
    }
    else 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string stringtolower(string key_mix)
{
    for (int i = 0; i < key_length; i++)
    {
        key_mix[i] = tolower(key_mix[i]);
    }
    return key_mix;
}

int invalidchar(string key)
{
    for (int i = 0; i < key_length; i++)
    {
        if (key[i] < 97 || key[i] > 122)
        {
            return 1;
        }
    }
    return 0;
}

int duplicatedchar(string key)
{
    for (int i = 0; i < key_length; i++)
    {
        for (int ii = 0; ii < key_length - 1; ii++)
        {
            if (key[i] == key[ii] && i != ii)
            {
                return 1;
            }
        }
    }
    return 0;
}

string encrypt_text(string text, string key)
{
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            int n = text[i] - 'a';
            text[i] = key[n];
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            int n = text[i] - 'A';
            text[i] = key[n];
            text[i] = toupper(text[i]);
        }
    }
    return text;
}