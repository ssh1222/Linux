/*文件描述符分配规则demo
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    //stdout----1
    //close(1);
    int fd = open("./test.txt", O_RDWR);
    if(fd < 0){
	perror("open error");
	return -1;
    }
    //int dup2(int oldfd, int newfd);
    //让newfd也指向oldfd所指向的文件（文件输出重定向）
    dup2(fd, 1);
    printf("fd:%d\n", fd);
    fflush(stdout);
    close(fd);
    return 0;
}
