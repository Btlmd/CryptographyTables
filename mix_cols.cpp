#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


const uint64_t per_file {1ull << 15};
const uint64_t per_dir {1ull << 25};
const uint64_t total {1ull << 32};
const uint64_t workers {4};
const char root[] = "/mnt/e/mix/%s";

uint8_t mul2(uint8_t rhs) {
    if (rhs & 0x80) {
        return (rhs << 1) ^ 0x1b;
    }
    return rhs << 1;
}

uint8_t mul3(uint8_t rhs) {
    return rhs ^ mul2(rhs);
}

void gen(uint64_t begin, uint64_t end, pid_t pid) {
    FILE *f {nullptr};
    char dir_name[50];
    char dir_abs[50];

    for (uint64_t col {begin}; col < end; ++col) {
        auto p {(uint8_t *) &col};

        if (col % per_dir == 0) {
            sprintf(dir_name, "%08lX", col);
            sprintf(dir_abs, root, dir_name);
            mkdir(dir_abs, S_IRWXU);
            printf("Worker [%d] on %s\n", pid, dir_abs);
        }

        if (col % per_file == 0) {
            char fmt[50] = {0}, file[50] = {0};
            strcpy(fmt, dir_abs);
            strcat(fmt, "/%08lX.txt");
            sprintf(file, fmt, col);
            if (f)
                fclose(f);
            f = fopen(file, "w");
        }

        fprintf(f, "%02X %02X %02X %02X->%02X %02X %02X %02X\n",
                p[3], p[2], p[1], p[0],
                mul2(p[3]) ^ mul3(p[2]) ^ p[1] ^ p[0],
                p[3] ^ mul2(p[2]) ^ mul3(p[1]) ^ p[0],
                p[3] ^ p[2] ^ mul2(p[1]) ^ mul3(p[0]),
                mul3(p[3]) ^ p[2] ^ p[1] ^ mul2(p[0])
        );
    }
}

int main() {
    pid_t subs[workers];
    pid_t pid;
    int status;
    assert(total % workers == 0);
    for (int i {0}; i < workers; ++i) {
        pid = fork();
        if (pid) {
            subs[i] = pid;
            printf("Worker [%d] initiated\n", pid);
        } else {
            gen(i * total / workers, (i + 1) * total / workers, getpid());
            break;
        }
    }
    if (pid){
        for (int i {0}; i < workers; ++i) {
            auto termination {wait(&status)};
            printf("Worker [%d] exit with status %d\n", termination, WEXITSTATUS(status));
        }
    }
    return 0;
}