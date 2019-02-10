/* 缓冲区位置的演示
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    fwrite("fwrite", 1, 6, stdout);
    fprintf(stdout, "%s", "fprintf");
    printf("printf");
    write(STDOUT_FILENO, "write", 5);

    sleep(3);
    return 0;
}
