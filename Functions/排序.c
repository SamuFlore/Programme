#include <stdio.h>
#include <stdlib.h>
//以下均为从小到大排序

//插入排序，给arr排序，长度为n，时间复杂度O(n^2)，稳定排序
void insertSort(int arr[], int n)
{
    int i, j;
    int tmp;
    for (i = 1; i < n; i ++)//n-1趟排序
    {
        tmp = arr[i];//抽出第i个元素待插入
        for (j = i - 1; j >= 0 && tmp < arr[j]; j --)
        {
            arr[j + 1] = arr[j];//比tmp大的元素往后移，腾出待插入的位置
        }
        arr[j + 1] = tmp;//插入tmp
    }
}

//选择排序，给arr排序，长度为n，时间复杂度O(n^2)，不稳定排序
void selectSort(int arr[], int n)
{
    int i, j, d;
    int tmp;
    for (i = 0; i < n - 1; i ++)
    {
        d = i;//记录最小元素位置
        for (j = i + 1; j < n; j ++)
        {
            if (arr[j] < arr[d])
            {
                d = j;
            }
        }
        if (d != i)//最小元素不是第一个元素，将最小的挪到最前面
        {
            tmp = arr[d];
            arr[d] = arr[i];
            arr[i] = tmp;
        }
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", arr[i]);
        }
    }
}

//循环形式的冒泡排序，稳定排序，时间复杂度O(n^2)
void bubbleSort(int arr[], int n)
{
    int swapFlag;
    for (int i = 1; i < n; i ++)
    {
        swapFlag = 0;
        for (int j = 0; j < n - i; j ++)//每轮循环，检测0到n-i-1的元素是否需要交换
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

//谢尔排序，不稳定排序，时间复杂度通常小于O(n^1.5)
void shellSort(int arr[], int n)
{
    int i, j, flag, gap = n;
    int tmp;
    while (gap > 1)
    {
        gap = gap / 2;//gap减少
        do
        {
            flag = 0;
            for (i = 0; i < n - gap; i ++)
            {
                j = i + gap;//gap是步长
                if (arr[i] > arr[j])//冒泡排序的原理
                {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    flag = 1;
                }
            }
        } while (flag != 0);
    }
}

/*以下堆排序*/

//堆化
void heapify(int arr[], int i, int n)
{
    int j;
    int tmp;
    tmp = arr[i];
    j = 2 * i + 1;//左子节点
    while (j < n)
    {
        if (j + 1 < n && arr[j] < arr[j + 1])
        {
            j ++;
        }
        if (tmp < arr[j])
        {
            arr[(j - 1) / 2] = arr[j];
            j = 2 * j + 1;
        }
        else
        {
            break;
        }
        arr[(j - 1) / 2] = tmp;
    }
}
//堆排序，不稳定，时间复杂度O(nlogn)
void heapSort(int arr[], int n)
{
    int i;
    int tmp;
    for (i = n / 2 - 1; i >= 0; i --)
    {
        heapify(arr, i, n);
    }
    for(i = n - 1; i >= 1; i --)
    {
        tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        heapify(arr, 0, i);
        for (int k = 0; k < n; k ++)
        {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

/*以下二路归并排序*/

void merge(int arr[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {
        if (arr[i] <= arr[j])
        {
            tmp[q ++] = arr[i ++];
        }
        else
        {
            tmp[q ++] = arr[j ++];
        }
    }
    while (i <= leftend)
    {
        tmp[q ++] = arr[i ++];
    }
    while (j <= rightend)
    {
        tmp[q ++] = arr[j ++];
    }
    for (i = left; i <= rightend; i ++)
    {
        arr[i] = tmp[i];
    }
}

void mSort(int arr[], int tmp[], int left, int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        mSort(arr, tmp, left, center);
        mSort(arr, tmp, center + 1, right);
        merge(arr, tmp, left, center, right);
    }
}
//二路归并排序，稳定排序，时间复杂度O(nlogn)，请调用此函数
void mergeSort(int arr[], int n)
{
    int *tmp;
    tmp = (int *)malloc(n * sizeof(int));
    if (tmp != NULL)
    {
        mSort(arr, tmp, 0, n - 1);
        free(tmp);
    }
    else
    {
        printf("Memory allocation failed!\n");
    }
}

int main()
{
    int arr[] = { 2,12,16,70,5,10 };
    selectSort(arr, 6);
    for (int i = 0; i < 6; i ++)
    {
        printf("%d ", arr[i]);
    }
}