#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
int main(int argc,char**arev){
	int sock = socket(PF_INET,SOCK_STREAM,0);//�ʐM�p�̐ݔ����J��
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr("10,13,64,20");
	target.sin_port = htons(10001);
	
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	//printf("sock is %d",sock);
	close(sock);	//�I�����ɕ���

	return 0;
}