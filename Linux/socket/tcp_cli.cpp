#include "tcpsocket.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "usage port"<< std::endl;
    return -1;
  }
  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);

  TcpSocket lst_sock;
  CHECK_RET(lst_sock.Socket());
  CHECK_RET(lst_sock.Connect(ip, port));
      while (1) {
      std::string buf;
      std::cout << "cli say" << std::endl;
      std::cin >> buf;
      lst_sock.Send(buf);

      buf.clear();
      lst_sock.Recv(&buf);
      std::cout << "srv say" << buf << std::endl;
      }
      lst_sock.Close();
      return 0;
      }
