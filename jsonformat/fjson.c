#include <stdio.h>
int null (FILE *in, FILE *out){
  int c = fgetc(in);
  if(c != 'n')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'u')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'l')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'l')
    return 0;
  fputc(c,out);
  return 1;
}

int false (FILE *in, FILE *out){
  int c = fgetc(in);
  if(c != 'f')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'a')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'l')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 's')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'e')
    return 0;
  fputc(c,out);
  return 1;
}

int true (FILE *in, FILE *out){
  int c = fgetc(in);
  if(c != 't')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'r')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'u')
    return 0;
  fputc(c,out);
  c = fgetc(in);
  if(c != 'e')
    return 0;
  fputc(c,out);
  return 1;
}

int apostrophe (FILE *in, FILE *out, int lc){
  int c = fgetc(in);
  if(c == '\"' && lc != '\\'){
    fputc(c,out);
    return 0;
  }
  fputc(c,out);
  //fputc('.',out);
  return 1;
}

int main(int argc, char const *argv[]) {
  int depth = 0;
  int c;
  char istext = 0;
  int ok = 1;
  FILE *fp;
  fp = fopen("output.json","w+");
  while (ok && !feof(stdin)) {
    c = fgetc(stdin);
    if (!istext){
    if (c == '\"') {
      istext = 1;
      fputc(c, fp);
    } else if(c == 'n'){
      ungetc(c,stdin);
      ok = null(stdin,fp);
    } else if(c == 'f'){
      ungetc(c,stdin);
      ok = false(stdin,fp);
    } else if(c == 't'){
      ungetc(c,stdin);
      ok = true(stdin,fp);
    } else if (c == '{') {
      fputc(c, fp);
      fputc('\n', fp);
      depth++;
      for (int i = 0; i < depth; i++) {
        fputc('\t', fp);
      }
    } else if (c == '[') {
      fputc(c, fp);
      fputc('\n', fp);
      depth++;
      for (int i = 0; i < depth; i++) {
        fputc('\t', fp);
      }
    } else if (c == '}' || c == ']') {
      fputc(c, fp);
      fputc('\n', fp);
      depth--;
      for (int i = 0; i < depth; i++) {
        fputc('\t', fp);
      }
    } else if (c == ':') {
      fputc(c, fp);
      fputc(' ', fp);
    } else if (c == ',') {
      fputc(c, fp);
      fputc('\n', fp);
      for (int i = 0; i < depth; i++) {
        fputc('\t', fp);
      }
    }
  } else {
    /*if (c == '\\'){
      fputc(c,fp);
      istext = apostrophe(stdin,fp,c);
    }*/
    fputc(c,fp);
    istext = apostrophe(stdin,fp,c);
  }
    /*if (c == '{') {
      depth++;
      fputc(c, fp);
    } else if (c == '}') {
      depth--;
      fputc(c, fp);
    } else if (c == '\n') {
      fputc(c, fp);
      for (int i = 0; i < depth; i++) {
        fputc('\t', fp);
      }
    }*/
  }
  fclose(fp);
}
