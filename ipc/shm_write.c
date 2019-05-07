/*************************************************************************
	> File Name: shm_read.c
	> Author: ssh
	> Mail: sunshihao163@163.com 
	> Created Time: Mon 15 Apr 2019 03:51:10 PM CST
 ************************************************************************/

/*共享内存的基本使用*/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/shm.h>
#define IPC_KEY 0x12345678
#define PROJ_ID 0x12345678
#define SHM_SIZE 4096
int main(){
	//1.创建/打开共享内存
	//key_t ftok(const char *pathname, int proj_id);
	//	通过文件名与一个proj_id生成一个key值
	//int shmget(key_t key, size_t size, int shmflg);
	//	key：	共享内存标识符
	//	size：	共享内存大小
	//	shmflg：选项标志
	//		IPC_CREAT	存在则打开，不存在则创建
	//		ICP_EXCL	与IPC_CREAT同用，若存在则报错，不存在则创建
	//		mode_flags	权限
	//	返回值：句柄：正整数	失败：-1
	//	key_t key = ftok(".", PROJ_ID);
	int shmid = shmget(IPC_KEY, SHM_SIZE, IPC_CREAT|0664);
	if(shmid < 0){
		perror("shmid error");
		return -1;
	}
	//2.将共享内存映射到虚拟地址空间
	//void *shmat(int shmid, const void *shmaddr, int shmflg);
	//	shmid:	共享内存创建返回的句柄
	//	shmaddr:映射首地址-通常置NULL
	//	shmflg:	
	//		0		   可读可写
	//		SHM_RDONLY 只读
	//	返回值： 成功：映射首地址    失败：(void*)-1
	char *shm_start = (char*)shmat(shmid, NULL, 0);
	if(shm_start == (void*)-1){
		perror("shmat erroe");
		return -1;
	}
	//3.进行内存操作
	int i = 0;
	while(1){
		sprintf(shm_start, "ni hao!", i++);
		sleep(1);
	}
	//4.解除映射关系
	//int shmdt(const void *shmaddr);
	//	shmaddr:	映射首地址
	//	返回值：成功：0		失败：-1
	shmdt(shm_start);
	//5.删除共享内存
	//int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	//	shmid:	句柄
	//	cmd:	操作
	//		IPC_RMID	删除共享内存
	//	buf:	设置/获取属性信息
	//		想获取传入首地址，不想获取了置NULL
	//	共享内存并不会被立即删除，而是判断当前连接数，若不为0，则拒绝后
	//	续连接，直到为0的时候才会删除这块共享内存
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
