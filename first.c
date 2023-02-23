#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please, enter a command-line parametrs");
        return 0;
    }

    int fd;

    char *myfifo = argv[1];

    mkfifo(myfifo, 0123);

    char arr1[80], arr2[80];
    while (1)
    {
        printf("Enter your message to second process:\n");
        fd = open(myfifo, O_WRONLY);

        fgets(arr2, 80, stdin);

        write(fd, arr2, strlen(arr2) + 1);
        close(fd);

        fd = open(myfifo, O_RDONLY);

        read(fd, arr1, sizeof(arr1));

        printf("Message from second program: %s\n", arr1);
        close(fd);
    }
    return 0;
}