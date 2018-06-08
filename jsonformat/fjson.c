#include <stdio.h>

int main(int argc, char const *argv[]) {
  int depth = 0;
  int c;
  char state = 0;

  while ((c = fgetc(stdin)) != EOF) {
    if (c == '\"') {
      if (state == 0) {
        state = 1;
      } else {
        state = 0;
      }

      fputc(c, stdout);
    } else if (c == '{' || c == '[') {
      fputc(c, stdout);
      fputc('\n', stdout);
      depth++;
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    } else if (c == '}' || c == ']') {
      fputc(c, stdout);
      fputc('\n', stdout);
      depth--;
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    } else if (c == ':') {
      fputc(c, stdout);
      fputc(' ', stdout);
    } else if (state == 1) {
      fputc(c, stdout);
    } else if (state == ',') {
      fputc(c, stdout);
      fputc('\n', stdout);
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    }
    /*if (c == '{') {
      depth++;
      fputc(c, stdout);
    } else if (c == '}') {
      depth--;
      fputc(c, stdout);
    } else if (c == '\n') {
      fputc(c, stdout);
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    }*/
  }
}
