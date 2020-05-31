#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main () {
  //chuangjian
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    perror("socket error");
    return -1;
  }
  //绑定
  //客户端让操作系统自己绑定
  //发送
  struct sockaddr_in srv_addr;
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(9000);
  srv_addr.sin_addr.s_addr = inet_addr("192.168.96.129");
  socklen_t len = sizeof(struct sockaddr_in);
  char data[1024] = {0};
  fgets(data, 1024, stdin);
  sendto(sockfd, &data, strlen(data), 0, (struct sockaddr*)&srv_addr, len);
  //接收
  char buf[1024] = {0};
  
  recvfrom(sockfd, buf, 1023, 0, (struct sockaddr*)&srv_addr, &len);
  printf("server say%s\n",buf);
  close(sockfd);
  return 0;
}
