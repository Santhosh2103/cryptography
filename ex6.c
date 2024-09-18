#include <stdio.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

void decryptAffine(char *ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int y = toupper(ciphertext[i]) - 'A';
            int x = (a_inv * (y - b + 26)) % 26;
            printf("%c", x + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "LBWVW";
    int a, b;
    a = 1; 
    b = 13;

    decryptAffine(ciphertext, a, b);
    return 0;
}
