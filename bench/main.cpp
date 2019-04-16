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
RsaKey rsaKey;
ecc_key eccKey;
int e = 65537;

void summary(const char* desc, const char* unit, long ms, long data) {
    printf("%-30s [%.2lf %s/s]\n", desc, (data * 1000.0 * 1000) / ms, unit);
}

void init() {
    wc_InitRng(&rng);
    wc_ecc_init(&eccKey);

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

    benches["ec make key"] = {
        [](){
            wc_ecc_make_key_ex(&rng, 32, &eccKey, ECC_SECP256R1);
        },
        1024,
        1024,
        "ECC make key 32b",
        ""
    };

}

void destroy() {
    wc_FreeRng(&rng);
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
