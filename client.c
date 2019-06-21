#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define BUF_SIZE 256

void DieWithError(char *errorMessage) {
	perror(errorMessage);
	exit(1);
}

void commun (int sock) {
	char buf[BUF_SIZE];
	int len_r;
	if ((len_r = recv(sock, buf, BUF_SIZE, 0)) <= 0)
		DieWithError(“recv() failed”);
	buf[len_r] = ‘\0’;
	printf( “%s\n”, buf );
	
	if (send(sock, buf, strlen(buf), 0) != strlen(buf))
		DieWithError(“send() sent a message of unexpected bytes”);
}

int main(int arg0, char **argv) {
	char buf[BUF_SIZE];
	int i;
	
	/***********************/
	/*  クライアント情報の保存用  */
	/***********************/
	struct sockaddr_in clientAddress
	unsinged int szClientAddr;
	int cliSock;

	/***********************/
	/*  待ち受けソケットの作成  */
	/***********************/
	int servSock = socket(PF_INET, SOCK_STREAM, 0);

	/******************/
	/*  マシン情報作成  */
	/******************/
	struct sockaddr_in servAddress;

	servAddress.sin_family      = PF_INET;
	servAddress.sin_port        = (in_port_t)htons(10001);  // 待ち受けソケットのポート番号
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);        // 待ち受けるための（自分の）IPアドレス（普段はINADDR_ANY）

	/*********************************/
	/* 待ち受けソケットにマシンの情報をセット  */
	/*********************************/
	bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

	/********************/
	/*   待ち受け開始   */
	/********************/
	listen(servSock, 5);

	while(1) {
		szClientAddr = sizeof(clientAddress);
		cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);
		
		/****************/
		/* 　　通信開始    */
		/****************/
		
		commun(cliSock);

		close(cliSock);
	}

	/********************/
	/* 待受用ソケットを */
	/* 閉じる           */
	/********************/
	close(servSock);

	return 0;
}
/*
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>//closeを使うため
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256 //マクロ

void DieWithError(char *ErrorMessage){
	perror(ErrorMessage);//標準エラー出力にエラーメッセージを出す
	exit(1);//≒終了ステータス。エラーの時は１以上を返す
	
}
void commun(int sock){//原則としてプログラムは上から下に読み込まれるので、どういう関数かを教えるこの関数はmainの上に書いたほうがよい
	char buf[BUF_SIZE];
	int len_r;
	char *message = "banana banana banana banana banana banana banana banana banana banana banana";
	send(sock,message,strlen(message),0);
	
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send()send a message of unexpected bytes");
	
	if(len_r = recv(sock,buf,BUF_SIZE,0)<=0)DieWithError("recv()failed");
	
	buf[len_r] = '\0';//nul
	printf("%s\n",buf);//%s 文字列の出力
}


//send関数の引数　ソケットディスクリプタ、メッセージ、メッセージの文字数、0(固定)

int main(int argc,char**argv){
	
	if(argc != 3)DieWithError("arduments is not available");
	char *server_ipaddr = argv[1];//char *server_ipaddr = "10.13.64.20";
	int server_port = atoi(argv[2]);//int server_port = 10001;
	int sock = socket(PF_INET,SOCK_STREAM,0);//通信用の設備を開く
	if(sock < 0)DieWithError("soclet()failed");
	
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr("server_ipaddr");
	target.sin_port = htons(server_port);
	
	if(connect(sock,(struct sockaddr*)&target,sizeof(target))<0)DieWithError("connect()failed");
	
	commun(sock);
	//printf("sock is %d",sock);
	close(sock);	//終了時に閉じる

	return 0;
}
*/


