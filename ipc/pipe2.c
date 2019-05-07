/*************************************************************************
	> File Name: pipe2.c
	> Author: ssh
	> Mail: sunshihao163@163.com 
	> Created Time: Mon 15 Apr 2019 02:43:32 PM CST
 ************************************************************************/

/*匿名管道实现，命令链接，数据传输*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int pipefd[2];
	int ret = pipe(pipefd);
	if(ret < 0){
		perror("pipe error");
		return -1;
	}

	int pid1 = fork();
	if(pid1 == 0){
		//ls
		//因为ls的结果是写入到标准输出进行打印的
		//但是想要实现将数据交给另一个进程，需要将数据写入管道而不是标准
		//输出，因此对标准输出进行重定向-->重定向到管道写入端
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execlp("ls", "ls", NULL);
		exit(0);
	}

	int pid2 = fork();
	if(pid2 == 0){
		//grep make
		//因为grep要从标准输入读取数据，但是我们的目的是让grep从管道读取
		//处理结果进行过滤，这时候就要对标准输入进行重定向
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		execlp("grep", "grep", "pi", NULL);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}

