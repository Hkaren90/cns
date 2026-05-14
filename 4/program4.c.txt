#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
char playfairMatrix[SIZE][SIZE];

void prepare_key(const char *key, char *processedKey) {
    int seen[26] = {0}, index = 0;
    for (int i = 0; key[i]; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !seen[ch - 'A']) {
            seen[ch - 'A'] = 1;
            processedKey[index++] = ch;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!seen[ch - 'A']) processedKey[index++] = ch;
    }
    processedKey[index] = '\0';
}

void generate_matrix(const char *processedKey) {
    int index = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            playfairMatrix[i][j] = processedKey[index++];
}

void find_position(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (playfairMatrix[i][j] == ch) {
                *row = i; *col = j; return;
            }
}

void process_text(const char *text, char *processedText) {
    int len = strlen(text), index = 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(text[i])) continue;
        char ch = toupper(text[i] == 'J' ? 'I' : text[i]);
        processedText[index++] = ch;
        if (index > 1 && processedText[index - 1] == processedText[index - 2]) {
            processedText[index - 1] = 'X';
            processedText[index++] = ch;
        }
    }
    if (index % 2) processedText[index++] = 'X';
    processedText[index] = '\0';
}

void encrypt_playfair(char *text) {
    for (int i = 0; text[i]; i += 2) {
        int r1, c1, r2, c2;
        find_position(text[i], &r1, &c1);
        find_position(text[i + 1], &r2, &c2);
        if (r1 == r2) {
            text[i]     = playfairMatrix[r1][(c1 + 1) % SIZE];
            text[i + 1] = playfairMatrix[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) {
            text[i]     = playfairMatrix[(r1 + 1) % SIZE][c1];
            text[i + 1] = playfairMatrix[(r2 + 1) % SIZE][c2];
        } else {
            text[i]     = playfairMatrix[r1][c2];
            text[i + 1] = playfairMatrix[r2][c1];
        }
    }
}

void decrypt_playfair(char *text) {
    for (int i = 0; text[i]; i += 2) {
        int r1, c1, r2, c2;
        find_position(text[i], &r1, &c1);
        find_position(text[i + 1], &r2, &c2);
        if (r1 == r2) {
            text[i]     = playfairMatrix[r1][(c1 - 1 + SIZE) % SIZE];
            text[i + 1] = playfairMatrix[r2][(c2 - 1 + SIZE) % SIZE];
        } else if (c1 == c2) {
            text[i]     = playfairMatrix[(r1 - 1 + SIZE) % SIZE][c1];
            text[i + 1] = playfairMatrix[(r2 - 1 + SIZE) % SIZE][c2];
        } else {
            text[i]     = playfairMatrix[r1][c2];
            text[i + 1] = playfairMatrix[r2][c1];
        }
    }
}

int main() {
    char key[100], text[100], processedKey[26], processedText[100];

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    prepare_key(key, processedKey);
    generate_matrix(processedKey);

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    process_text(text, processedText);

    encrypt_playfair(processedText);
    printf("Encrypted text: %s\n", processedText);

    decrypt_playfair(processedText);
    printf("Decrypted text: %s\n", processedText);

    return 0;
}
