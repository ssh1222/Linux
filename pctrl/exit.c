/*这是验证进程终止方式的demo
 * return exit _exit
 */

#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>

int a = 1;
int main()
{
    printf("hello bit ~~");
    sleep(3);
    _exit(0);
    //void _exit(int status);
    //_exit(233);
    //void exit(int status);
    //正常终止进程，并且返回val
    //exit(253);
    int i;
    for(i = 0; i < 256; ++i){
	//char* strerror(int errnum);
	//根据错误编号获取错区信息
	printf("error:%d--%s\n", i, strerror(i));
    }
    if(a == 1){
	return 256;
    }else{
	return -1;
    }

    while(1){
	printf("----\n");
	sleep(1);
    }
    return 0;
}
