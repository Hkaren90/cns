#include <stdio.h>

void linear_congruential_generator(int seed, int a, int c, int m, int n) {
    int X = seed;
    printf("Generated Pseudo-Random Numbers:\n");
    for (int i = 0; i < n; i++) {
        X = (a * X + c) % m; 
        printf("%d ", X);
    }
    printf("\n");
}

int main() {
    int seed = 7; 
    int a    = 5; 
    int c    = 3;
    int m    = 16; 
    int n    = 10; 

    printf("Linear Congruential Generator (LCG) Example:\n");
    linear_congruential_generator(seed, a, c, m, n);

    return 0;
}
