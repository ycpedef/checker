/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "func.h"
using namespace std;

//#define COMPATIBLE

std::string readline(std::string prompt) {
    printf("%s", prompt.c_str());
    std::string res;
    getline(cin, res);
    return res;
}

bool isdir(string filename) {
    struct stat s_buf;
    stat(filename.c_str(), &s_buf);
    return S_ISDIR(s_buf.st_mode);
}

void clear_buffer() {
    setbuf(stdin, nullptr);
}

long long myclock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

std::string tostring(int a) {
    char s[256];
    memset(s, 0, sizeof(s));
    int tot = 0;
    while (a > 0) {
        s[tot] = (a % 10) + '0';
        tot++;
        a /= 10;
    }
    for (int i = 0; i < (tot / 2); i++) {
        std::swap(s[i], s[tot - 1 - i]);
    }
    return s;
}

int run(std::string cmd) {
    return system(cmd.c_str());
}

void delline() {
    printf("\e[2A");
    printf("\e[K");
}

void bash_fail() {
    puts(L_RED"\nFailed");
    exit(0);
}

#define pid_t int
int get_memory_by_pid(pid_t p) {
    FILE* fd;
    char name[32], line_buff[256] = {0}, file[64] = {0};
    int i, vmrss = 0;
    sprintf(file, "/proc/%d/status", p);
    fd = fopen(file, "r");
    if (fd == NULL) {
        return -1;
    }
    for (i = 0; i < 40; i++) {
        if (fgets(line_buff, sizeof(line_buff), fd) == NULL) {
            break;
        }
        if (strstr(line_buff, "VmRSS:") != NULL) {
            sscanf(line_buff, "%s %d", name, &vmrss);
            break;
        }
    }
    fclose(fd);
    return vmrss;
}

int get_total_mem() {
    const char* file = "/proc/meminfo";
    FILE* fd;
    char line_buff[256] = {0};
    fd = fopen(file, "r");
    char name[32];
    int memtotal;
    //char* ret = fgets(line_buff, sizeof(line_buff), fd);
    sscanf(line_buff, "%s %d", name, &memtotal);
    fprintf(stderr, "====%s：%d====\n", name, memtotal);
    fclose(fd);
    return memtotal;
}

bool file_exists(string file) {
    return (access(file.c_str(), F_OK) == 0);
}
