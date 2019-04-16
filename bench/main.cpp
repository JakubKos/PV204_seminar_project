#include <cstdio>
#include <map>
#include <string>
#include <optional>

extern "C" {
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/ecc.h>
}

class Bench {
    void(*f)(void);
    size_t iter;
    size_t data;
    const char* desc;
    const char* unit;
    std::optional<long> time;

public:
    Bench() = default;

    Bench(void (*f)(void), size_t iter, size_t data, const char* desc, const char* unit, bool time = false) {
        this->f = f;
        this->iter = iter;
        this->data = data;
        this->desc = desc;
        this->unit = unit;
    }

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

        printf("%-30s [%.2lf %s/s]\n", desc, (data * 1000.0 * 1000) / *time, unit);
    }
};

std::map<std::string, Bench> benches;

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

ecc_key eccKey, eccKeyA, eccKeyB;
int ret;

void summary(const char* desc, const char* unit, long ms, long data) {
    printf("%-30s [%.2lf %s/s]\n", desc, (data * 1000.0 * 1000) / ms, unit);
}

void init() {
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

    // RSA - signing & encrypt
    wc_RsaSSL_Sign(in, 32, sign64, 64, &rsaKey512, &rng);
    wc_RsaSSL_Sign(in, 64, sign128, 128, &rsaKey1024, &rng);
    wc_RsaSSL_Sign(in, 128, sign256, 256, &rsaKey2048, &rng);
    // encrypt - TODO

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


    benches["rng_128"] = {
        [](){
            byte buff[128];
            wc_RNG_GenerateBlock(&rng, buff, sizeof(buff));
        },
        1024*1024,
        128,
        "RANDOM by 128B",
        "MB"
    };

    benches["ec make key"] = {
        [](){
            wc_ecc_make_key_ex(&rng, 32, &eccKey, ECC_SECP256R1);
        },
        1024,
        1024,
        "ECC make key 32b",
        ""
    };

    benches["ecc_hash"] = {
        [](){
            sigLen = 512;
            wc_ecc_sign_hash(in, 128, sig512, &sigLen, &rng, &eccKeyA);
        },
        1024,
        128,
        "ECC HASH",
        "KB"
    };

    benches["ecc_verify"] = {
        [](){
            wc_ecc_verify_hash(sig512, sigLen, in, 128, &ret, &eccKeyA);
        },
        1024,
        128,
        "ECC VERIFY",
        "KB"
    };

    benches["ecc_encrypt"] = {
        [](){
            wc_ecc_encrypt(&eccKeyA, &eccKeyB, in, 128, encECC, &encECCLen, NULL);
        },
        1024,
        128,
        "ECC ENCRYPT",
        "KB"
    };

    benches["ecc_decrypt"] = {
        [](){
            wc_ecc_decrypt(&eccKeyB, &eccKeyA, encECC, encECCLen, decECC, &decECCLen, NULL);
        },
        1024,
        encECCLen,
        "ECC DECRYPT",
        "KB"
    };

    benches["RSA_512b"] = {
        [](){
            wc_MakeRsaKey(&rsaKey, 512, e, &rng);
        },
        512,
        512,
        "RSA make key 512b",
        ""
    };

    benches["RSA_1024b"] = {
        [](){
            wc_MakeRsaKey(&rsaKey, 1024, e, &rng);
        },
        256,
        256,
        "RSA make key 1024b",
        ""
    };

    benches["RSA_2048"] = {
        [](){
            wc_MakeRsaKey(&rsaKey, 2048, e, &rng);
        },
        128,
        128,
        "RSA make key 2048b",
        ""
    };

    benches["RSA signature 512"] = {
        [](){
            wc_RsaSSL_Sign(in, 32, sign64, 64, &rsaKey512, &rng);
        },
        1024,
        32,
        "RSA signature, 512b key",
        "KB"
    };

    benches["RSA signature 1024"] = {
        [](){
            wc_RsaSSL_Sign(in, 64, sign128, 128, &rsaKey1024, &rng);
        },
        1024,
        64,
        "RSA signature, 1024b key",
        "KB"
    };

    benches["RSA signature 2048"] = {
        [](){
            wc_RsaSSL_Sign(in, 128, sign256, 256, &rsaKey2048, &rng);
        },
        1024,
        128,
        "RSA signature, 2048b key",
        "KB"
    };

    benches["RSA verify 512"] = {
        [](){
            wc_RsaSSL_Verify(sign64, 64, in, 32, &rsaKey512);
        },
        1024,
        64,
        "RSA verify, 2048b key",
        "KB"
    };

    benches["RSA verify 1024"] = {
        [](){
            wc_RsaSSL_Verify(sign128, 128, in, 64, &rsaKey1024);
        },
        1024,
        128,
        "RSA verify, 1024b key",
        "KB"
    };

    benches["RSA verify 2048"] = {
        [](){
            wc_RsaSSL_Verify(sign256, 256, in, 128, &rsaKey2048);
        },
        1024,
        256,
        "RSA verify, 2048b key",
        "KB"
    };
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

int main(int argc, char** argv) {
    init();

    if (argc == 1) {
        for(auto& [_, bench] : benches)
            bench.summary();
    }
    else {
        for(int i = 0; i < argc; ++i) {
            auto found = benches.find(argv[i]);
            if(found != benches.end())
                found->second.summary();
        }
    }

    destroy();
    return 0;
}
