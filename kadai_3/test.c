#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  int num;
  int i;
  char str[256];
  int *p;
  system("ls");
  printf("-->");
  scanf("%d",&num);
  printf("input[%d]\n",num);

  p = (int *)malloc(sizeof(int)*num);
  for(i=0;i<num;i++){
    printf("p[%d]->",i);
    scanf("%d",&p[i]);
  }
  
  for(i=0;i<num;i++){
    printf("p[%d]=%d\n",i,p[i]);
  }  

  while(1){
    printf("(exit)-->");
    scanf("%s",str);
    printf("%s\n",str);
    if(strcmp(str,"exit")==0){
      break;
    }
    

  }
  
  return 0;
}