#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include "tcpsocket.hpp"

void sigcb(int no) {
  //SIGCHLD信号是非可靠信号， 有可能丢失
  //因此在一次的信号处理中 处理到没有子进程退出为止
  while (waitpid(-1, NULL, WNOHANG) > 0);//返回值大于零说明有子进程退出
}
int main (int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "usage: ./tcp_srv ip port" << std::endl;
    return -1;
  }
  signal(SIGCHLD, sigcb);

  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);
  TcpSocket lst_sock;
  CHECK_RET(lst_sock.Socket());
  CHECK_RET(lst_sock.Bind(ip, port));
  CHECK_RET(lst_sock.Listen());
  while (1) {
    TcpSocket new_sock;
    bool ret = lst_sock.Accept(&new_sock);
    if (ret == false) {
      continue;//持续监听
    }
    int pid = fork();
    if (pid == 0) {
      while (1) {
        std::string buf;
        new_sock.Recv(&buf);
        std::cout << "cll say :" << buf << std::endl;
        buf.clear();
        std::cout << "srv say :";
        std::cin >> buf;
        new_sock.Send(buf);
      }
      new_sock.Close();
      exit(0);
    }
    new_sock.Close();
  }
  lst_sock.Close();
  return 0;
}
