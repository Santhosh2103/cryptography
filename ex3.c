#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int i, j, k = 0;
    int flag[26] = {0};  
    flag['J' - 'A'] = 1; 

    for (i = 0; i < strlen(key); i++) {
        if (isalpha(key[i])) {
            key[i] = toupper(key[i]);
            if (key[i] == 'J') key[i] = 'I';
            if (!flag[key[i] - 'A']) {
                matrix[k / SIZE][k % SIZE] = key[i];
                flag[key[i] - 'A'] = 1;
                k++;
            }
        }
    }

    for (i = 0; i < 26; i++) {
        if (!flag[i]) {
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    int i = 0, row1, col1, row2, col2;

    while (plaintext[i] != '\0') {
        char first = toupper(plaintext[i]);
        char second = toupper(plaintext[i + 1]);

        if (first == 'J') first = 'I';
        if (second == 'J') second = 'I';

        findPosition(matrix, first, &row1, &col1);
        findPosition(matrix, second, &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }

        i += 2;
    }

    ciphertext[i] = '\0';  
}

void preprocessPlaintext(char plaintext[]) {
    int i, j = 0;
    char result[100];

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            result[j] = toupper(plaintext[i]);
            if (result[j] == 'J') result[j] = 'I';
            if (j > 0 && result[j] == result[j - 1]) {
                result[j + 1] = 'X';
                j++;
            }
            j++;
        }
    }

    if (j % 2 != 0) {
        result[j] = 'X';
        j++;
    }

    result[j] = '\0';
    strcpy(plaintext, result);
}

int main() {
    char key[50], plaintext[100], ciphertext[100];
    char matrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;  

   
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;  

    createMatrix(key, matrix);

    preprocessPlaintext(plaintext);

    encrypt(plaintext, matrix, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

