#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0){
		printf("socket create failed \n");
		exit(-1);
	}
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		printf("socket bind failed \n");
		exit(-2);
	}
	if(listen(listenfd, SOMAXCONN) < 0){
		printf("listen failed\n");
		exit(-3);
	}
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int connect = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
	if(connect < 0){
		printf("accept failed \n");
		exit(-4);
	}
	char recvbuf[1024 * 1024];
	while(1){
		memset(recvbuf, 0, sizeof(recvbuf));
		int ret = read(connect, recvbuf, sizeof(recvbuf));
		printf("%s\n", recvbuf);
		write(connect, recvbuf, ret);
	}
	close(connect);
	close(listenfd);
	return 0;
}
