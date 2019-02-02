/*演示父子进程创建子进程之后，父子进程数据独有的demo
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int val = 100;
int main()
{
    int pid = fork();
    if(pid == 0)
    {
	val = 200;
	printf("child val:%d %p\n", val, &val);
    }
    else if(pid > 0)
    {
	sleep(1);
	printf("parent val:%d %p\n", val, &val);
    }else
    {
	return -1;
    }
    return 0;
}

