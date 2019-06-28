#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>//closeを使うため
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256 //マクロ

void DieWithError(char *errorMessage){
	perror(errorMessage);//標準エラー出力にエラーメッセージを出す
	exit(1);//≒終了ステータス。エラーの時は１以上を返す
	
}

void commun(int sock){//原則としてプログラムは上から下に読み込まれるので、どういう関数かを教えるこの関数はmainの上に書いたほうがよい
	char buf[BUF_SIZE];
	int len_r;
	char response[BUF_SIZE];
	//int len = r;
	char *message = "お返しでーす";
	
	while((len_r = recv(sock,buf,BUF_SIZE,0))>0){
		
		buf [len_r]='\0';		
		printf("%s\n,buf");
		if (strstr(buf,"\r\n\n\n")){//　\r　・・・ 同じ行の先頭に戻る
			printf("received HTTP Request.\n");
			break;
		}
	if((len_r = recv(sock,buf,BUF_SIZE,0)) <= 0)DieWithError("recv() failed");
	}
	buf[len_r] = '\0';//nul
	printf("%s\n",buf);//%s 文字列の出力
	
	if(len_r <= 0){
		DieWithError("recieved() failed,");}
	
	sprintf(response," HTTP /1.1 200 OK \r\n");
	
	if(send(sock,response,strlen(response),0)!=strlen(response))DieWithError("send()sent a message of unexpected bytes");
	
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send()sent a message of unexpected bytes");
}
//send関数の引数　ソケットディスクリプタ、メッセージ、メッセージの文字数、0(固定)


int main(int argc,char **argv){
	int servSock = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddress;//自分のアドレスをせってい
	struct sockaddr_in clientAddress;
	int cliSock;
	unsigned int szClientAddr;
	
	if(servSock<0)DieWithError("socket() failed");
	
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddress.sin_port = htons(80);
	
	bind(servSock,(struct sockaddr*)&servAddress,sizeof(servAddress));
	listen(servSock,5);//接続されるのを待つ関数。//6まで
	
	close(servSock);//ソケットを破棄

	while(1){
		szClientAddr = sizeof(clientAddress);
		cliSock = accept(servSock,(struct sockaddr *)&clientAddress,&szClientAddr);
		commun(cliSock);
		
		close(cliSock);
	}
	close(servSock);
	return 0;
}



