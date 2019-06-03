#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
  char *command = "cat";
  char cmd[100];
  char  *add = " aaa.txt";
  int res;
  strcpy(cmd,command); 
  printf("command=%s\n",cmd);
  strcat(cmd,add);
  printf("command=%s\n",cmd);
//  command = "ls -al";

  system(cmd);

  return 0;
}
