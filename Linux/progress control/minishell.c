#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CMD 1024
char command[MAX_CMD];

int do_face() {//处理错误
  memset(command, 0x00, MAX_CMD);
  printf("minishell$ ");
  fflush(stdout);
  if (scanf("%[^\n]%*c", command) == 0) {//手动结束 即出错
    getchar();
    return -1;
  }
  return 0;
}
char **do_parse(char *buFF) { //字符串解析函数

  int myargc = 0;
  static char *myargv[32];
  char *ptr = buFF;
  while (*ptr != '\0') {
    if(*ptr != ' ') {
      myargv[myargc++] = ptr;
      while(*ptr != ' ' && *ptr != '\0') {
        ptr++;
      }
    }
    *ptr = '\0';
    ptr++;

  }
  myargv[myargc] = NULL;
  return myargv;
}

int do_exit(char* buFF) { //程序替换函数 将自己所输入的参数通过函数转换到程序替换函数
  char** myargv = {NULL};
  pid_t pid = fork();
  if (pid < 0) {
    perror("error");
    return -1;
  }else if (pid == 0) { //对子进程进行替换
    myargv = do_parse(buFF);
    if (myargv == NULL) {
      exit(-1);
    }else {
      execvp(myargv[0],myargv);
    }

  }else {
    waitpid(pid,NULL,0);
  }
  return 0;
}
int main () {
  while(1) {
    if (do_face() < 0) {
      continue;
    }
    do_exit(command);
  }
  return 0;
}
