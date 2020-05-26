#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//自身进程id pid 
//父进程id ppid 
int main () {
  printf("pid: %d\n",getpid());
  printf("ppid: %d\n",getppid());
  return 0;
}
