#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#define BUF_SIZE 1024

struct linux_dirent {
  long d_ino;
  off_t d_off;
  unsigned short d_reclen;
  char d_name[];
};

FILE *fp;
void readDir(int fd) {
  struct linux_dirent *d;
  int nread, bpos;
  char buf[BUF_SIZE];
  char d_type;

  for (;;) {
    nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
    if (nread == 0)
      break;
    for (bpos = 0; bpos < nread;) {
      d = (struct linux_dirent *)(buf + bpos);
      d_type = *(buf + bpos + d->d_reclen - 1);
      if (d_type == DT_DIR &&
          !(strcmp(d->d_name, ".") || !(strcmp(d->d_name, "..")))) {
        int nfd = openat(fd, d->d_name, O_RDONLY | O_DIRECTORY);
        readDir(nfd);
        close(nfd);
      }
      fputs(d->d_name, fp);
      fputs("\n", fp);
      bpos += d->d_reclen;
    }
  }
}

int main(int argc, char const *argv[]) {
  int fd;
  fp = fopen("dir.json", "w+");
  fd = open(".", O_RDONLY | O_DIRECTORY);
  readDir(fd);
  close(fd);
  fclose(fp);
}
