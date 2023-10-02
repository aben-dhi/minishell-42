#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    size_t  size;

    size = pathconf(".", _PC_PATH_MAX);
    printf("%ld\n", size);
    return (0);
}