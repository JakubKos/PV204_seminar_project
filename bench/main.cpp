#include <cstdio>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <cstring>

#include <sys/ioctl.h>
#include <unistd.h>

extern "C" {

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/ecc.h>
}

int TERM_WIDTH;

class Bench {
    void(*f)(void);
    size_t iter;
    size_t data;
    const char* desc;
    const char* unit;
    std::optional<long> time;

public:
    Bench() = default;

    Bench(void (*f)(void), size_t iter, size_t data, const char* desc, const char* unit)
        : f(f), iter(iter), data(data), desc(desc), unit(unit) {}

    long run() {
        clock_t begin = clock();
        while(iter--)
            f();
        clock_t end = clock();
        return *(time = (end - begin) * (1000000 / CLOCKS_PER_SEC));
    }

    void summary() {
        if(!time)
            run();

        char result[256];
        sprintf(result, "[%0.2f %s]", (data * 1000.0 * 1000 / *time), unit);

        char buffer[TERM_WIDTH + 1];
        std::memset(buffer, '.', sizeof(buffer));
        buffer[TERM_WIDTH] = '\0';
        buffer[sprintf(buffer, "%s", desc)] = '.';
        strcpy(buffer + TERM_WIDTH - strlen(result), result);
        std::puts(buffer);
    }
};

struct Options {
    int rsa_max = 2048;
    int ecc_max = 256;
    bool enable_rng = true;
};

std::vector<Bench> benches;

WC_RNG rng;
RsaKey rsaKey, rsaKey512, rsaKey1024, rsaKey2048;
int e = 65537;

byte in[128] = "The tiger and the lion may be more powerful, but the wolf doesn't perform in the circus!\0";
byte sign64[64]; // RSA 512
byte sign128[128]; // RSA 1024
byte sign256[256]; // RSA 2048
byte sig512[512]; // ECC
byte encECC[160];
word32 encECCLen = 160;
byte decECC[160];
word32 decECCLen = 160;
word32 sigLen = 512;

byte enc64[64];
byte enc128[128];
byte enc256[256];
byte dec[128];

ecc_key eccKey, eccKeyA, eccKeyB;
int ret;

void init(Options opt) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    TERM_WIDTH = w.ws_col;

    // RNG
    wc_InitRng(&rng);
    // RSA - init & make
    wc_InitRsaKey(&rsaKey, NULL);
    wc_InitRsaKey(&rsaKey512, NULL);
    wc_InitRsaKey(&rsaKey1024, NULL);
    wc_InitRsaKey(&rsaKey2048, NULL);
    wc_MakeRsaKey(&rsaKey512, 512, e, &rng);
    wc_MakeRsaKey(&rsaKey1024, 1024, e, &rng);
    wc_MakeRsaKey(&rsaKey2048, 2048, e, &rng);
    wc_RsaSetRNG(&rsaKey512, &rng);
    wc_RsaSetRNG(&rsaKey1024, &rng);
    wc_RsaSetRNG(&rsaKey2048, &rng);

    // RSA - signing & encrypt
    wc_RsaSSL_Sign(in, 32, sign64, 64, &rsaKey512, &rng);
    wc_RsaSSL_Sign(in, 64, sign128, 128, &rsaKey1024, &rng);
    wc_RsaSSL_Sign(in, 128, sign256, 256, &rsaKey2048, &rng);
    wc_RsaPublicEncrypt(in, 128, enc256, 256, &rsaKey2048, &rng);
    wc_RsaPublicEncrypt(in, 64, enc128, 128, &rsaKey1024, &rng);
    wc_RsaPublicEncrypt(in, 32, enc64, 64, &rsaKey512, &rng);

    // ECC - init & make
    wc_ecc_init(&eccKey);
    wc_ecc_init(&eccKeyA);
    wc_ecc_init(&eccKeyB);
    wc_ecc_make_key_ex(&rng, 32, &eccKey, ECC_SECP256R1);
    wc_ecc_make_key_ex(&rng, 32, &eccKeyA, ECC_SECP256R1);
    wc_ecc_make_key_ex(&rng, 32, &eccKeyB, ECC_SECP256R1);

    // ECC - signing & encrypt
    wc_ecc_sign_hash(in, 128, sig512, &sigLen, &rng, &eccKeyA);
    wc_ecc_encrypt(&eccKeyA, &eccKeyB, in, 128, encECC, &encECCLen, NULL);

    if(opt.enable_rng)
        benches.emplace_back(
            [](){
                byte buff[128];
                wc_RNG_GenerateBlock(&rng, buff, sizeof(buff));
            },
            1024*1024,
            128,
            "RNG 128B block",
            "MB/s"
        );

    if(opt.ecc_max >= 256) {
        benches.emplace_back(
            [](){
                wc_ecc_make_key_ex(&rng, 32, &eccKey, ECC_SECP256R1);
            },
            1024,
            1024,
            "ECC make 256b key",
            "op/s"
        );

        benches.emplace_back(
            [](){
                sigLen = 512;
                wc_ecc_sign_hash(in, 128, sig512, &sigLen, &rng, &eccKeyA);
            },
            1024,
            128,
            "ECC sign, 256b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_ecc_verify_hash(sig512, sigLen, in, 128, &ret, &eccKeyA);
            },
            1024,
            128,
            "ECC verify, 256b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_ecc_encrypt(&eccKeyA, &eccKeyB, in, 128, encECC, &encECCLen, NULL);
            },
            1024,
            128,
            "ECC encrypt, 256b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_ecc_decrypt(&eccKeyB, &eccKeyA, encECC, encECCLen, decECC, &decECCLen, NULL);
            },
            1024,
            encECCLen,
            "ECC decrypt, 256b key",
            "KB/s"
        );
    }

    if(opt.rsa_max >= 512) {
        benches.emplace_back(
            [](){
                wc_MakeRsaKey(&rsaKey, 512, e, &rng);
            },
            512,
            512,
            "RSA make 512b key",
            "op/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Sign(in, 32, sign64, 64, &rsaKey512, &rng);
            },
            1024,
            32,
            "RSA sign, 512b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Verify(sign64, 64, in, 32, &rsaKey512);
            },
            1024,
            64,
            "RSA verify, 512b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaPublicEncrypt(in, 32, enc64, 64, &rsaKey512, &rng);
            },
            1024,
            32,
            "RSA encrypt, 512b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaPrivateDecrypt(enc64, 64, dec, 32, &rsaKey512);
            },
            1024,
            64,
            "RSA decrypt, 512b key",
            "KB/s"
        );
    }

    if(opt.rsa_max >= 1024) {
        benches.emplace_back(
            [](){
                wc_MakeRsaKey(&rsaKey, 1024, e, &rng);
            },
            256,
            256,
            "RSA make 1024b key",
            "op/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Sign(in, 64, sign128, 128, &rsaKey1024, &rng);
            },
            1024,
            64,
            "RSA sign, 1024b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Verify(sign128, 128, in, 64, &rsaKey1024);
            },
            1024,
            128,
            "RSA verify, 1024b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaPublicEncrypt(in, 64, enc128, 128, &rsaKey1024, &rng);
            },
            1024,
            64,
            "RSA encrypt, 1024b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaPrivateDecrypt(enc128, 128, dec, 64, &rsaKey1024);
            },
            1024,
            128,
            "RSA decrypt, 1024b key",
            "KB/s"
        );
    }

    if(opt.rsa_max >= 2048) {
        benches.emplace_back(
            [](){
                wc_MakeRsaKey(&rsaKey, 2048, e, &rng);
            },
            128,
            128,
            "RSA make 2048b key",
            "op/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Sign(in, 128, sign256, 256, &rsaKey2048, &rng);
            },
            1024,
            128,
            "RSA signature, 2048b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaSSL_Verify(sign256, 256, in, 128, &rsaKey2048);
            },
            1024,
            256,
            "RSA verify, 2048b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                wc_RsaPublicEncrypt(in, 128, enc256, 256, &rsaKey2048, &rng);
            },
            1024,
            128,
            "RSA encrypt, 2048b key",
            "KB/s"
        );

        benches.emplace_back(
            [](){
                ret = wc_RsaPrivateDecrypt(enc256, 256, dec, 128, &rsaKey2048);
            },
            1024,
            256,
            "RSA decrypt, 2048b key",
            "KB/s"
        );
    }
}

