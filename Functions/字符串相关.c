#include <stdio.h>
#include <string.h>

void reverseString(char *str, int length) 
{
    int start = 0; // 开始位置
    int end = length - 1; // 结束位置

    // 交换字符直到中间
    while (start < end) 
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}