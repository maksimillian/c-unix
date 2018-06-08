#include <stdio.h>

int main(int argc, char const *argv[]) {
  char buf[1000];
  fgets(buf, sizeof buf, stdin);
}
