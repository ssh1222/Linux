/*环境变量的全局特性演示
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envri[])
{
    //char* getenv(const char*name)
    //通过环境变量名称获取变量的值
    char* ptr = getenv("MYVAL");
    printf("MYVAL:%s\n", ptr);

    int i;
    for(i = 0; envri[i] != NULL; ++i)
    {
	printf("env[%d]:[%s]\n", envri[i]);
    }

    extern char** environ;
    for(i = 0; environ[i] != NULL; ++i)
    {
	printf("environ[%d]:[%s]\n", environ[i]);
    }
    return 0;
}
