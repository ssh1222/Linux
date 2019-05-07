/*************************************************************************
	> File Name: fifo_write.c
	> Author: ssh
	> Mail: sunshihao163@163.com 
	> Created Time: Mon 15 Apr 2019 03:32:29 PM CST
 ************************************************************************/

/*命名管道的基本使用*/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(){
	//int mkfifo(const char *pathname, mode_t mode);
	//	pathname:   命名管道文件路径名
	//	mode：      创建文件时的权限
	//	返回值： 成功：0  失败： -1
	umask(0);
	char *fifo = "./test.fifo";
	int ret = mkfifo(fifo, 0664);
	if(ret < 0){
		//出先错误，如果错误原因不是因为文件已经存在，则报错退出
		if(errno != EEXIST){
			perror("fifo error");
			return -1;
		}
	}
	printf("fifo success!");
	int fd = open(fifo, O_WRONLY);
	if(fd < 0){
		perror("open error");
		return -1;
	}
	printf("open fifo success!");
	while(1){
		char buf[1024] = {0};
		scanf("%s", buf);
		write(fd, buf, strlen(buf));
		printf("write buf:[%s]\n", buf);
	}
	close(fd);
	return 0;
}
