#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k, len = strlen(key);

    for (i = 0, k = 0; i < len; i++) {
        if (key[i] != 'j' && dict[key[i] - 'a'] == 0) {
            keyTable[k / SIZE][k % SIZE] = key[i];
            dict[key[i] - 'a'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        
        if (i != 9 && dict[i] == 0) {
            keyTable[k / SIZE][k % SIZE] = 'a' + i;
            k++;
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;

    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            }
            if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

void decrypt(char str[], char keyTable[SIZE][SIZE]) {
    int i, a[4];

    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyTable[a[0]][(a[1] - 1 + SIZE) % SIZE];
            str[i + 1] = keyTable[a[2]][(a[3] - 1 + SIZE) % SIZE];
        } else if (a[1] == a[3]) {
            str[i] = keyTable[(a[0] - 1 + SIZE) % SIZE][a[1]];
            str[i + 1] = keyTable[(a[2] - 1 + SIZE) % SIZE][a[3]];
        } else {
            str[i] = keyTable[a[0]][a[3]];
            str[i + 1] = keyTable[a[2]][a[1]];
        }
    }
}

void prepare(char str[], char preparedStr[]) {
    int i, j;

    for (i = 0, j = 0; i < strlen(str); i++) {
        if (str[i] == 'j') {
            preparedStr[j++] = 'i';
        } else if (isalpha(str[i])) {
            preparedStr[j++] = tolower(str[i]);
        }
    }
    if (j % 2 != 0) {
        preparedStr[j++] = 'x';
    }
    preparedStr[j] = '\0';
}

int main() {
    char key[SIZE * SIZE], keyTable[SIZE][SIZE], str[100], preparedStr[100];

    printf("Enter key: ");
    gets(key);
    printf("Enter ciphertext: ");
    gets(str);

    generateKeyTable(key, keyTable);
    prepare(str, preparedStr);
    decrypt(preparedStr, keyTable);

    printf("Decrypted text: %s\n", preparedStr);

    return 0;
}
