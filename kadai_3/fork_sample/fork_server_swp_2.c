#include "mynet.h"
#include <sys/wait.h>

#define BUFSIZE 50   /* バッファサイズ */



void fork_send(int sock_accepted,char *buf,int strsize){
  if((strsize=recv(sock_accepted, buf, BUFSIZE, 0)) == -1){
    exit_errmesg("recv()");
  }
}

void fork_accept(int sock_accepted,char *buf,int strsize){
  if(send(sock_accepted, buf, strsize, 0) == -1 ){
    exit_errmesg("send()");
  }
}

void fork_failure(int sock_listen){
  close(sock_listen);
  exit_errmesg("fork()");
}

void child_process(int sock_listen,int sock_accepted,char *buf,int strsize){
  for(;;){
      sock_accepted = accept(sock_listen, NULL, NULL);
      close(sock_listen);
      do{
          /* 文字列をクライアントから受信する */
          fork_send(sock_accepted,buf,strsize);
  /*        
            if((strsize=recv(sock_accepted, buf, BUFSIZE, 0)) == -1){
              exit_errmesg("recv()");
            }
  */
          /* 文字列をクライアントに送信する */
          fork_accept(sock_accepted,buf,strsize);
  /*
            if(send(sock_accepted, buf, strsize, 0) == -1 ){
              exit_errmesg("send()");
            }
  */
        }while( buf[strsize-1] != '\n' ); /* 改行コードを受信するまで繰り返す */
        close(sock_accepted);
  }
}


void parent_process(pid_t child,int sock_accepted){
  printf("Client is accepted.[%d]\n", child);
  close(sock_accepted);
}

void make_child(int num,pid_t child,int sock_listen,int sock_accepted,char *buf,int strsize){
  int i;
  if(num <= 0){
    printf("child_number:error\n");
    exit(EXIT_FAILURE);
  }
  for(i=0;i<num;i++){
    if( (child=fork()) == 0 ){
      /* Child process */
      child_process(sock_listen,sock_accepted,buf,strsize);
   }
    else if(child > 0){
      /* parent's process */
      parent_process(child,sock_accepted);
    }
    else{
      /* fork()に失敗 */
      fork_failure(sock_listen);
/*
      close(sock_listen);
      exit_errmesg("fork()");
*/
     }
    }
}

int main(int argc, char *argv[])
{
  int port_number;
  int child_number;
  int sock_listen, sock_accepted;
  pid_t child;
  char buf[BUFSIZE];
  int strsize;

  /* 引数のチェックと使用法の表示 */
  if( argc != 3 ){
    fprintf(stderr,"Usage: %s Port_number\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  port_number = atoi(argv[1]);
  child_number = atoi(argv[2]);

  /* サーバの初期化 */
  sock_listen = init_tcpserver(port_number, 5);
  make_child(child_number,child,sock_listen,sock_accepted,buf,strsize);
/*
  for(;;){
    if( child == 0 ){
//       Child process 
      child_process(sock_listen,sock_accepted,buf,strsize);
   }
    else if(child > 0){
//       parent's process 
      parent_process(n_process,child,sock_accepted);
    }
    else{
//       fork()に失敗 
      fork_failure(sock_listen);

      close(sock_listen);
      exit_errmesg("fork()");

    }


  }
*/

  /* never reached */
}
