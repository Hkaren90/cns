#include <stdio.h>

int P10[]    = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[]     = {6, 3, 7, 4, 8, 5, 10, 9};
int IP[]     = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[]     = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[]     = {2, 4, 3, 1};

int S0[4][4] = { {1,0,3,2}, {3,2,1,0}, {0,2,1,3}, {3,1,3,2} };
int S1[4][4] = { {0,1,2,3}, {2,0,1,3}, {3,0,1,2}, {2,1,0,3} };

int permute(int input, int *table, int size) {
    int output = 0;
    for (int i = 0; i < size; i++) {
        output <<= 1;
        output |= (input >> (10 - table[i])) & 1;
    }
    return output;
}

void generate_keys(int key, int *K1, int *K2) {
    key = permute(key, P10, 10);
    int left = (key >> 5) & 0x1F, right = key & 0x1F;

    left  = ((left << 1) & 0x1F) | (left >> 4);
    right = ((right << 1) & 0x1F) | (right >> 4);
    *K1   = permute((left << 5) | right, P8, 8);

    left  = ((left << 2) & 0x1F) | (left >> 3);
    right = ((right << 2) & 0x1F) | (right >> 3);
    *K2   = permute((left << 5) | right, P8, 8);
}

int s_box_substitution(int input, int S[4][4]) {
    int row = ((input & 0x8) >> 2) | (input & 0x1);
    int col = (input >> 1) & 0x3;
    return S[row][col];
}

int feistel(int right, int subkey) {
    int expanded   = permute(right, EP, 8);
    int xored      = expanded ^ subkey;
    int left_sbox  = s_box_substitution((xored >> 4) & 0xF, S0);
    int right_sbox = s_box_substitution(xored & 0xF, S1);
    int output     = (left_sbox << 2) | right_sbox;
    return permute(output, P4, 4);
}

int s_des(int plaintext, int key, int mode) {
    int K1, K2;
    generate_keys(key, &K1, &K2);
    if (mode == 0) { int tmp = K1; K1 = K2; K2 = tmp; }

    int permuted = permute(plaintext, IP, 8);
    int left = (permuted >> 4) & 0xF, right = permuted & 0xF;

    left ^= feistel(right, K1);
    left ^= feistel(right, K2);

    return permute((left << 4) | right, IP_INV, 8);
}

int main() {
    int plaintext = 0b10101010;
    int key       = 0b1010000010;

    printf("Original : %02X\n", plaintext);
    int encrypted = s_des(plaintext, key, 1);
    printf("Encrypted: %02X\n", encrypted);
    int decrypted = s_des(encrypted, key, 0);
    printf("Decrypted: %02X\n", decrypted);

    return 0;
}
