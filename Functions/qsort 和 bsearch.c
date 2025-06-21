#include<stdlib.h>

int cmp(const void *p1,const void *p2)//升序排序，降序把1和-1互换
{
    int *a = (int *)p1;
    int *b = (int *)p2;
    if (*a < *b)
    {
        return -1;//返回负数不交换
    }
    else if (*a > *b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int A[10086], n; 
int main()
{ 
    int key = 10086;
    qsort(A, n, sizeof(int), cmp);//第一个参数是数组的起始地址，第二个参数是数组的元素个数，第三个参数是每个元素的大小，第四个参数是比较函数的指针
    bsearch(A, n, sizeof(int), &key, cmp);//第一个参数是数组的起始地址，第二个参数是数组的元素个数，第三个参数是每个元素的大小，第四个参数是要查找的元素的地址，第五个参数是比较函数的指针，假如数组是升序排序，cmp就是升序，反之亦然。
}