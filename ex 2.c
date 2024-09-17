#include <stdio.h>
#include <string.h>

void encrypt(char plaintext[], char key[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            
            plaintext[i] = key[plaintext[i] - 'A'];
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
        	
            plaintext[i] = key[plaintext[i] - 'a'] + ('a' - 'A');
        }
    }
}

int main() {

    char key[26] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    
    char plaintext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    encrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

