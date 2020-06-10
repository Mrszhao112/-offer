#include <stdio.h>
#include <string.h>
int main () {
  FILE *fp = NULL;
  fp = fopen("./test.txt", "r+");// wrad+ 设置打开文件时的一些权限
  if (fp == NULL) {
    perror("open error");
    return -1;
  }
 // fseek(fp, 10, SEEK_END);

  char buf[] = "Its a fine day";
  int ret = fwrite(buf, strlen(buf), 1, fp);
  if (ret == 0) {
    perror("fwrite error");
    return -1;
  }
  printf("ret is %d \n", ret);
 
  fseek(fp, 0, SEEK_SET);
  
  char tmp[1024] = {0};
  ret = fread(tmp, 1, 1023, fp);
  if (ret == 0) {
    printf("havn't data or errro");
  }
  printf("ret: %d-%s \n", ret, tmp);
  fclose(fp);
  return 0;
}
