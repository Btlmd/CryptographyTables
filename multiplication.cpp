#include <bits/stdc++.h>

using namespace std;


uint8_t mul2(uint8_t rhs) {
    if (rhs & 0x80) {
        return (rhs << 1) ^ 0x1b;
    }
    return rhs << 1;
}

uint8_t mul3(uint8_t rhs) {
    return rhs ^ mul2(rhs);
}

int main() {
    FILE *f = fopen("out.txt", "w");

    fprintf(f, "Times Two\n");

    for (int i = 0; i < 0x0100; ++i) {
        if (i % 16 == 0)
            fprintf(f, "\n");
        fprintf(f, "%02X x 02= %02X\n", i, mul2(i));
    }

    fprintf(f, "\n");
    fprintf(f, "Times Three\n");

    for (int i = 0; i < 0x0100; ++i) {
        if (i % 16 == 0)
            fprintf(f, "\n");
        fprintf(f, "%02X x 03 = %02X\n", i, mul3(i));
    }
}