#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
//先让父进程退出 使得子进程成为孤儿进程
int main () {
  pid_t id = fork();
  if (id < 0) {
    perror("fork");
  }else if(id == 0) {
    printf("child %d\n",getpid());
    sleep(5);
  }else {
    printf("father %d\n",getppid());
    sleep(2);
    exit(0);
  }
  return 0;
}
