#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//fork创建进程
//返回值可以分流 
//小于零 出错
//等于零子进程
//大于零父进程 (多次测验发现 ret大于零时 与子进程pid相等)
int main () {
  int ret = fork();
  if (ret < 0) {
    perror("fork error");
    return -1;
  } else if (ret == 0) {
    printf("child %d ret %d\n",getpid(),ret);
  }else {
    printf("father %d ret %d\n",getpid(),ret);
  }
  sleep(1);
  return 0;
}
