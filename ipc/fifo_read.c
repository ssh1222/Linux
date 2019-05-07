/*************************************************************************
	> File Name: fifo_read.c
	> Author: ssh
	> Mail: sunshihao163@163.com 
	> Created Time: Mon 15 Apr 2019 03:11:29 PM CST
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
	//	mode:       创建文件时的权限
	//	返回值：成功：0  失败：-1
	umask(0);
	char *fifo = "./test.fifo";
	int ret = mkfifo(fifo, 0664);
	if(ret < 0){
		//出现错误，如果错误原因不是因为文件已存在，则报错退出
		if(errno != EEXIST){
			perror("mkfifo error");
			return -1;
		}
	}
	printf("i want you, guoxin!\n");
	int fd = open(fifo, O_RDONLY);
	if(fd < 0){
		perror("open error");
		return -1;
	}
	printf("open fifo success!");
	while(1){
		char buf[1024] = {0};
		int ret = read(fd, buf, 1023);
		if(ret > 0){
			printf("client say:[%s]\n", buf);
		}else if(ret == 0){
			printf("write close!\n");
			return -1;
		}else{
			perror("read error");
			return -1;
		}
	}
	close(fd);
	return 0;
}
