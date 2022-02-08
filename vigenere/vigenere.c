#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check the input data
    if(argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }

    int keyStrlen = strlen(argv[1]);
    string keyCode = argv[1];

    //Getting a string to encrypt
    string text = get_string("plaintext: ");

    unsigned char l = ' ';

    printf("ciphertext: ");

    for(int i = 0, j = 0; i < strlen(text); i++, j++)
    {   
        //If the character belongs to the alphabet
        if((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            l = text[i];

            //If the encryption word is less than the text to be encrypted
            if(j == keyStrlen)
            {
                j = 0;
            }

            //Character encryption
            l = l + keyCode[j] - (islower(keyCode[j]) ? 'a' : 'A');

            //if the character is outside the alphabet
            //the countdown starts from the beginning of the alphabet
            if(l > 'z')
            {
                l = 'a' + (l - 'z' - 1);
            }
            else
            if(l > 'Z' && isupper(text[i]))
            {
                l = 'A' + (l - 'Z' - 1);
            }

            printf("%c", l);
        }

        //if the character does not belong to the alphabet, is displayed in the stream
        else
        {
            printf("%c", text[i]);
            j--;
        }
    }
    printf("\n");
}
