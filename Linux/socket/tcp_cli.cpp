#include "tcpsocket.hpp"
#include <iostream>
#include <signal.h>

void sigcb(int no) {
  printf("recv %d\n", no);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "usage port"<< std::endl;
    return -1;
  }
  //绑定信息
  signal(SIGPIPE, sigcb);
  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);

  TcpSocket lst_sock;//新建套接字发起连接请求
  CHECK_RET(lst_sock.Socket());
  CHECK_RET(lst_sock.Connect(ip, port));

      while (1) {
      std::string buf;
      std::cout << "client say: ";
      std::cin >> buf;
      lst_sock.Send(buf);

      buf.clear();
      lst_sock.Recv(&buf);
      std::cout << "srv say" << buf << std::endl;
      }
      lst_sock.Close();
      return 0;
}
