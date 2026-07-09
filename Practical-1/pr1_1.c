/*A. Write a C program to perform encryption and decryption of a given text using Caesar Cipher algorithm and analyze the time and space complexity of the encryption and decryption processes.*/ 

/*Encryption procedure: C=E(P)=(P+K) mod 26 
Decryption Procedure: P=D(C)=(C-K) mod 26*/

#include <stdio.h>
#include <string.h>

void encrypt(char *text, int key) {
    for (size_t i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (ch >= 'a' && ch <= 'z')
            text[i] = (char)(((ch - 'a' + key) % 26) + 'a');
        else if (ch >= 'A' && ch <= 'Z')
            text[i] = (char)(((ch - 'A' + key) % 26) + 'A');
    }
}

void decrypt(char *text, int key) {
    for (size_t i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (ch >= 'a' && ch <= 'z')
            text[i] = (char)(((ch - 'a' - key + 26) % 26) + 'a');
        else if (ch >= 'A' && ch <= 'Z')
            text[i] = (char)(((ch - 'A' - key + 26) % 26) + 'A');
    }
}

int main() {
    char plaintext[1024];
    int key;

    printf("Enter plaintext: ");
    if (!fgets(plaintext, sizeof plaintext, stdin))
        return 1;

    size_t len = strlen(plaintext);
    if (len && plaintext[len - 1] == '\n')
        plaintext[len - 1] = '\0';

    printf("Enter key (shift value): ");
    if (scanf("%d", &key) != 1)
        return 1;

    char cipher[1024];
    char decrypted[1024];

    strcpy(cipher, plaintext);
    encrypt(cipher, key);
    printf("\nEncrypted text: %s\n", cipher);

    strcpy(decrypted, cipher);
    decrypt(decrypted, key);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

