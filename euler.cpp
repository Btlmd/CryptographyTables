#include <cstdio>
#include <cstdint>
#include <map>
#include <cmath>


bool prime(uint64_t n) {
    for (int i{2}; i < n; ++i) {
        if (n % i == 0 && i != n) {
            return false;
        }
    }
    return true;
}

uint64_t euler(uint64_t n) {
    uint64_t num {n};
    std::map<int, int> factors;
    for (int i {2}; i <= n; ++i) {
        if (prime(i) && num % i == 0) {
            int exp {0};
            while (num % i == 0) {
                ++exp;
                num /= i;
            }
            factors[i] = exp;
        }
    }
    uint64_t phi {1};
    for (const auto& [f, e]: factors) {
        uint64_t exp_min {static_cast<uint64_t>(pow(f, e - 1))};
        phi *= f * exp_min - exp_min;
    }
    return phi;
}

int main() {
    auto f {fopen("euler.txt", "w")};
    for (int i {2}; i < 1000; ++i) {
        fprintf(f, "phi(%d)=%lu\n", i, euler(i));
    }
    return 0;
}