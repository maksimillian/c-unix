#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 1024

struct linux_dirent {
  long d_ino;
  off_t d_off;
  unsigned short d_reclen;
  char d_name[];
};

FILE *fp;
int level = 0;
void readDir(int fd) {
  struct linux_dirent *d;
  struct stat s;
  int nread, bpos;
  char buf[BUF_SIZE];
  char d_type;
  int fc = 0;
  int dc = 0;
  for (;;) {
    nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
    if (nread == 0) {
      fprintf(fp, "]}");
      break;
    }
    for (bpos = 0; bpos < nread;) {
      d = (struct linux_dirent *)(buf + bpos);
      d_type = *(buf + bpos + d->d_reclen - 1);
      if (d_type == DT_DIR) {
        if (!(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)) {
          int nfd = openat(fd, d->d_name, O_RDONLY | O_DIRECTORY);
          if (dc || fc)
            fputc(',', fp);
          fprintf(fp, "{\"%s\":[", d->d_name);
          readDir(nfd);
          dc++;
          close(nfd);
        }
      } else {
        if (fc)
          fputc(',', fp);
        printf("%s:", d->d_name);
        printf("%d\n", fstatat(fd, d->d_name, &s, AT_SYMLINK_NOFOLLOW));
        fprintf(fp, "{\"name\":\"%s\"", d->d_name);
        fprintf(fp, ",\"size\":\"%ld\"", s.st_size);
        fprintf(fp, ",\"size on disk\":\"%ld\"", s.st_blocks * 512);
        fprintf(fp, ",\"slag\":\"%ld\"}", s.st_blocks * 512 - s.st_size);
        fc++;
      }
      bpos += d->d_reclen;
    }
  }
}

int main(int argc, char const *argv[]) {
  int fd;
  fp = fopen("dir.json", "w+");
  fd = open(".", O_RDONLY | O_DIRECTORY);
  fprintf(fp, "{\"%s\":[", get_current_dir_name());
  readDir(fd);
  close(fd);
  fflush(fp);
  fclose(fp);
}
