#include <unistd.h>
int main () {
  char *const argv[] = {"ps", "-ef", NULL};//字符数组的形式
  char *const envp[] ={"PATH=/bin:/user/bin","TERM=console", NULL};

  evecl("/bin/ps","ps","-ef",NULL);//写全路径
  execlp("ps", "ps", "-ef", NULL);//使用PATH环境变量
  execle("ps", "ps", "-ef", NULL, envp);// e 自己组织环境变量

  //v 使用数组当参数
  execv("/bin/ps", argv);
  execve("/bin/ps", argv,envp);
  execvp("ps", argv);
  return 0;
}
