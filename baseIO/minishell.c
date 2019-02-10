/*编写建议的minishell，实现能够运行shell的 外部命令
 * 1.读取缓冲区
 * 2.解析输入
 * 3.创建子进程
 * 4.程序替换
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    char buf[1024] ={ 0 };
    while(1){
	printf("[sun@sun~]:");
	fflush(stdout);//刷新标准输出缓冲区--将缓冲区的数据直接打印
	memset(buf, 0x00, 1024);
	//%[^\n]  scanf取数据的时候遇到各种空白字符就会停止读取
	//        为了读取所有的输入，让scanf遇到换行的时候再终止
	//%*c     scanf取数据之后，缓冲区中遗留换行符，取不出来，导致
	//        scanf非阻塞，陷入死循环，所以取出一个字符并丢弃
	//scanf返回值读取数据的个数，如果读取失败，避免缓冲区的换行取不出来
	//导致死循环（防备直接回车情况）
	if(scanf("%[^\n]%*c", buf) != 1){
	    getchar();
	    continue;
	}
	//ls -l >> a.txt
	char* str = buf;
	int redirect_flag = 0;//0-清空 1-追加
	char* redirect_file = NULL;
	    int fd = -1;
	while(*str != '\0'){
	    //如果当前字符是重定向符号，则进入判断，将整个命令从这里截断
	    //前边是命令，后边是重定向信息
	    if(*str == '>'){
		*str = '\0';
		//判断重定向方式
		redirect_flag++;
		if(*(str+1) == '>'){
		    redirect_flag++;
		}
		str += redirect_flag;
		//走完文件名前边的空白字符
		while(isspace(*str) && *str != '\0'){
		    *str++ = '\0';
		}
		//文件名的起始位置
		redirect_file = str;
		//走完文件名
		while(!isspace(*str) && *str != '\0'){
		    str++;
		}
		//文件名最后需要结束符
		*str = '\0';
		continue;
	    }
	    str++;
	}
	//ls    -l  -a
	char *ptr = buf;
	int argc = 0;
	char *argv[32];
	while(*ptr != '\0')
	{
	    if(!isspace(*ptr))
	    {
		argv[argc++] = ptr;
		//将ls读完，指向空白字符处
		while(*ptr != '\0' && !isspace(*ptr))
		{
		    ++ptr;
		}
	    }
	    //将空白字符全部替换为字符串结尾标志
	    *ptr = '\0';
	    ++ptr;
	}
	//参数结尾必须为空
	argv[argc] = NULL;
	//创建子进程
	int pid = fork();
	if(pid < 0){
	    perror("fork error");
	    return -1;
	}else if(pid == 0){
	    //子进程程序替换，运行指定命令
	    if(redirect_flag == 1){
		//清空重定向
		fd = open(redirect_file, O_CREAT|O_WRONLY|O_TRUNC, 0664);
		//这个重定向不能再父进程中完成，因为一旦父进程重定向了，
		//shell程序后续的界面就打印不出来了，都会写入到这个文件中
		dup2(fd, 1);
	    }else if(redirect_flag == 2){
		//追加重定向
		fd = open(redirect_file, O_CREAT|O_WRONLY|O_APPEND, 0664);
		dup2(fd, 1);
	    }
	    execvp(argv[0],argv);
	    exit(0);
	}
	//避免僵尸子进程
	waitpid(pid, NULL, 0);
    }
    return 0;
}
