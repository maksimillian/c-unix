#include <stdio.h>
int null(FILE *in, FILE *out) {
  int c = fgetc(in);
  if (c != 'n')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'u')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'l')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'l')
    return 0;
  fputc(c, out);
  return 1;
}

int false(FILE *in, FILE *out) {
  int c = fgetc(in);
  if (c != 'f')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'a')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'l')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 's')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'e')
    return 0;
  fputc(c, out);
  return 1;
}

int true(FILE *in, FILE *out) {
  int c = fgetc(in);
  if (c != 't')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'r')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'u')
    return 0;
  fputc(c, out);
  c = fgetc(in);
  if (c != 'e')
    return 0;
  fputc(c, out);
  return 1;
}

int text(FILE *in, FILE *out) {
  int c = fgetc(in);
  int slash = (c == '\\');

  fputc(c, out);
  for (c = fgetc(in); c != '"' || slash; c = fgetc(in)) {
    fputc(c, out);

    if (slash)
      slash = 0;
    else
      slash = (c == '\\');
  }
  fputc(c, out);

  return 1;
}

int main(int argc, char const *argv[]) {
  int depth = 0;
  int c;
  char istext = 0;
  int ok = 1;
  while (ok && !feof(stdin)) {
    c = fgetc(stdin);

    if (c == '"') {
      // ungetc(c, stdin);
      fputc(c, stdout);
      ok = text(stdin, stdout);
    } else if (c == 'n') {
      ungetc(c, stdin);
      ok = null(stdin, stdout);
    } else if (c == 'f') {
      ungetc(c, stdin);
      ok = false(stdin, stdout);
    } else if (c == 't') {
      ungetc(c, stdin);
      ok = true(stdin, stdout);
    } else if (c == '{') {
      fputc(c, stdout);
      fputc('\n', stdout);
      depth++;
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    } else if (c == '[') {
      fputc(c, stdout);
      fputc('\n', stdout);
      // depth++;
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    } else if (c == ']') {
      fputc('\n', stdout);
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
      fputc(c, stdout);
    } else if (c == '}') {
      depth--;
      fputc('\n', stdout);
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
      fputc(c, stdout);
    } else if (c == ':') {
      fputc(c, stdout);
      fputc(' ', stdout);
    } else if (c == ',') {
      fputc(c, stdout);
      fputc('\n', stdout);
      for (int i = 0; i < depth; i++) {
        fputc('\t', stdout);
      }
    }
  }
  fputc('\n', stdout);
  fflush(stdin);
}
