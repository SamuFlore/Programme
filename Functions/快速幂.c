#include <stdio.h>

long long qpow(long long a, long long n, int mod)//求 (a^n)%mod , 快速幂算法
{
    if (n == 0) 
    {
        return 1; 
    }
    
    long long r = qpow(a, n/2, mod); 
    r = r * r % mod; 
    if (n & 1)  
    {
        r = r * a % mod;
    }
         
    return r; 
}