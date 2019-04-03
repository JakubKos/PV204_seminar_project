#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/asn_public.h>

int main(int argc, char** argv) {

    byte in[256];
    byte out[256];
    byte bk[256];
    byte sig[256];
    word32 outLen = sizeof(out);
    word32 bkLen = sizeof(bk);
    word32 sigLen = sizeof(sig);

    FILE* fenc = fopen("heatMSBenc.csv", "w");
    FILE* fdec = fopen("heatMSBdec.csv", "w");
    FILE* fsig = fopen("heatMSBsig.csv", "w");

    for(int i = 0; i < 256; ++i)
        in[i] = i;

    setenv("CUSTOM_RNG", "1", 0);

    for(int i = 0; i <= 0xff; ++i) {
        FILE* r = fopen("/tmp/random", "wb");
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(0x00, r);
        fputc(i, r);
        for(int i = 0; i < 40; ++i)
            fputc(rand() % 256, r);
        fclose(r);

        WC_RNG rng;
        wc_InitRng(&rng);

        ecc_key keyA;
        wc_ecc_init(&keyA);
        wc_ecc_make_key_ex(&rng, 32, &keyA, ECC_SECP256R1);

        ecc_key keyB;
        wc_ecc_init(&keyB);
        wc_ecc_make_key_ex(&rng, 32, &keyB, ECC_SECP256R1);

        for(int j = 0; j < 1000; ++j) {
            outLen = sizeof(out);
            bkLen = sizeof(bk);
            sigLen = sizeof(sig);
            {
                clock_t begin = clock();
                if(wc_ecc_encrypt(&keyA, &keyB, in, 128, out, &outLen, NULL) != 0)
                    return 1;
                clock_t end = clock();
                long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
                fprintf(fenc, "%d;%ld\n", i, elapsed_microsecs);
            }

            {
                clock_t begin = clock();
                if(wc_ecc_decrypt(&keyB, &keyA, out, outLen, bk, &bkLen, NULL) != 0)
                    return 2;
                clock_t end = clock();
                long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
                fprintf(fdec, "%d;%ld\n", i, elapsed_microsecs);
            }

            {
                clock_t begin = clock();
                if(wc_ecc_sign_hash(in, 32, sig, &sigLen, &rng, &keyA) != 0)
                    return 3;
                clock_t end = clock();
                long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
                fprintf(fsig, "%d;%ld\n", i, elapsed_microsecs);
            }
        }

        printf("%02x DONE!\n", i);
    }

    fclose(fsig);
    fclose(fdec);
    fclose(fenc);
    return 0;
}

