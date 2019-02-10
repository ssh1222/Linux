/*回顾c库中的io接口
 *  fopen fclose fwrite fread fseek
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    //mode: r r+ w w+ a a+
    //r:只读 r+：读写
    //w：只写 w+：读写  若文件不存在则创建，若问阿金存在则清空内容
    //a：写追加 a+：读写打开，追加写，从起始位置读，文件不存在则创建
    FILE* fp = fopen("./test.txt", "w+");
    if(fp == NULL){
	printf("fopen error]n");
	return-1;
    }

    char* ptr = "hello bit!!\n";
    //size_t fwrite(void* ptr, size_t size, size_t nmemb, FILE* stream);
    fseek(fp, 5, SEEK_END);
    if(fwrite(ptr, 1, strlen(ptr), fp) != strlen(ptr)){
	printf("fwirte error\n");
    }

    //int fseek(FILE* stream, long offset, int whence);
    //whence:
    //SEEK_SET  文件起始位置
    //SEEK_CUR  文件读写位置
    //SEEK_END  文件末尾位置
    fseek(fp, 0, SEEK_SET);
    //size_t fread(void* ptr, size_t size, size_t nmmeb, FILE* stream);
    char buf[1024] = { 0 };
    int ret = fread(buf, 1, 1024-1, fp);
    if(ret < 0){
	printf("read error");
    }
    printf("ret:%d buf:%s\n", ret, buf);
    fclose(fp);
    return 0;
}
