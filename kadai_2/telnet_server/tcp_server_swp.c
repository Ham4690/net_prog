#include <mynet.h>

#define PORT 50000
#define BUFSIZE 256


/*

void type(){

}

*/

void server_send(int sock_accepted,char *buf,int strsize){
  if( send(sock_accepted, buf,strsize,0)== -1 ){
    fprintf(stderr,"send()");
    exit(EXIT_FAILURE);
  }
}

void separate_op(char **p , char *buf,int arg_num){
  p[0] = strtok(buf,"\n\r ");
  p[1] = strtok(NULL,"\n\r ");
}


void cmd_list(int sock_accepted){
  FILE *fp;
  char *cmdline = "ls";
  char s_buf[BUFSIZE];
  int strsize;
  if((fp=popen(cmdline,"r")) == NULL){
    perror("error");
    exit(EXIT_FAILURE);
  }
  char cmd_buf[BUFSIZE];

  while(!feof(fp)){
    fgets(s_buf, sizeof(s_buf),fp);
    strsize = strlen(s_buf);
    server_send(sock_accepted,s_buf,strsize);
  }
}

void cmd_exit(int sock_accepted){
  close(sock_accepted);
  exit(EXIT_SUCCESS);
}


void judge_code(int sock_accepted,char *buf){
  printf("%s\n",buf);

  if( (strcmp(buf,"list") == 0)){
    cmd_list(sock_accepted);
  }else if( (strcmp(buf,"type") == 0)){
//  type()
  }else if( (strcmp(buf,"exit") == 0)){
    cmd_exit(sock_accepted);
  }

}


int main()
{
  struct sockaddr_in my_adrs;

  int sock_listen, sock_accepted;

  char buf[BUFSIZE];
  char *op_token[2];
  int strsize;
  int arg_num=0;


  sock_listen = init_tcpserver(PORT,5);

  /* クライアントの接続を受け付ける */
  sock_accepted = accept(sock_listen,NULL,NULL);
  close(sock_listen);

  do{

    //server_send(sock_accepted, p,strsize);

    /* 文字列をクライアントから受信する */
    if((strsize=recv(sock_accepted,buf,BUFSIZE,0)) == -1){
      fprintf(stderr,"recv()");
      exit(EXIT_FAILURE);
    }

    separate_op(op_token,buf,arg_num);
//    printf("%s %s\n",op_token[0],op_token[1]);
    judge_code(sock_accepted,op_token[0]);
//    list(sock_accepted);


    /* 文字列をクライアントに送信する */
    //server_send(sock_accepted, p,strsize);

  }while(1); /* 改行コードを受信するまで繰り返す */
//  }while( buf[strsize-1] != '\n' ); /* 改行コードを受信するまで繰り返す */

  close(sock_accepted);

  exit(EXIT_SUCCESS);
}
