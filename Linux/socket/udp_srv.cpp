#include <iostream>
#include <string>
#include "udpsocket.hpp"
#define CHECK_RET(q) if((q)!=false){return -1;}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./udp_srv ip port\n";
    return -1;
  }
  uint16_t port = std::stoi(argv[2]);
  std::string ip = argv[1];
  UdpSocket srv_sock;
  //创建
  CHECK_RET(srv_sock.Socket());
  //绑定
  CHECK_RET(srv_sock.Bind(ip, port));
  //发送 and 接收
  while (1) {
    std::string buf;
    std::string peer_ip;
    uint16_t peer_port;
    CHECK_RET(srv_sock.Recv(&buf, &peer_ip, &peer_port));
    std::cout << "client "<< peer_ip<<" "<<peer_port << "say " << buf << std::endl;
    //发送数据
    buf.clear();
    std::cout << "server say";
    std::cin >> buf;
    CHECK_RET(srv_sock.Send(buf, peer_ip, peer_port));
  }
  srv_sock.Close();
  return 0;
}
