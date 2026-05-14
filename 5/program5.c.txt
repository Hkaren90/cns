#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

int determinant(int key[2][2]) {
    return ((key[0][0] * key[1][1]) - (key[0][1] * key[1][0])) % MOD;
}

int mod_inverse(int det) {
    det = (det % MOD + MOD) % MOD;
    for (int i = 1; i < MOD; i++)
        if ((det * i) % MOD == 1) return i;
    return -1;
}

void inverse_key_matrix(int key[2][2], int inv[2][2]) {
    int det = determinant(key);
    int det_inv = mod_inverse(det);
    if (det_inv == -1) {
        printf("Key is not invertible.\n");
        return;
    }
    inv[0][0] = ( key[1][1] * det_inv) % MOD;
    inv[1][1] = ( key[0][0] * det_inv) % MOD;
    inv[0][1] = (-key[0][1] * det_inv) % MOD;
    inv[1][0] = (-key[1][0] * det_inv) % MOD;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv[i][j] = (inv[i][j] + MOD) % MOD;
}

void encrypt_hill(char *text, int key[2][2]) {
    int len = strlen(text);
    if (len % 2) strcat(text, "X");

    for (int i = 0; i < len; i += 2) {
        int v[2] = { text[i] - 'A', text[i + 1] - 'A' };
        int r[2];
        r[0] = (key[0][0] * v[0] + key[0][1] * v[1]) % MOD;
        r[1] = (key[1][0] * v[0] + key[1][1] * v[1]) % MOD;
        text[i]     = r[0] + 'A';
        text[i + 1] = r[1] + 'A';
    }
}

void decrypt_hill(char *text, int key[2][2]) {
    int inv[2][2];
    inverse_key_matrix(key, inv);

    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int v[2] = { text[i] - 'A', text[i + 1] - 'A' };
        int r[2];
        r[0] = (inv[0][0] * v[0] + inv[0][1] * v[1]) % MOD;
        r[1] = (inv[1][0] * v[0] + inv[1][1] * v[1]) % MOD;
        text[i]     = r[0] + 'A';
        text[i + 1] = r[1] + 'A';
    }
}

int main() {
    int key[2][2] = { {6, 24}, {1, 13} };
    char text[100];

    printf("Enter text (uppercase only): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    encrypt_hill(text, key);
    printf("Encrypted text: %s\n", text);

    decrypt_hill(text, key);
    printf("Decrypted text: %s\n", text);

    return 0;
}
