#include <stdio.h>

long long combination(int n, int m)//组合数
{
    long long res = 1;
    for (int i = 1; i <= m; i ++)
    {
        res = res * (n - i + 1)/i;
    }
    return res;
}