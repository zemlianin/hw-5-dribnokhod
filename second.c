#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Please, enter a command-line parametr");
        return 0;
    }
    int fd1;

    char *myfifo = argv[1];
    mkfifo(myfifo, 0123);

    char str1[80], str2[80];
    while (1)
    {
        printf("Enter your message to first process:\n");
        fd1 = open(myfifo, O_RDONLY);
        read(fd1, str1, 80);

        printf("Message from first program: %s\n", str1);
        close(fd1);

        fd1 = open(myfifo, O_WRONLY);
        fgets(str2, 80, stdin);
        write(fd1, str2, strlen(str2) + 1);
        close(fd1);
    }
    return 0;
}