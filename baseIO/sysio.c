/*演示基础io系统调用接口demo
 *  open close read write lseek
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
    //将当前进程文件创建权限掩码设置为0（仅对当前进程有效）
    //mode_t umask(mode_t mask);
    umask(0);
    //int open(const char* pathname, int flags, mode_t mode);
    //pathname:文件名称
    //flags:选项标志
    //    必选项：
    //	    O_RDONLY  只读
    //	    O_ERONLY  只写
    //	    O_RDWR    读写
    //	  可选项：
    //	    O_CREAT   若文件不存在则创建，存在则打开
    //	    O_EXCL    搭配O_CREAT使用，若文件存在则报错返回
    //	    O_TRUNC   打开文件同时清空文件内容
    //	    O_APPEND  向文件中追加内容
    //mode:权限（通常使用八进制数据表示）
    //返回值：文件描述符（非负整数） 失败：-1
    int fd = open("./test.txt", O_CREAT|O_RDWR|O_TRUNC|O_APPEND, 0664);
    if(fd < 0){
	perror("open error");
	return -1;
    }
    //ssize_t write(int fd, const void* buf, size_t count);
    //fd:文件描述符
    //buf：要写入的数据
    //count:要写入的数据长度
    //返回值:实际写入长度  失败：-1
    char* ptr = "hallo bit~~!";
    ssize_t ret = write(fd, ptr, strlen(ptr));
    if(ret < 0){
	perror("write");
	return -1;
    }

    //off_t lseek(int fd, off_t offset, int whence);
    //跳转文件读写位置到whence位置偏移offset个字节
    //whence：SEEK_SET  SEEK_CUR  SEEK_END
    lseek(fd, 0, SEEK_SET);
    char buf[1024] = { 0 };
    //ssize_t read(int fd, void* buf, size_t count);
    //返回值：实际的读取字节长度  失败;-1
    ret = read(fd, buf, 1023);
    if(ret < 0){
	perror("read error");
	return -1;
    }else if(ret == 0){
	printf("end of file!\n");
    }
    printf("buf:[%s]\n",buf);
    //关闭文件
    close(fd);
    return 0;
}
