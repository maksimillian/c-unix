#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#define c_width 12
#define c_heigth 21

enum { f_i, f_o, f_t, f_s, f_z, f_j, f_l };

typedef struct figure figure_t;
typedef struct cup cup_t;
struct figure {
  int a : 16;
  int p : 2;
  void (*const print)(figure_t);
  void (*const rotate_cw)(figure_t);
  void (*const rotate_ccw)(figure_t);
  int (*const width)(figure_t);
  int (*const height)(figure_t);
  int (*const mayFall)(figure_t);
};
struct cup {
  int f[c_width][c_heigth];
};

cup_t cup;

void initCup() {

  for (int y = 0; y < c_heigth; y++) {
    for (int x = 0; x < c_width; x++) {
      if (x == 0 || x == c_width - 1 || y == c_heigth - 1)
        cup.f[x][y] = 1;
      else
        cup.f[x][y] = 0;
    }
  }
};

void printCup() {
  char s = '\n';
  for (int y = 0; y < c_heigth; y++) {
    for (int x = 0; x < c_width; x++) {
      if (cup.f[x][y] == 1)
        write(1, "\u25AF", 3);
      else
        write(1, ".", 1);
    }
    write(1, &s, 1);
  }
};

int main(int argc, char const *argv[]) {
  struct termios t;
  char c;

  char block[] = {0xE2, 0x96, 0xA3};
  char *s;
  fd_set f;
  tcgetattr(0, &t);
  t.c_lflag &= ~ICANON;
  t.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
  tcsetattr(0, TCSANOW, &t);
  int flags = fcntl(0, F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl(0, F_SETFL, flags);
  // FD_SET(0, &f);
  initCup();
  printCup();
  // fcntl(1, O_NONBLOCK);
  /*while (1) {
    usleep(10000);
    if (read(0, &c, 1) != -1) {

      write(1, &c, 1);
    } else {
      s = "\033[38;5;206m\u25A3 ";
      write(1, s, 14);
    }
  }*/
  return 0;
}
