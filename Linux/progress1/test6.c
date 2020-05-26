#include <stdio.h>
#include <stdlib.h>
//函数
int main (int argc, char *argv[], char *env[]) {
  int i = 0;
  for (; env[i]; i++) {
    printf("env[%s] ",env[i]);
    printf("\n");
  }
//第三方变量获取 environ是一个全局变量指向环境变量表 环境变量表就是main的第三个参数
  extern char **environ;
  int j = 0;
  for (; environ[j]; j++) {
    printf("environ%s\n",environ[j]);
  }
//putenv/getenv 系统调用获取
  printf("PATH %s\n",getenv("PATH"));
  
//环境变量具有全局性 
//在外部通过 export MYVAL="1234"  设置一个环境变量进行查看 
  printf("MYVAL %s\n",getenv("MYVAL"));
  return 0;
  
}
