#include <stdio.h>
int isPrime(int n)//flag = 1是质数
{
    int flag = 1;
    if (n == 1)
    {
        flag = 0;
    }
    if (n > 2 && n % 2 == 0)
    {
        flag = 0;
    }
    else
    {
        for (int i = 3; i*i <= n; i += 2)
        {
            if (n % i == 0)
            {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}