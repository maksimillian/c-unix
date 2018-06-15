#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  struct termios t;
  char c;
  fd_set f;
  tcgetattr(0, &t);
  t.c_lflag &= ~ICANON;
  t.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
  tcsetattr(0, TCSANOW, &t);
  int flags = fcntl(0, F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl(0, F_SETFL, flags);
  // FD_SET(0, &f);

  // fcntl(1, O_NONBLOCK);
  while (1) {
    usleep(10000);
    if (read(0, &c, 1) != -1) {

      write(1, &c, 1);
    } else {
      c = '*';
      write(1, &c, 1);
    }
  }
  return 0;
}
