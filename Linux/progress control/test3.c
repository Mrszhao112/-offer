#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//test1 测试简单的程序等待 用于结束僵尸进程
void test1(){
  pid_t id = fork();
  if (id < 0) {
    perror("error\n");
  }else if (id == 0) {
    sleep(1);
    exit(0);
  }else {
    sleep(5);
   pid_t waitp =  wait(0);
   printf("结束了僵尸进程 %d \n",waitp);
    sleep(10);
  }
}
//测试正常退出与异常退出  并获取status
void test2() {
  pid_t id = fork();
  if (id < 0) {
    perror("error");
      exit(1);
  }else if (id == 0) {
    sleep(20);
    //exit(0);
  }else {
    int st;
    int ret;
    ret = wait(&st);//ret获取等待到的进程id st用于输出进程退出状况
    //st 获取的值是status位图中的低八位 全零说明正常退出 不为零时 是异常的信号
    if (ret > 0 && (st& 0x7F) == 0)  {
      printf ("正常退出 %d\n",(st>>8)&0xff );//低16位中的高8位 存储的是一个字节的返回值
    }else if (ret > 0) {
      printf("sign code %d\n",st&0x7f);//异常信号 core dump是首个bt位 
    }
  }
}
//进程的阻塞等待
void test3() {
  pid_t pid ;
  pid = fork();
  if (pid < 0) {
   perror("error");
  }else if (pid == 0) {
    sleep(1000);
    exit(0);
  }else {
    int status = 0;
    pid_t ret = waitpid(-1, &status, 0);//阻塞等待
    if (WIFEXITED(status)&&ret) {
      printf("okay %d\n",WEXITSTATUS(status));
    }else if (ret) {
      printf("faild %d\n",WEXITSTATUS(status));
    }
  }
}

//进程的阻塞等待
void test4() {
  pid_t pid ;
  pid = fork();
  if (pid < 0) {
   perror("error");
  }else if (pid == 0) {
    sleep(1000);
    exit(0);
  }else {
    int status = 0;
    pid_t ret = 0;
    do{
    ret = waitpid(-1, &status, WNOHANG);//非阻塞等待 如果没有进程退出那么就是循环等待WNOHANG
    if(ret == 0) {
      printf("son is running\n");
    }
    sleep(1);
    }while(ret == 0);
    if (WIFEXITED(status)&&ret) {
      printf("okay %d\n",WEXITSTATUS(status));
    }else if (ret) {
      printf("faild %d\n",WEXITSTATUS(status));
    }
  }
}

int main () {
  //test2();
  //test3();
  test4();
  return 0;
}
