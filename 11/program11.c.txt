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

int main() {
    long long p = 23;
    long long g = 5;

    long long a = 6;
    long long b = 15;

    long long A = mod_exp(g, a, p);
    long long B = mod_exp(g, b, p);

    printf("Public prime (p): %lld\n", p);
    printf("Public base (g): %lld\n", g);
    printf("Alice's Private Key: %lld\n", a);
    printf("Bob's Private Key: %lld\n", b);
    printf("Alice's Public Key (A): %lld\n", A);
    printf("Bob's Public Key (B): %lld\n", B);

    long long alice_secret = mod_exp(B, a, p);
    long long bob_secret   = mod_exp(A, b, p);

    printf("Alice's Computed Secret Key: %lld\n", alice_secret);
    printf("Bob's Computed Secret Key: %lld\n", bob_secret);

    return 0;
}
