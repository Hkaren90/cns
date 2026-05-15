#include <stdio.h>
#include <ctype.h>

void caesar_cipher(char *text, int shift) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}

void caesar_decipher(char *text, int shift) {
    caesar_cipher(text, 26 - shift);
}

int main() {
    char text[100];
    int shift;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter shift: ");
    scanf("%d", &shift);

    caesar_cipher(text, shift);
    printf("Encrypted: %s", text);

    caesar_decipher(text, shift);
    printf("Decrypted: %s", text);

    return 0;
}
