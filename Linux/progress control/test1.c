#include <unistd.h>
#include <stdio.h>
int main () {
  pid_t pid;
  printf("before pid %d\n",getpid());
  pid = fork();
  //返回值分流 
  //子进程等于零 父进程大于零时=子进程pid
  if (pid < 0) {
    perror("error\n");
    return -1;
  }else if (pid == 0) {
    printf("son 返回值 %dand pid  %d\n",pid,getpid());
    sleep(1);
  }else {
    sleep(2);
    printf("father 返回值 %dand pid %d\n",pid,getpid());
  }
  return 0;
}
