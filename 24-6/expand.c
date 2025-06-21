#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str[10000];
    gets(str);
    int len = strlen(str);
    for (int i = 0; i < len; i ++)
    {
        if (str[i] != '-')
        {
            putchar(str[i]);
        }
        else
        {
            if (i == 0 || i == len - 1)
            {
                putchar('-');
            }
            else if (islower(str[i - 1]) && islower(str[i + 1]))
            {
                int index = str[i - 1] + 1;
                for (; index < str[i + 1]; index ++)
                {
                    putchar(index);
                }
            }
            else if (isupper(str[i - 1]) && isupper(str[i + 1]))
            {
                int index = str[i - 1] + 1;
                for (; index < str[i + 1]; index ++)
                {
                    putchar(index);
                }
            }
            else if (isdigit(str[i - 1]) && isdigit(str[i + 1]))
            {
                int index = str[i - 1] + 1;
                for (; index < str[i + 1]; index ++)
                {
                    putchar(index);
                }
            }
            else
            {
                putchar('-');
            }
        }
    }
    return 0;
}