#include <mynet.h>

#define PORT 50000
#define BUFSIZE 256

/*

void list(){
  FILE *fp;
  char *cmdline = "ls";
  if((fp=popen(cmdline,"r")) == NULL){
    perror("error");
    exit(EXIT_FAILURE);
  }
  char cmd_buf[BUFSIZE];

  while(!feof(fp)){
    fgets(buf, sizeof(buf),fp);
  }

}


void type(){

}

void exit(){
}
*/

void judge_code(char *buf){
  printf("%s\n",buf);
}

void server_send(int sock_accepted,char *buf,int strsize){
  if( send(sock_accepted, buf,strsize,0)== -1 ){
    fprintf(stderr,"send()");
    exit(EXIT_FAILURE);
  }
}


int main()
{
  struct sockaddr_in my_adrs;

  int sock_listen, sock_accepted;

  char buf[BUFSIZE];
  int strsize;


  sock_listen = init_tcpserver(PORT,5);

  /* クライアントの接続を受け付ける */
  sock_accepted = accept(sock_listen,NULL,NULL);
  close(sock_listen);

  do{
    /* 文字列をクライアントから受信する */
    if((strsize=recv(sock_accepted,buf,BUFSIZE,0)) == -1){
      fprintf(stderr,"recv()");
      exit(EXIT_FAILURE);
    }

    judge_code(buf);

    /* 文字列をクライアントに送信する */
    server_send(sock_accepted, buf,strsize);
    /*
    if( send(sock_accepted, buf,strsize,0)== -1 ){
      fprintf(stderr,"send()");
      exit(EXIT_FAILURE);
    }
    */
  }while( buf[strsize-1] != '\n' ); /* 改行コードを受信するまで繰り返す */

  close(sock_accepted);

  exit(EXIT_SUCCESS);
}
