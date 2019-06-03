#include <mynet.h>

#define PORT 50000
#define BUFSIZE 256

void server_send(int sock_accepted,char *buf,int strsize){
  if( send(sock_accepted, buf,strsize,0)== -1 ){
    fprintf(stderr,"send()");
    exit(EXIT_FAILURE);
  }
}

void server_receive(int sock_accepted,char *buf,int strsize){
  if((strsize=recv(sock_accepted,buf,BUFSIZE,0)) == -1){
  fprintf(stderr,"recv()");
  exit(EXIT_FAILURE);
  }
}

void separate_op(char **p , char *buf){
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
    strcpy(s_buf,"\0");
  }
}

void cmd_type(int sock_accepted,char *buf[2]){
  char *op1,*op2;
  char cmd[100];
  char *blank = " ";
  FILE *fp;
  char s_buf[BUFSIZE];
  int strsize;
  char cmd_buf[BUFSIZE];
  char str[40];

  

  op1 = strtok(buf[1],"/");
  op2 = strtok(NULL,"/");

  if((strcmp(op1,"..")==0 || op1 == NULL )){
    strcpy(str,"error\n");
    server_send(sock_accepted,str,strlen(str));
  }else{
    strcpy(cmd,"cat");
    strcat(cmd,blank);
    strcat(cmd,op1);

    if((fp=popen(cmd,"r")) == NULL){
      perror("error");
      exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
      fgets(s_buf, sizeof(s_buf),fp);
      strsize = strlen(s_buf);
      server_send(sock_accepted,s_buf,strsize);
      strcpy(s_buf,"\0");
    }

  }

}

void cmd_exit(int sock_accepted){
  close(sock_accepted);
  exit(EXIT_SUCCESS);
}


void judge_code(int sock_accepted,char *buf[2]){
  char str[40];

  if( (strcmp(buf[0],"list") == 0)){
    cmd_list(sock_accepted);
  }else if( (strcmp(buf[0],"type") == 0)){
    cmd_type(sock_accepted,buf);
  }else if( (strcmp(buf[0],"exit") == 0)){
    cmd_exit(sock_accepted);
  }else{
    strcpy(str,"No such command!\n");
    server_send(sock_accepted,str,strlen(str));
  }
}

void check_password(int sock_accepted,char *buf,int strsize){
  int count = 0;
  bool key = false;
  char *op_token[2];
  char *pass_key="password";
  char str[40];

  strcpy(str,"--please your password-->");
  while(key == false){
    server_send(sock_accepted,str,strlen(str));
    server_receive(sock_accepted,buf,strsize);
    separate_op(op_token,buf);

    if((strcmp(op_token[0],pass_key)==0)){
      strcpy(str,"success!!\n");
      server_send(sock_accepted,str,strlen(str));
      key = true;
    }else{
        strcpy(str,"password is woring\n");
        server_send(sock_accepted,str,strlen(str));
        count++;
        if(count>=3){
        strcpy(str,"you made a mistake three times\n");
        server_send(sock_accepted,str,strlen(str));
        cmd_exit(sock_accepted);
        }        
    }
    strcpy(op_token[0],"\0");
    strcpy(str,">");
  }
}


int main()
{
  struct sockaddr_in my_adrs;
  int sock_listen, sock_accepted;
  char buf[BUFSIZE];
  char *op_token[2];
  int strsize;
  char str = '>' ;

  sock_listen = init_tcpserver(PORT,5);
  sock_accepted = accept(sock_listen,NULL,NULL);
  close(sock_listen);

  check_password(sock_accepted,buf,strsize);

  do{
    server_send(sock_accepted,&str,1);
    server_receive(sock_accepted,buf,strsize);
    separate_op(op_token,buf);
    judge_code(sock_accepted,op_token);
  }while(1); 
}
