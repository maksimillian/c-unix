#include <stdio.h>

FILE *tmpF;
int main(int argc, char const *argv[]) {
  tmpF = fopen("tmpF", "w+");
  char s[256];
  int c;
  while (fgets(s, 256, stdin) != NULL) {
    fputs(s, tmpF);
  }
  fclose(tmpF);
  tmpF = fopen("tmpF", "r");
  fseek(tmpF, -2L, SEEK_END);
  while (ftell(tmpF) > 0) {
    c = fgetc(tmpF);
    fseek(tmpF, -2L, SEEK_CUR);
    fputc(c, stdout);
  }
  fseek(tmpF, 0, SEEK_SET);
  c = fgetc(tmpF);
  fputc(c, stdout);
  fputc('\n', stdout);
  fclose(tmpF);
}
