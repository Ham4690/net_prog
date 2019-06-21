#include "mynet.h"
#include <sys/wait.h>

#define MAX 100
#define BUFSIZE 50   /* バッファサイズ */
#define COMMAND 10

pid_t Fork();
void child_process(int sock_listen, int number);
void multi_fork(int sock_listen, int max_child, pid_t *PID);
void multi_kill(pid_t *PID, int max_child);



int main(int argc, char *argv[])
{
  int port_number;
  int sock_listen, sock_accepted;
  int n_process = 0;
  pid_t child;
  char buf[BUFSIZE];
  int strsize;
  int i;
  int max_child;

  /* 引数のチェックと使用法の表示 */
  if( argc != 3 ){
    fprintf(stderr,"Usage: %s Port_number and max_child_number\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port_number = atoi(argv[1]);
  max_child = atoi(argv[2]);
  //pid_t PID[MAX];
  pid_t *PID;
  if( (PID=(pid_t *)malloc(max_child*sizeof(pid_t)))==NULL ){
      exit_errmesg("malloc()");
    }

  /* サーバの初期化 */
  sock_listen = init_tcpserver(port_number, 5);
  multi_fork(sock_listen, max_child, PID);

}

pid_t Fork(){
 pid_t pid;
 pid = fork();
 if(-1 == pid){
  warn("can not fork");
 }
 return (pid);
}

void child_process(int sock_listen,int number){
    /* クライアントの接続を受け付ける */
 while(1){
    int sock_accepted; 
    int strsize;
    char buf[BUFSIZE];
    sock_accepted = accept(sock_listen, NULL, NULL);
    
       /* クライアントとのやり取り*/
 do{
     /* 文字列をクライアントから受信する */
     if((strsize=recv(sock_accepted, buf, BUFSIZE, 0)) == -1){
       fprintf(stderr,"recv()");
       exit(EXIT_FAILURE);
     }

     /* 文字列をクライアントに送信する */
     if(send(sock_accepted, buf, strsize, 0) == -1 ){
       fprintf(stderr,"send()");
       exit(EXIT_FAILURE);
     }
   }while( buf[strsize-1] != '\n' ); /* 改行コードを受信するまで繰り返す */
 close(sock_accepted);
 printf("break the connection (number:[%d])\n", number + 1);
 }

}

void multi_fork(int sock_listen, int max_child, pid_t *PID){
 int i = 0;
 for(i = 0; i<max_child; i++){
  pid_t child = Fork();
  if(child == -1){
   break;
  }
  /* child process */
  else if(child == 0){
   child_process(sock_listen, i);
   exit (EXIT_SUCCESS);
  }
  
  /* parent's process */
  else {
     printf("child process is prepared.[%d]\n", child);
     PID[i]=child;
     
  }
  
 }
 char exit_command[COMMAND];
 while(1){
   fgets(exit_command , COMMAND , stdin);
   exit_command[strlen(exit_command)-1]='\0';
   if((strcmp(exit_command, "exit")) == 0){
    multi_kill(PID, max_child);
    return;
   } 
         }
}

void multi_kill(pid_t *PID, int max_child){
 int i;
 for(i=0; i<max_child; i++){
  kill(PID[i], SIGKILL);
 }
 free(PID);
}