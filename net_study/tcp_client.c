//
// TCP client
//
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// クライアントの接続サーバ情報

struct client_info
{
    /* data */
    unsigned short sv_port;
    char *sv_ipaddr;
    char *msg;
};
typedef struct client_info cl_info_t;

/*!
 * @brief      TCP接続してメッセージを送る
 * @param[in]  sd       ソケットディスクリプタ
 * @param[in]  sv_addr  接続先サーバ情報
 * @param[in]  msg      送信するメッセージ
 * @param[out] errmsg   エラーメッセージ格納先
 * @return     成功ならば0、失敗ならば-1を返す。
 */
static int
tcp_send_msg(int sd, struct sockaddr_in *sv_addr, char *msg,
             char *errmsg)
{
    int rc = 0;
    int msg_len = strlen(msg) + 1;

    /* サーバに接続する */
    rc = connect(sd, (struct sockaddr *)sv_addr, sizeof(*sv_addr));
    if(rc != 0){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    /* メッセージの送信 */
    rc = send(sd, msg, msg_len, 0);
    if(rc != msg_len){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    return(0);
}

/*!
 * @brief      TCPクライアント実行
 * @param[in]  info   クライアント接続情報
 * @param[out] errmsg エラーメッセージ格納先
 * @return     成功ならば0、失敗ならば-1を返す。
 */
static int
tcp_client(cl_info_t *info, char *errmsg)
{
    struct sockaddr_in sv_addr = {0};
    int sd = 0;
    int rc = 0;

    /* ソケットの生成 : TCPを指定する */
    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sd < 0){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    /* サーバのアドレス構造体を作成する */
    memset(&sv_addr, 0, sizeof(sv_addr));
    sv_addr.sin_family = AF_INET;
    sv_addr.sin_addr.s_addr = inet_addr(info->sv_ipaddr);
    sv_addr.sin_port = htons(info->sv_port);

    /* 文字列を送信する */
    rc = tcp_send_msg(sd, &sv_addr, info->msg, errmsg);

    /* ソケットの破棄 */
    if(sd != 0) close(sd);

    return( rc );
}

/*!
 * @brief      初期化処理。IPアドレスとポート番号を設定する。
 * @param[in]  argc   コマンドライン引数の数
 * @param[in]  argv   コマンドライン引数
 * @param[out] info   クライアント接続情報
 * @param[out] errmsg エラーメッセージ格納先
 * @return     成功ならば0、失敗ならば-1を返す。
 */
static int
initialize(int argc, char *argv[], cl_info_t *info, char *errmsg)
{
    if(argc != 4){
        sprintf(errmsg, "Usage: %s <ip-addr> <port> <msg>", argv[0]);
        return(-1);
    }

    memset(info, 0, sizeof(cl_info_t));
    info->sv_ipaddr = argv[1];
    info->sv_port   = atoi(argv[2]);
    info->msg       = argv[3];

    return(0);
}

/*!
 * @brief   main routine
 * @return  成功ならば0、失敗ならば-1を返す。
 */
int
main(int argc, char *argv[])
{
    int rc = 0;
    cl_info_t info = {0};
    char errmsg[256];

    rc = initialize(argc, argv, &info, errmsg);
    if(rc != 0){
        fprintf(stderr, "Error: %s\n", errmsg);
        return(-1);
    }

    rc = tcp_client(&info, errmsg);
    if(rc != 0){
        fprintf(stderr, "Error: %s\n", errmsg);
        return(-1);
    }

    return(0);
}

