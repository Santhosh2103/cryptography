#include <stdio.h>
#include <string.h>

void caesarCipher(char text[], int k) {
    for (int i = 0; i < strlen(text); i++) {
        char ch = text[i];

        if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + k) % 26 + 'A'; 
        }
     
        else if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + k) % 26 + 'a'; 
        }
        text[i] = ch;
    }
}

int main() {
    char text[100];
    int k;


    printf("Enter the text: ");
    gets(text); 
    
    printf("Enter the shift value (k): ");
    scanf("%d", &k);


    caesarCipher(text, k);

    printf("Encrypted text: %s\n", text);

    return 0;
}
