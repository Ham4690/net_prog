#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
  char *command = "ls";
  char cmd[10];
  char  *add = " -al";
  int res;
  strcpy(cmd,command); 
  printf("command=%s\n",cmd);
  strcat(cmd,add);
  printf("command=%s\n",cmd);
//  command = "ls -al";

  system(cmd);

  return 0;
}
