#include<stdbool.h>

bool bit_k_in_x(int x,int k)//判断 x 的第 k 位是否为 1 
{
    return (x>>k)&1; 
} 

int set_bit_k_in_x(int x,int k,int b)//将 x 的第 k 位设为 b 
{
    if ( b==1 ) 
    {
        x|=(1<<k);
    }    
         
    else
    {
        x&=~(1<<k); 
    }
        
    return x; 
} 

int lowbit(int x)//求 x 的最低位，例如 12=(1100)_2 ，返回 4=(100)_2 
{
    return x&-x; 
} 

int popcount(unsigned int x)
{//求 x 二进制表示中 1 的数量 
    int cnt; 
    for ( cnt=0 ; x ; x&=x-1,cnt++ ); 
    return cnt; 
} 

__builtin_popcount(x);//某些编译器自带的库函数，求 x 二进制表示中 1 的数量

void print_bin(int x)
{ 
    for ( int i=31 ; i>=0 ; i-- )//如果是long long，要改成63 
    {
        printf("%d",bit_k_in_x(x,i)); 
    }
}