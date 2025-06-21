#include <stdio.h>
#include <pthread.h>

int main()
{
    char a = 'A';
    char b = a | 0x20;
    printf("%c\n", b);
}