#include <stdio.h>

int gcd(int a, int b)//辗转相除法求最大公因数
{
    int r;
    if (b == 0)
    {
        return a < 0 ? -a : a;
    }
    else
    {
        while ((r = a % b) != 0)
        {
            a = b;
            b = r;
        }
        return b < 0 ? -b : b;
    }
    
}

int lcm(int a, int b)//最小公倍数
{
    return a * b / gcd(a, b);
}
