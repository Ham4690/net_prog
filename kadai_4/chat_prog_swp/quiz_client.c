/*
  quiz_client.c
*/
#include "chat.h"
#include "mynet.h"
#include <stdlib.h>
#include <sys/select.h>

#define S_BUFSIZE 100   /* 送信用バッファサイズ */
#define R_BUFSIZE 100   /* 受信用バッファサイズ */

void quiz_client(char* servername, int port_number)
{
  int sock;
  char s_buf[S_BUFSIZE], r_buf[R_BUFSIZE];
  int strsize;
  fd_set mask, readfds;

  /* サーバに接続する */
  sock = init_tcpclient(servername,port_number);

  printf("Connected.\n");

  /* ビットマスクの準備 */
  // bit 0 :標準入出力を確認
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  FD_SET(sock,&mask);

  for(;;){

    /* 受信データの有無をチェック */
    readfds = mask;
    select(sock+1,&readfds,NULL,NULL,NULL);

    if( FD_ISSET(0, &readfds) ){
      /* キーボードから文字列を入力する */
      fgets(s_buf, S_BUFSIZE, stdin);
      strsize = strlen(s_buf);
      Send(sock, s_buf, strsize, 0);

      memset(&s_buf[0],0x00,sizeof(s_buf) );

    }

    if( FD_ISSET(sock,&readfds ) ){
      /* サーバから文字列を受信する */
      strsize = Recv(sock, r_buf, R_BUFSIZE-1, 0);
      r_buf[strsize] = '\0';
      printf("%s",r_buf);
      fflush(stdout); /* バッファの内容を強制的に出力 */
    }

  }

}