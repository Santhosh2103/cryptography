#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherSequence(const char *keyword, char cipher[ALPHABET_SIZE]) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;


    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            ciphertext[i] = cipher[ch - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    plaintext[i] = 'A' + j; 
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char keyword[100];
    char plaintext[100];

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    char cipher[ALPHABET_SIZE];
    generateCipherSequence(keyword, cipher);

    printf("Cipher Sequence: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");

    char ciphertext[strlen(plaintext) + 1];
    encrypt(plaintext, cipher, ciphertext);
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    char decryptedText[strlen(ciphertext) + 1];
    decrypt(ciphertext, cipher, decryptedText);
    
    printf("Decrypted Text: %s\n", decryptedText);
}
