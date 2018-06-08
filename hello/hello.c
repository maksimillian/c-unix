#include <stdio.h>

int main(int argc, char const *argv[]) {
    unsigned char buf[1000];
    int i = 0;
    int j = 0;
    int n = 2;
    fgets(buf, sizeof buf, stdin);
    // fprintf(stdout, "%s\n", buf);
    while (buf[i] != '\0') {
        if (buf[i] >= 0xF0) {
            // printf("%d >= \xF0", buf[i]);
            for (j = i; j < i + 4; j++) {
                fputc(buf[j], stdout);
            }
            // printf("4 n = %d \n", n);
            n--;
            i += 4;
        } else if (buf[i] >= 0xE0) {
            for (j = i; j < i + 3; j++) {
                fputc(buf[j], stdout);
            }
            // printf("3 n = %d \n", n);
            n--;
            i += 3;
        } else if (buf[i] >= 0xC0) {
            for (j = i; j < i + 2; j++) {
                fputc(buf[j], stdout);
            }
            // printf("2 n = %d \n", n);
            n--;
            i += 2;
        } else if (buf[i] != '\n' && buf[i] < 0x80) {
            fputc(buf[i], stdout);
            // printf("1 n = %d \n", n);
            n--;
            i += 1;
        }
        if (n <= 0) {
            n = 2;
            printf("\n");
        }
        //'\x80' <= c &&c <= '\xbf'
    }
    printf("\n");
    return 0;
}
