#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char str[] = "Hello World!\n";
    ssize_t len;

    fd = open("test.txt", O_WRONLY | O_CREAT);
    printf("文件描述符fd = %d\n", fd);

    len = write(fd, str, sizeof(str));
    printf("写入内容长度len = %zd\n", len);

    return 0;
}
