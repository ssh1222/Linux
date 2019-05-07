/*************************************************************************
	> File Name: pipe.c
	> Author: ssh
	> Mail: sunshihao163@163.com 
	> Created Time: Mon 15 Apr 2019 02:20:50 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	//int pipe(int pipefd[2]);
	//	pipedf:用于接受管道的操作句柄（文件描述符）
	//	返回值：成功：0  失败：-1
	int pipefd[2];
	int ret = pipe(pipefd);
	if(ret < 0){
		perror("pipe error");
		return -1;
	}

	int pid = fork();
	if(pid < 0){
		perror("fork error");
		return -1;
	}else if(pid == 0){
		//子进程只写数据，将读端关闭，不然会引起read阻塞
		close(pipefd[0]);
		int len = 0;
		while(1){
			char *ptr = "ni hao!";
			printf("write len: %d\n", len);
			int ret = write(pipefd[1],ptr,strlen(ptr));
			len += ret;
			printf("write len: %d\n", len);
		}
	}else{
		close(pipefd[1]);
		//父进程读数据
		char buf[1024] = {0};
		int ret = read(pipefd[0], buf, 1023);
		printf("child read buf[%d-%s]\n", ret, buf);
	}
	return 0;
}
