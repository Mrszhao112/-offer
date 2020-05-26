#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//执行该程序 在另一个中断通过ps aux | grep a.out | grep -v grep 命令可以发现该进程
int main () {

  while (1) {
    sleep(2);
  }
  return 0;
}
//tip 进程优先级PRI  ps -l 查看 top->r->id->nice值 修改
