#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main () {
  printf("hello world");
  //_exit(0); 
  //区别在于 是否执行清理函数刷新缓冲关闭流
  // exit(0);
  return 0;
}
