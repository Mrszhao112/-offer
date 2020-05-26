#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//人为让子进程退出 父进程不关注 造成僵尸进程
int main () {
  pid_t id = fork();
  if (id < 0) {
    perror("fork error");
    return -1;
  }else if (id > 0) {
    printf("father [%d] sleep\n",getpid());
    sleep(10);
    return 0;
  }else {
    printf("son [%d] ZZZ\n",getpid());
    sleep(5);
    exit(EXIT_SUCCESS);
  }
  return 0;
}
