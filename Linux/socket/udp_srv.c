#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
  uint16_t port = 9000;
  char *ip = "192.168.96.129";
  //chuangjian
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    perror("socket error");
    return -1;
  }
  //bind
  struct sockaddr_in addr;
  addr.sin_family =AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);
  socklen_t len = sizeof(struct sockaddr_in);
  int ret = bind(sockfd, (struct sockaddr*)&addr, len);
  if (ret < 0) {
    perror("bing error");
    return -1;
  }
  //recv
  char tmp[4096] = {0};
  struct sockaddr_in cli_addr;
  char cli_ip[24] = {0};
  uint16_t cli_port = 0;
  ret = recvfrom(sockfd, tmp, 4096, 0, (struct sockaddr*)&cli_addr, &len);
  if (ret < 0) {
    perror("recv error");
    return -1;
  }
  strcpy(cli_ip, inet_ntoa(cli_addr.sin_addr));
  cli_port = ntohs(cli_addr.sin_port);
  printf("port %s\n", tmp);
  //fasong 
  ret = sendto(sockfd, tmp, ret, 0, (struct sockaddr*)&cli_addr, len);
  if (ret < 0) {
    perror("sendto error");
    return -1;
  }
  close(sockfd);
  return 0;
}