void destroy() {
    wc_FreeRng(&rng);
    wc_FreeRsaKey(&rsaKey);
    wc_FreeRsaKey(&rsaKey512);
    wc_FreeRsaKey(&rsaKey1024);
    wc_FreeRsaKey(&rsaKey2048);
    wc_ecc_free(&eccKey);
    wc_ecc_free(&eccKeyA);
    wc_ecc_free(&eccKeyB);
}

void print_help(const char* argv0) {
    printf("USAGE:\n");
    printf("  %s [options]\n", argv0);
    printf("OPTIONS:\n");
    printf("  --help          print help\n");
    printf("  --norsa         disable RSA benchmarks\n");
    printf("  --noecc         disable ECC benchmarks\n");
    printf("  --norng         disable RNG benchmarks\n");
    printf("  --rsamax <MAX>  set maximal RSA key length to <MAX>\n");
    printf("  --eccmax <MAX>  set maximal ECC key length to <MAX>\n");
}

int main(int argc, char** argv) {
    Options opt;

    for(int i = 1; i < argc; ++i) {
            if(!std::strcmp("--norsa", argv[i]))
                opt.rsa_max = 0;
            else if(!std::strcmp("--noecc", argv[i]))
                opt.ecc_max = 0;
            else if(!std::strcmp("--norng", argv[i]))
                opt.enable_rng = false;
            else if(!std::strcmp("--eccmax", argv[i])) {
                if(i + 1 < argc) {
                    opt.ecc_max = std::atoi(argv[++i]);
                }
                else {
                    fprintf(stderr, "Invalid options, please, read help.\n");
                    print_help(argv[0]);
                    return 1;
                }
            }
            else if(!std::strcmp("--rsamax", argv[i])) {
                if(i + 1 < argc) {
                    opt.rsa_max = std::atoi(argv[++i]);
                }
                else {
                    fprintf(stderr, "Invalid options, please, read help.\n");
                    print_help(argv[0]);
                    return 1;
                }
            }
            else if(!std::strcmp("--help", argv[i])) {
                print_help(argv[0]);
                return 0;
            }
            else {
                fprintf(stderr, "Invalid options, please, read help.\n");
                print_help(argv[0]);
                return 1;
            }
    }

    init(opt);

    for(auto& bench : benches)
        bench.summary();


    destroy();
    return 0;
}
