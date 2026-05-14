#include <stdio.h>
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
int euler_totient(int n) {
    int result = 1;
    for (int i = 2; i < n; i++)
        if (gcd(i, n) == 1) result++;
    return result;
}
long long fermat_mod_inverse(int a, int p) {
    return mod_exp(a, p - 2, p);
}
long long euler_theorem(int a, int n) {
    int phi_n = euler_totient(n);
    return mod_exp(a, phi_n, n);
}
int main() {
    int a = 7, p = 13;
    int n = 10;
    long long fermat_inverse = fermat_mod_inverse(a, p);
    printf("Fermat's Theorem:\n");
    printf("Modular Inverse of %d mod %d: %lld\n\n", a, p, fermat_inverse);
    long long euler_result = euler_theorem(a, n);
    printf("Euler's Theorem:\n");
    printf("%d^f(%d) mod %d = %lld\n", a, n, n, euler_result);
    return 0;
}
