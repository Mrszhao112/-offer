#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd = -1;
  // umask(0);//将掩码本次设置为零 从而不用计算掩码
  fd = open("./test.txt", O_RDWR|O_CREAT, 0664);
  if (fd < 0) {
    perror("open error");
    return -1;
  }
  char *ptr = "zhaoyang zai gan ma \n";
  int ret = write(fd, ptr, strlen(ptr));
  if (ret < 0) {
    perror("write error");
    return -1;
  }
  printf("ret %d/n",ret);
  close(fd);
  return 0;
}
