#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/asn_public.h>

int main() {
    FILE* summary = fopen("ectimes.csv", "w");

    // Init
    WC_RNG rng;
    ecc_key key;
    wc_InitRng(&rng);
    wc_ecc_init(&key);

    for(int i = 0; i < 1000000; ++i) {
        // Measure
        clock_t begin = clock();
        wc_ecc_make_key_ex(&rng, 32, &key, ECC_SECP256R1);
        clock_t end = clock();

        // Export
        uint8_t buff[4096];
        uint32_t len = wc_EccKeyToDer(&key, buff, sizeof(buff));

        char fname[64];
        sprintf(fname, "eckeys/%06d.der", i);
        FILE* f = fopen(fname, "wb");
        fwrite(buff, 1, len, f);
        fclose(f);

        long elapsed_secs = (end - begin) * (1000000000 / CLOCKS_PER_SEC);
        fprintf(summary, "%d;e;d;%ld;\n", i, elapsed_secs);
    }

    fclose(summary);
    return 0;
}
