#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>//close���g������
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256 //�}�N��

void DieWithError(char *ErrorMessage){
	perror(ErrorMessage);//�W���G���[�o�͂ɃG���[���b�Z�[�W���o��
	exit(1);//���I���X�e�[�^�X�B�G���[�̎��͂P�ȏ��Ԃ�
	
}

void commun(int sock){//�����Ƃ��ăv���O�����͏ォ�牺�ɓǂݍ��܂��̂ŁA�ǂ������֐����������邱�̊֐���main�̏�ɏ������ق����悢
	
	
	
	char buf[BUF_SIZE];
	//int len_r = recv(sock,buf,BUF_SIZE,0);
	int len_r;
	if(len_r<=0)DieWithError("recv()failed!");
	
	buf[len_r] = '\0';//nul
	printf("%s\n",buf);//%s ������̏o��
	
	if(send(sock,buf,strlen(buf),0)!=strlen(buf))DieWithError("send()sent a message of unexpected bytes");
}
//send�֐��̈����@�\�P�b�g�f�B�X�N���v�^�A���b�Z�[�W�A���b�Z�[�W�̕������A0(�Œ�)


int main(int argc,char **argv){
	
	int servSock = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddress;//�����̃A�h���X�������Ă�
	struct sockaddr_in clientAddress;
	int cliSock;
	unsigned int szClientAddr;
	
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddress.sin_port = htons(80);
	
	bind(servSock,(struct sockaddr *)&servAddress,sizeof(servAddress));
	listen(servSock,5);//�ڑ������̂�҂֐��B//6�܂�
	
	close(servSock);//�\�P�b�g��j��

	while(1){
		szClientAddr = sizeof(clientAddress);
		cliSock = accept(servSock,(struct sockaddr *)&clientAddress,&szClientAddr);
		commun(cliSock);
		
		
	}
	

	return 0;
}//gcc -o server server.c



