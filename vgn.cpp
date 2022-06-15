#include <cstdio>
#include <cstdlib>

int main() {
    auto f {fopen("v.txt", "w")};
    for (char i {'A'}; i <= 'Z'; ++i) {
        fprintf(f, "\n");
        for (char j {'A'}; j <= 'Z'; ++j) {
            fprintf(f, "%c @ %c = %c\n", j, i, (char)((j - 'A' + i - 'A') % 26 + 'A'));
        }
    }

    return 0;
}