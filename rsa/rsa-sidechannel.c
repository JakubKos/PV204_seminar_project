#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/rsa.h>

#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/asn_public.h>

#define PRNG_NORMAL 0
#define PRNG_0xFFFF 1
#define PRNG_0x00FF 2
#define PRNG_0xAAAA 3
#define PRNG_0x8000 4

#define DATA_NORMAL 0
#define DATA_0xFFFF 1
#define DATA_0x00FF 2
#define DATA_0xAAAA 3
#define DATA_0x8000 4
#define DATA_0x0000 5

int main(int argc, char** argv) {
    int prng = 0;
    int data = 0;
    if(argc == 3) {
        prng = *argv[1] - '0';
        data = *argv[2] - '0';
    }

    byte in[256];
    byte out[128];
    word32 outLen = 128;
    word32 inLen = 256;

    FILE* r;
    if(prng != PRNG_NORMAL) {
        setenv("CUSTOM_RNG", "1", 0);
        r = fopen("/tmp/random", "wb");
    }

    switch(prng) {
        case PRNG_0xFFFF: fputc(0xff, r); break;
        case PRNG_0x00FF: fputc(0x00, r); fputc(0xff, r); break;
        case PRNG_0xAAAA: fputc(0xaa, r); break;
        case PRNG_0x8000: fputc(0x80, r); fputc(0x00, r); break;
    }

    if(prng != PRNG_NORMAL) {
        fclose(r);
    }

    for(int i = 0; i < 128; i += 2) {
        switch(data) {
            case DATA_NORMAL: in[i] = i; in[i+1] = i+1; break;
            case DATA_0xFFFF: in[i] = 0xff; in[i+1] = 0xff; break;
            case DATA_0x00FF: in[i] = 0x00; in[i+1] = 0xff; break;
            case DATA_0x8000: in[i] = 0x80; in[i+1] = 0x00; break;
            case DATA_0x0000: in[i] = 0x00; in[i+1] = 0x00; break;
        }
    }

    char buffer[256];
    sprintf(buffer, "prng%ddata%dsign.txt", prng, data);
    FILE* fsign = fopen(buffer, "w");

    sprintf(buffer, "prng%ddata%denc.txt", prng, data);
    FILE* fenc = fopen(buffer, "w");

    sprintf(buffer, "prng%ddata%ddec.txt", prng, data);
    FILE* fdec = fopen(buffer, "w");

    sprintf(buffer, "prng%ddata%ddir.txt", prng, data);
    FILE* fdirenc = fopen(buffer, "w");

    sprintf(buffer, "prng%ddata%ddir.txt", prng, data);
    FILE* fdirdec = fopen(buffer, "w");

    WC_RNG rng;
    wc_InitRng(&rng);

    RsaKey key;
    wc_InitRsaKey(&key, NULL);
    wc_MakeRsaKey(&key, 2048, 65537, &rng);

    // SIGNING
    for(int i = 0; i < 1000; ++i) {
        clock_t begin = clock();
        if(wc_RsaSSL_Sign(in, inLen, out, outLen, &key, &rng) != 0)
            return 1;
        clock_t end = clock();
        long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
        fprintf(fsign, "%ld\n", elapsed_microsecs);
    }

    // ENCRYPT/DECRYPT
    for(int i = 0; i < 1000; ++i) {
        {
            clock_t begin = clock();
            if(wc_RsaPublicEncrypt(in, inLen, out, outLen, &key, &rng) != 0)
                return 2;
            clock_t end = clock();
            long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
            fprintf(fenc, "%ld\n", elapsed_microsecs);
        }

        {
            clock_t begin = clock();
            if(wc_RsaPrivateDecrypt(out, outLen, in, inLen, &key) != 0)
                return 2;
            clock_t end = clock();
            long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
            fprintf(fdec, "%ld\n", elapsed_microsecs);
        }
    }

    // ENCRYPT/DECRYPT without padding
    for(int i = 0; i < 1000; ++i) {
        {
            clock_t begin = clock();
            if(wc_RsaDirect(in, inLen, out, &outLen, &key, 2, &rng) != 0)
                return 2;
            clock_t end = clock();
            long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
            fprintf(fdirenc, "%ld\n", elapsed_microsecs);
        }

        {
            clock_t begin = clock();
            if(wc_RsaDirect(out, outLen, in, &inLen, &key, 3, &rng) != 0)
                return 2;
            clock_t end = clock();
            long elapsed_microsecs = (end - begin) * (1000000 / CLOCKS_PER_SEC);
            fprintf(fdirdec, "%ld\n", elapsed_microsecs);
        }
    }

    fclose(fsign);
    fclose(fenc);
    fclose(fdec);
    fclose(fdirenc);
    fclose(fdirdec);
    return 0;
}

