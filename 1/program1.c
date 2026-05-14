#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
char reverse_key[26];

void generate_reverse_key() {
    for (int i = 0; i < 26; i++) {
        reverse_key[key[i] - 'A'] = 'A' + i;
    }
}

void encrypt(char *text) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int index = isupper(text[i]) ? text[i] - 'A' : text[i] - 'a';
            text[i] = isupper(text[i]) ? key[index] : tolower(key[index]);
        }
    }
}
void decrypt(char *text) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int index = isupper(text[i]) ? text[i] - 'A' : text[i] - 'a';
            text[i] = isupper(text[i]) ? reverse_key[index] : tolower(reverse_key[index]);
        }
    }
}
int main() {
    char text[100];
    generate_reverse_key();
    printf("Enter a string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    encrypt(text);
    printf("Encrypted text: %s\n", text);
    decrypt(text);
    printf("Decrypted text: %s\n", text);
    return 0;
}
