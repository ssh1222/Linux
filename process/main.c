/*写一个死循环程序，查看进程信息
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    //pit_t getpid(void);
    //获取调用进程的pid
    //pid_t fork(void);
    //通过复制调用进程，创建一个新的子进程
    pid_t pid = fork();
    //因为父子进程返回值不同，因此虽然代码相同，但是父进程因为返回会进入
    //不同的判断执行体
    if(pid == 0){
	printf("i am child!! pid:%d\n", getpid());
    }else if(pid > 0){
	printf("i am parent!! pid:%d\n", getpid());
	pid_t pid = fork();
    }else{
	//打印上一个系统调用的错误原因
	perror("fork error");
	return -1;
    }
    printf("pid:%d\n",getpid());
    while(1){
	sleep(1);
	printf("------\n");
    }
    return 0;
}
