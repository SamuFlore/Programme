#include <stdio.h>

void bubbleSort(int arr[], int n)//循环形式的冒泡排序，从小到大，每从头至尾循环一次大数会移动到末尾。
{
    int swapFlag;
    for (int i = 1; i < n; i ++)
    {
        swapFlag = 0;
        for (int j = 0; j < n - i; j ++)
        {
            if (arr[j] > arr[j + 1])
            {
                swapFlag = 1;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (swapFlag == 0)
        {
            break;
        }
    }
}
void bubbleSort2(int arr[], int n)//循环形式的冒泡排序，从小到大，每从头至尾循环一次小数会移动到开头。
{
    int swapFlag;
    int cnt = 0;
    for (int i = n - 1; i >= 1; i --)
    {
        swapFlag = 0;
        for (int j = n - 1; j >= n - i; j --)
        {
            if (arr[j] < arr[j - 1])
            {
                swapFlag = 1;
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
            
        }
        if (swapFlag == 0)
        {
            break;
        }
    }
}

void recurBubbleSort(int arr[], int n)
{
    int swapFlag = 0;
    if (n == 1)
    {
        return ;
    }
    else
    {
        
        for (int i = 0; i < n - 1; i ++)
        {
            if (arr[i] > arr[i + 1])
            {
                swapFlag = 1;
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        if (swapFlag == 0)
        {
            return ;
        }
        recurBubbleSort(arr, n - 1);
    }
}

//通用冒泡排序
void bubbleSort2(void *arr, int len, int elemSize, int (*cmp)(const void *a, const void *b))
{
    for (int i = 1; i < len; i ++)
    {
        for (int j = 0; j < len - i; j ++)
        {
            if (cmp(arr + j * elemSize, arr + (j + 1) * elemSize))//检查是否有序，有序返回0，无序返回非0
            {
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);//交换两个元素
            }
        }
    }
}

void swap(void *e1, void *e2, int elemSize)//一个字节一个字节地交换两个元素
{
    int i;
    char tmp;
    for (i = 0; i < elemSize; i ++)
    {
        tmp = *((char *)(e1) + i);
        *((char *)(e1) + i) = *((char *)(e2) + i);
        *((char *)(e2) + i) = tmp;
    }
}

int less(const void *a, const void *b)//比较函数，整数比较（欲修改只要修改less函数即可）
{
    int *p1 = (int *)a;//a指向地址，所以不能直接赋值给变量
    int *p2 = (int *)b;
    return *p1 < *p2;
}

int greater(const void *a, const void *b)
{
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    return *p1 > *p2;
}