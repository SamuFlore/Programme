#include <stdio.h>
#include <string.h>



int main()
{
    char str[10000], str2[10000];
    int nums[10000];
    char ops[10000];
    gets(str);
    int len = strlen(str);
    int k = 0;
    for (int i = 0; i < len; i ++)
    {
        if (str[i] != ' ')
        {
            str2[k] = str[i];
            k ++;
        }
    }
    str2[k] = '\0';//k == 15
    
    int num = 0, j = 0;
    for (int i = 0; i < k; i ++)
    {
        if (str2[i] >= '0' && str2[i] <= '9')
        {
            num = num * 10 + str2[i] - '0';
        }
        else
        {
            nums[j] = num;
            ops[j] = str2[i];
            j ++;
            num = 0;
        }
    }
    //j == 7
    int x = 0;//x是操作符的位置, z是数的位置
    for (; x < j; x ++)
    {
        if (ops[x] == '*')
        {
            nums[x] *= nums[x + 1];
            for (int y = x; y < j; y ++)
            {
                nums[y + 1] = nums[y + 2];
            }
            for (int y = x; y < j; y ++)
            {
                ops[y] = ops[y + 1];
            }
            x --;
            j --;
        }
        else if (ops[x] == '/')
        {
            nums[x] /= nums[x + 1];
            for (int y = x; y < j; y ++)
            {
                nums[y + 1] = nums[y + 2];
            }
            for (int y = x; y < j; y ++)
            {
                ops[y] = ops[y + 1];
            }
            x --;
            j --;
        }
        
    }
    int res = nums[0];
    for (int i = 0; i < j; i ++)
    {
        if (ops[i] == '+')
        {
            res += nums[i + 1];
        }
        else if (ops[i] == '-')
        {
            res -= nums[i + 1];
        }
        else if (ops[i] == '=')
        {
            break;
        }

    }
    printf("%d\n", res);
    // printf("\n");
    // for (int i = 0; i < j; i ++)
    // {
    //     printf("%c ", ops[i]);
    // }
    // printf("\n");
    return 0;

}