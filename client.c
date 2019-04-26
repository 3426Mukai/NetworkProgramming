#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>//closeを使うため
#include<string.h>
void commun(int sock){//原則としてプログラムは上から下に読み込まれるので、どういう関数かを教えるこの関数はmainの上に書いたほうがよい
	char buf[256];
	int len_r;
	char *message = "banana banana banana banana banana banana banana banana banana banana banana";
	send(sock,message,strlen(message),0);
	len_r = recv(sock,buf,256,0);
	buf[len_r] = '\0';//nul
	printf("%s\n",buf);//%s 文字列の出力
}


//send関数の引数　ソケットディスクリプタ、メッセージ、メッセージの文字数、0(固定)

int main(int argc,char**arev){
	int sock = socket(PF_INET,SOCK_STREAM,0);//通信用の設備を開く
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr("10,13,64,20");
	target.sin_port = htons(10001);
	
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	commun(sock);
	//printf("sock is %d",sock);
	close(sock);	//終了時に閉じる

	return 0;
}



