#include <stdio.h>
#include <string.h>

#define MAX 100

void create_matrix(char *text, char matrix[MAX][MAX], int rows, int cols) {
    int len = strlen(text), idx = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = (idx < len) ? text[idx++] : 'X';
}

void encrypt_transposition(char *text, int key[], int key_len) {
    int rows = (strlen(text) + key_len - 1) / key_len;
    char matrix[MAX][MAX];
    create_matrix(text, matrix, rows, key_len);

    printf("Encrypted Text: ");
    for (int i = 0; i < key_len; i++) {
        int col = key[i] - 1;
        for (int j = 0; j < rows; j++)
            printf("%c", matrix[j][col]);
    }
    printf("\n");
}

void decrypt_transposition(char *cipher, int key[], int key_len) {
    int len = strlen(cipher), rows = len / key_len;
    char matrix[MAX][MAX];
    int idx = 0;

    for (int i = 0; i < key_len; i++) {
        int col = key[i] - 1;
        for (int j = 0; j < rows; j++)
            matrix[j][col] = cipher[idx++];
    }

    printf("Decrypted Text: ");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key_len; j++)
            printf("%c", matrix[i][j]);
    printf("\n");
}

void encrypt_double_transposition(char *text, int key1[], int key2[], int key_len) {
    printf("After First Transposition:\n");
    encrypt_transposition(text, key1, key_len);
    printf("After Second Transposition:\n");
    encrypt_transposition(text, key2, key_len);
}

void decrypt_double_transposition(char *cipher, int key1[], int key2[], int key_len) {
    printf("After First Decryption:\n");
    decrypt_transposition(cipher, key2, key_len);
    printf("After Second Decryption:\n");
    decrypt_transposition(cipher, key1, key_len);
}

int main() {
    char text[MAX];
    int key1[] = {3, 1, 4, 2};
    int key2[] = {2, 4, 1, 3};
    int key_len = 4;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("\n** Single Transposition Encryption **\n");
    encrypt_transposition(text, key1, key_len);

    printf("\n** Single Transposition Decryption **\n");
    decrypt_transposition(text, key1, key_len);

    printf("\n** Double Transposition Encryption **\n");
    encrypt_double_transposition(text, key1, key2, key_len);

    printf("\n** Double Transposition Decryption **\n");
    decrypt_double_transposition(text, key1, key2, key_len);

    return 0;
}
