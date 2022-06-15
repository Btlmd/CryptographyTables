#include <bits/stdc++.h>

using namespace std;


uint64_t power(uint64_t a, uint64_t x, uint64_t m) {
    if (!x)
        return 1;
    uint64_t res {power(a, x / 2, m)};
    if (x % 2)
        return (a * res * res) % m;
    else
        return (res * res) % m;

}

int main() {
    auto f {fopen("mod_invs.txt", "w")};
    for (int i {2}; i < 500; ++i) {
        fprintf(f, "\n============\nInversions mod %d\n============\n", i);
        for (int j {2}; j < i; ++j) {
            int inv {-1};
            for (int k {0}; k < i; ++k) {
                if (k * j % i == 1) {
                    inv = k;
                    break;
                }
            }
            if (inv == -1) {
                fprintf(f, "inv(%d) mod %d X\n", j, i);
            } else {
                fprintf(f, "inv(%d) mod %d = %d\n", j, i, inv);
            }
        }
    }

    auto f {fopen("powers.txt", "w")};
    const int range {100};

    for (int i {2}; i < range; ++i) {
        fprintf(f, "\n============\nMod %d\n============\n", i);
        for (int j {2}; j < range; ++j) {
            if (i == j)
                continue;
            fprintf(f, "[%d^x mod %d]\n", j, i);
            for (int k {2}; k < range; ++k) {
                fprintf(f, "> %d^%d mod %d = %ld\n", j, k, i, power(j, k, i));
            }
        }
    }
    return 0;
}