#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generate_key(const char *text, const char *key, char *new_key) {
    int text_len = strlen(text), key_len = strlen(key);
    for (int i = 0, j = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            new_key[i] = key[j % key_len];
            j++;
        } else {
            new_key[i] = text[i];
        }
    }
    new_key[text_len] = '\0';
}
void encrypt_vigenere(char *text, const char *key) {
    char new_key[100];
    generate_key(text, key, new_key);

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(new_key[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + (new_key[i] - key_base)) % 26 + base;
        }
    }
}
void decrypt_vigenere(char *text, const char *key) {
    char new_key[100];
    generate_key(text, key, new_key);

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(new_key[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - (new_key[i] - key_base) + 26) % 26 + base;
        }
    }
}
int main() {
    char text[100], key[100];
    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    encrypt_vigenere(text, key);
    printf("Encrypted text: %s\n", text);
    decrypt_vigenere(text, key);
    printf("Decrypted text: %s\n", text);
    return 0;
}
