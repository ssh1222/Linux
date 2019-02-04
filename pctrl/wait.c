/*进程等待demo
 *  wait waitpid
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int pid = fork();
    if(pid < 0){
	printf("error:%s\n",strerror(errno));
	perror("fork error");
	exit(-1);
    }else if(pid == 0){
	sleep(3);
	exit(199);
    }
    //pid_t wait(int* status);
    //等待任意一个进程的退出
    //status:输出型参数，用于获取子进程退出的返回值
    //返回值：退出的子程序的pid
    //wait(NULL);
    //pid_t waitpid(pid_t pid, int* status, int options);
    //pid:
    //	-1 等待任意子进程退出
    //	>0 等待指定子进程退出
    //status:输出型参数，用于获取子进程退出返回值
    //options：
    //	0 默认等待子进程退出
    //	WNOHANG 如果没有子进程已经退出，则立即返回
    //返回值：>0 退出子进程  pid==0没有子进程退出  <0出错
    int status;
    while(waitpid(pid, &status, WNOHANG) == 0){
	//do other thing
	printf("child not exit!!\n");
	sleep(1);
    }
    //WIFEXITED(status)
    //根据statu判断子进程是否正常退出，正常退出返回true
    if(WIFEXITED(status)){
	//WEXITSTATUS(status)
	//获取子进程的退出返回值
	printf("child exit code:%d\n",WEXITSTATUS(status));
    }
    if((status & 0x7f) == 0){
	printf("child exit code:%d\n",(status >> 8) & 0xff);
    }

    printf("child exit!!\n");
    while(1){
	sleep(1);
    }
    return 0;
}
