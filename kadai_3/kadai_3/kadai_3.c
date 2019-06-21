#include "mynet.h"
#include <sys/wait.h>

#define BUFSIZE 50   /* バッファサイズ */

void child_process(int sock_listen,int *sock_accepted){
  char buf[BUFSIZE];
  int strsize;
  for(;;){
  /* クライアントの接続を受け付ける */
  *sock_accepted = accept(sock_listen, NULL, NULL);
    do{
        /* 文字列をクライアントから受信する */
        if((strsize=recv(*sock_accepted, buf, BUFSIZE, 0)) == -1){
          exit_errmesg("recv()");
        }

        /* 文字列をクライアントに送信する */
        if(send(*sock_accepted, buf, strsize, 0) == -1 ){
          exit_errmesg("send()");
        }
      }while( buf[strsize-1] != '\n' ); /* 改行コードを受信するまで繰り返す */
    close(*sock_accepted);
  }
}

void parrent_process(pid_t child,int *child_pid,int count,int sock_accepted){
  printf("Client is accepted.[%d]\n", child);
  child_pid[count]=child;
  close(sock_accepted);
}

void failed_fork(sock_listen){
  close(sock_listen);
  exit_errmesg("fork()");
}

void cmnd_check(){

}

int main(int argc, char *argv[])
{
  int port_number;
  int child_number;
  int sock_listen, sock_accepted;
  int *child_pid;
  pid_t child;
  int count;
  char str[256];
  char cmnd[256];
  int i;

  /* 引数のチェックと使用法の表示 */
  if( argc != 3 ){
    fprintf(stderr,"Usage: %s Port_number\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port_number = atoi(argv[1]);
  child_number = atoi(argv[2]);
  child_pid=(int *)malloc(sizeof(int)*child_number);

  /* サーバの初期化 */
  sock_listen = init_tcpserver(port_number, 5);

  for(count=0;count<child_number;count++){
    
    if( (child=fork() ) == 0 ){
      child_process(sock_listen,&sock_accepted);
    }else if( child > 0 ){
      parrent_process(child,child_pid,count,sock_accepted);
    }else{
      failed_fork(sock_listen);
    }

  }

  for(i=0;i<count;i++){
    printf("child_pid[%d]=%d\n",i,child_pid[i]);
  }

  while(1){
    printf("-->");
    fgets(str,sizeof(str), stdin);
    str[strlen(str)-1]='\0';
    if(strcmp(str,"exit")==0){
      for(i=0;i<count;i++){
        printf("kill child. [%d]\n", child_pid[i]);
        sprintf(cmnd,"kill %d",child_pid[i]);
        system(cmnd);
      }
       break;
    }
  }
 
  free(child_pid);

} 