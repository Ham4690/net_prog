/*
   Proxyを介してHTTPサーバと対話するクライアントプログラム
　　（利用者が自らHTTPを入力する必要がある）
*/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024    /* バッファサイズ */

// ./kadai_1 http://www.is.kit.ac.jp/ 
//or
// ./kadai_1 http://www.is.kit.ac.jp/ proxy.cis.kit.ac.jp 8080


int main(int argc, char *argv[])
{
  struct hostent *server_host;
  struct sockaddr_in proxy_adrs;

  int tcpsock;
  int PROXYPORT;
  char *word;
  char *proxyname; /* プロキシサーバ */
  char k_buf[BUFSIZE], s_buf[BUFSIZE], r_buf[BUFSIZE];
  int strsize;
  char *tp;  
  size_t length;
  char url[BUFSIZE]; 
//  char server_name[];
  int conten_len;
  char cmp_word[BUFSIZE];

  bool flag_server_name = false;
  bool flag_content_length = false;



  //引数の要素数確認
  if(argc>4){
    printf("Number of argument is too many \n");
    exit(EXIT_FAILURE);
  }else if((argc%2)!=0){
    printf("Not enough number of argument \n");
    exit(EXIT_FAILURE);
  }

  //引数の数によっての処理判別
  switch(argc){
    case 2://第2引数および第3引数が指定されていない場合
      sprintf(url,"%s",argv[1]);
//      puts( url );
      tp = argv[1];
      strtok(tp,"/");
      proxyname = strtok( NULL,"/");

      printf("%s\n",proxyname);
      PROXYPORT = 80;
 
      /* サーバ名をアドレス(hostent構造体)に変換する */
      if((server_host = gethostbyname( proxyname ) ) == NULL){
        fprintf(stderr,"gethostbyname()");
        exit(EXIT_FAILURE);
      }
      break;

    case 4://引数が指定されている場合
      proxyname = argv[2];
      sscanf(argv[3],"%d",&PROXYPORT);

      /* サーバ名をアドレス(hostent構造体)に変換する */
      if((server_host = gethostbyname( proxyname ) ) == NULL){
        fprintf(stderr,"gethostbyname()");
        exit(EXIT_FAILURE);
      }
      break;

    default :
      break;
  }

  printf("proxyname=%s,PROXYPORT=%d\n",proxyname,PROXYPORT);

  /* サーバの情報をsockaddr_in構造体に格納する */
  memset(&proxy_adrs, 0, sizeof(proxy_adrs));
  proxy_adrs.sin_family = AF_INET;
  proxy_adrs.sin_port = htons(PROXYPORT);

  memcpy(&proxy_adrs.sin_addr, server_host->h_addr_list[0], server_host->h_length);

  /* ソケットをSTREAMモードで作成する */
  if((tcpsock = socket(PF_INET, SOCK_STREAM, 0)) == -1){
    fprintf(stderr,"socket()");
    exit(EXIT_FAILURE);
  }

  /* ソケットにサーバの情報を対応づけてサーバに接続する */
  if(connect(tcpsock,(struct sockaddr *)&proxy_adrs, sizeof(proxy_adrs))   == -1){
    fprintf(stderr,"connect");
    exit(EXIT_FAILURE);
  }


///////////////////////////////////////////////////////////////////////////////
  /* キーボードから文字列を入力してサーバに送信 */
  sprintf(s_buf,"HEAD / HTTP/1.1\r\n");
  printf("\n\n%s",s_buf);
  strsize = strlen(s_buf);
  if(send(tcpsock, s_buf, strsize,0) == -1 ){
      fprintf(stderr,"send()1");
      exit(EXIT_FAILURE);
  }
  

  sprintf(s_buf,"Host:%s\r\n",proxyname);
  printf("%s\n\n",s_buf);
  strsize = strlen(s_buf);
  if(send(tcpsock, s_buf, strsize,0) == -1 ){
      fprintf(stderr,"send()2");
      exit(EXIT_FAILURE);
  }
  


  send(tcpsock, "\r\n", 2, 0); /* HTTPのメソッド（コマンド）の終わりは空行 */

  /* サーバから文字列を受信する */
  if((strsize=recv(tcpsock, r_buf, BUFSIZE-1,0)) == -1){
    fprintf(stderr,"recv()");
    exit(EXIT_FAILURE);
  }
  r_buf[strsize] = '\0';

//受信した文字列の選別

printf("%s\n\n",r_buf);

tp = strtok( r_buf,": \n");
sprintf(cmp_word,"%s",tp);
puts(cmp_word);
//printf("cmp_word=%s\n",cmp_word);
//printf("%d\n",strncmp(cmp_word,"HTTP/1.1",8));

while( tp != NULL ){
  tp = strtok(NULL,": \n");
  if( tp != NULL ){
    sprintf(cmp_word,"%s",tp);
//    printf("cmp_word = %s,strlen=%d\n",cmp_word,strlen(cmp_word));
//      puts(tp);
//      printf(tp == "Server");
    if( strncmp(cmp_word,"Content-Length",14) == 0){
      tp = strtok(NULL,": \n");
      printf("cmp_word = %s,strlen=%lu\n",cmp_word,strlen(cmp_word));
      printf("%s:%s\n",cmp_word,tp);
    }else if( strncmp(cmp_word,"Server",4) == 0 ){
      tp = strtok(NULL,": \n");
      printf("cmp_word = %s,strlen=%lu\n",cmp_word,strlen(cmp_word));
      printf("%s:%s\n",cmp_word,tp);
    }
  }

} 
  

                        

 /* 受信した文字列を画面に書く */
//  printf("%s",r_buf);

  close(tcpsock);             /* ソケットを閉じる */
  exit(EXIT_SUCCESS);
}
