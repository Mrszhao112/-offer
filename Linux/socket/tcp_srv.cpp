#include "tcpsocket.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "usage: tcp_srv is port" << std::endl;
    return -1;
  }
  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);
  
  TcpSocket lst_sock;
  CHECK_RET(lst_sock.Socket());
  CHECK_RET(lst_sock.Bind(ip, port));
  CHECK_RET(lst_sock.Listen());
  while(1) {
    TcpSocket new_sock;
    bool ret = lst_sock.Accept(&new_sock);
    if (ret == false) {
      continue;
    }
    std::string buf;
    new_sock.Recv(&buf);
    std::cout << "cli say" << buf << std::endl;
    buf.clear();
    std::cout << "srv say";
    std::cin >> buf;
    new_sock.Send(buf);
  }
  lst_sock.Close();
  return 0;
}
