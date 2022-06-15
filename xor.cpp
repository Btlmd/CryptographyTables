#include <cstdio>
#include <cstdint>

int main() {
    FILE* f = fopen("xor.txt", "w");
    for (int i {0}; i < 0x0100; ++i) {
        for (int j {0}; j < 0x0100; ++j) {
            if (j == 0) {
                fprintf(f, "\n");
            }
            uint8_t lhs{static_cast<uint8_t>(i)}, rhs{static_cast<uint8_t>(j)};
            fprintf(f, "%02X xor %02X = %02X\n", lhs, rhs, lhs ^ rhs);
        }
    }
    return 0;
}