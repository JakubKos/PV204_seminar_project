#include <cstdio>
#include <unordered_map>
#include <string>
#include <optional>

extern "C" {
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>
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

    Bench(void (*f)(void), size_t iter, size_t data, const char* desc, const char* unit) {
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

std::unordered_map<std::string, Bench> benches;

WC_RNG rng;

void summary(const char* desc, const char* unit, long ms, long data) {
    printf("%-30s [%.2lf %s/s]\n", desc, (data * 1000.0 * 1000) / ms, unit);
}

void init() {
    wc_InitRng(&rng);

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
