#include <cstdio>
#include <string>
#include <unistd.h>
#include <netinet/in.h>//包含地址结构信息
#include <arpa/inet.h>//字节序转换接口
#include <sys/socket.h>//套接字接口信息
class UdpSocket{
  public:
    UdpSocket():_sockfd(-1){}
    bool Socket() {//创建套接字
      //socket(地址域， 套接字类型， 协议类型)
      _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if (_sockfd < 0) {
        perror("socket error");
        return false;
      }
      return true;
    }
    bool Bind(const std::string &ip,  uint16_t port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(struct sockaddr_in);
      int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        perror("bind error");
        return false;

      }
      return true;

    } 

    bool Recv(std::string *buf,  std::string *ip=NULL,  uint16_t *port=NULL) {
      struct sockaddr_in peer_addr;
      socklen_t len = sizeof(struct sockaddr_in);
      char tmp[4096] = {0};
      int ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*)&peer_addr, &len);
      if (ret < 0) {
        perror("recvfrom error");
        return false;

      }
      buf->assign(tmp, ret); 
      if (port != NULL) {
        *port = ntohs(peer_addr.sin_port);

      }
      if (ip != NULL) {
        *ip = inet_ntoa(peer_addr.sin_addr);

      }
      return true;
    }
    bool Send(const std::string &data, const std::string &ip, const uint16_t port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(struct sockaddr_in);
      int ret = sendto(_sockfd, data.c_str(), data.size(), 0, 
          (struct sockaddr*)&addr, len);
      if (ret < 0) {
        perror("sendto error");
        return false;

      }
      return true;

    }

    bool Close(){
      if (_sockfd > 0) {
        close(_sockfd);
        _sockfd = -1;

      }
      return true;
    }
  private:
   int  _sockfd;
};
