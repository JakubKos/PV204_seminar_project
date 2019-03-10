#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/rsa.h>

#include <time.h>
#include <stdio.h>
#include <stdint.h>

#define RSA_KEY_SIZE 512
/* #define RSA_KEY_SIZE 1024 */
/* #define RSA_KEY_SIZE 2048 */

int main() {
    RsaKey rsaKey;
    RNG rng;

    byte *buff = NULL;
    word32 len;
    int id;
    int e = 65537;
    FILE* summary = fopen("rsatimes-512.csv", "w");

    /* Init */
    wc_InitRng(&rng);
    wc_InitRsaKey(&rsaKey, NULL);

    int max = 10000;
    if (RSA_KEY_SIZE == 512)
        max = 1000000;

    char fname[64];
    clock_t begin, end;
    for (id = 1; id <= max; ++id) {
        /* Generate key & measuring */
        begin = clock();
        wc_MakeRsaKey(&rsaKey, RSA_KEY_SIZE, e, &rng);
        end = clock();
        long ns = (end - begin) * (1000000000 / CLOCKS_PER_SEC);

        /* Export key data */
        buff = malloc(RSA_KEY_SIZE);
        len = wc_RsaKeyToDer(&rsaKey, buff, RSA_KEY_SIZE);
        printf("RSA key id: %d time: %ld\n", id, ns);

        /* Save data into file */
        sprintf(fname, "keys/%d/%06d.der", RSA_KEY_SIZE, id);
        FILE* key = fopen(fname, "wb");
        fwrite(buff, 1, len, key);
        fclose(key);

        /* Update statistics */
        fprintf(summary, "%d;n;%d;p;q;d;%ld\n", id, e, ns);
    }

    fclose(summary);

    return 0;
}
