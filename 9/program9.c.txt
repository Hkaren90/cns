#include <stdio.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
void blum_blum_shub(long long seed, long long p, long long q, int count) {
    long long n = p * q;
    long long X = (seed * seed) % n;

    printf("Generated Pseudo-Random Numbers:\n");
    for (int i = 0; i < count; i++) {
        X = mod_exp(X, 2, n); 
        printf("%lld ", X % 256); 
    }
    printf("\n");
}

int main() {
    long long p = 11, q = 19; 
    long long seed = 7;
    int count = 10; 

    printf("Blum Blum Shub (BBS) PRNG Example:\n");
    blum_blum_shub(seed, p, q, count);

    return 0;
}
