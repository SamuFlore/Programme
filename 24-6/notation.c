#include <stdio.h>
#include <string.h>

int main()
{
    char num[10000];
    gets(num);
    int len = strlen(num);
    int dot, index;
    if (num[0] == '0')
    {
        for (int i = 1; i < len; i ++)
        {
            if (num[i] == '.')
            {
                dot = i;
            }
            else if (num[i] != '0' && num[i] != '.')
            {
                index = i;
                break;
            }
        }
        int number = index - dot;
        printf("%c", num[index]);
        if (index != len - 1)
        {
            printf(".");
            for (int i = index + 1; i < len; i ++)
            {
                printf("%c", num[i]);
            }
        }
        printf("e");
        printf("-%d", number);
    }
    else
    {
        for (int i = 1; i < len; i ++)
        {
            if (num[i] == '.')
            {
                dot = i;
                break;
            }
        }
        int number = dot - 1;
        printf("%c", num[0]);
        if (dot != 1)
        {
            printf(".");
            for (int i = 1; i < dot; i ++)
            {
                printf("%c", num[i]);
            }
            for (int i = dot + 1; i < len; i ++)
            {
                printf("%c", num[i]);
            }
        }
        else
        {
            for (int i = 1; i < len; i ++)
            {
                printf("%c", num[i]);
            }
        }
        printf("e");
        printf("%d", number);
    }
}