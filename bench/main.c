#include <stdio.h>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>

WC_RNG rng;

void init() {
    wc_InitRng(&rng);
}

void destroy() {
    wc_FreeRng(&rng);
}

long bench(void(*f)(void), size_t iter) {
    clock_t begin = clock();
    while(iter--) {
        f();
    }
    clock_t end = clock();
    return (end - begin) * (1000000 / CLOCKS_PER_SEC);
}

void summary(char* desc, char* unit, long ms, long data) {
    printf("%-30s [%.2lf %s/s]\n", desc, (data * 1000.0 * 1000) / ms, unit);
}

void RNG_128() {
    byte buff[128];
    wc_RNG_GenerateBlock(&rng, buff, sizeof(buff));
}

int main(int argc, char** argv) {
    init();

    summary("RANDOM by 128B", "MB", bench(RNG_128, 1024*1024), 128);

    destroy();
    return 0;
}
