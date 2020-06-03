#include <cstdio>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define CHECK_RET(q) if((q)==false){return -1;}

class TcpSocket {
  public:
    TcpSocket()
      :_sockfd(-1)
    {}
    //创建监听套接字
    bool Socket() {
      _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (_sockfd < 0) {
        perror("socket error");
        return false;
      }
      return true;
    }
    //绑定地址信息
    bool Bind(std::string &ip, uint16_t port){
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
    //开始监听
    bool Listen(int backlog1 = 5) {
      //listen 套接字描述符 最大并发连接数
      int ret = listen(_sockfd, backlog1);
      if (ret < 0 ) {
        perror("listen error");
        return false;
      }
      return true;
    }
    //接收信息为两端建立专属套接字
    bool Accept(TcpSocket *new_sock, std::string *ip=NULL, uint16_t *port=NULL) {
      //新建套接字描述符 = accept 监听套接字描述符 客户端地址信息 地址长度
      struct sockaddr_in addr;
      socklen_t len = sizeof(struct sockaddr_in);
      int new_fd = accept(_sockfd, (struct sockaddr*)&addr, &len);
      if (new_fd < 0) {
        perror("accept error");
        return false;
      }
      new_sock->_sockfd = new_fd;
      if (ip != NULL) {
        *ip = inet_ntoa(addr.sin_addr);
      }
      if (port != NULL) {
        *port = ntohs(addr.sin_port);
      }
      return true;
    }
    //接收信息
    bool Recv(std::string *buf) {
      char tmp[4096] = {0};
      int ret = recv(_sockfd, tmp, 4096, 0);
      if (ret < 0) {
        perror("recv error");
        return false;
      }else if (ret == 0) {
        printf("connect broken\n");
        return false;
      }
      buf->assign(tmp, ret);
      return true;
    }
    //发送信息
    bool Send(std::string &data) {
      int ret = send(_sockfd, data.c_str(), data.size(), 0);
      if (ret < 0) {
        perror("send error");
        return false;
      }
      return true;
    }
    //客户端向服务端建立连接请求
    bool Connect(const std::string &ip, uint16_t port) {
      //connect 描述符 服务端地址信息 服务端端口号 
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(addr);
      int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        perror("connect error");
        return false;
      }
      return true;
    }
    //关闭套接字
    bool Close() {
      if (_sockfd > 0) {
        close(_sockfd);
        _sockfd = -1;
      }
      return true;
    }

  private:
    int  _sockfd;
};
