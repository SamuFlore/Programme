#include <stdio.h>
#include <stdlib.h>

//选择排序，给arr排序，长度为n，时间复杂度O(n^2)，不稳定排序
int selectSort(int arr[], int n)
{
    int i, j, d;
    int tmp;
    int cnt = 0;
    for (i = 0; i < n - 1; i ++)
    {
        d = i;//记录最小元素位置
        for (j = i + 1; j < n; j ++)
        {
            cnt ++;
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
    }
    return cnt;
}

//循环形式的冒泡排序，稳定排序，时间复杂度O(n^2)
int bubbleSort(int arr[], int n)
{
    int swapFlag;
    int cnt = 0;
    for (int i = 1; i < n; i ++)
    {
        swapFlag = 0;
        for (int j = 0; j < n - i; j ++)//每轮循环，检测0到n-i-1的元素是否需要交换
        {
            cnt ++;
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
    return cnt;
}

//堆化
int heapify(int arr[], int i, int n)
{
    int j;
    int tmp;
    int cnt = 0;
    tmp = arr[i];
    j = 2 * i + 1;//左子节点
    while (j < n)
    {
        cnt ++;
        if (j + 1 < n && arr[j] < arr[j + 1])
        {
            j ++;
        }
        if (tmp >= arr[j])
        {
            
            break;
        }
        arr[(j - 1) / 2] = arr[j];
        j = 2 * j + 1;
    }
    arr[(j - 1) / 2] = tmp;
    return cnt;
}
//堆排序，不稳定，时间复杂度O(nlogn)
int heapSort(int arr[], int n)
{
    int i;
    int tmp;
    int cnt = 0;
    for (i = n / 2 - 1; i >= 0; i --)
    {
        cnt += heapify(arr, i, n);
    }
    for(i = n - 1; i >= 1; i --)
    {
        tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        cnt += heapify(arr, 0, i);
        // for (int k = 0; k < n; k ++)
        // {
        //     printf("%d ", arr[k]);
        // }
        // printf("\n");
    }
    return cnt;
}

/*以下二路归并排序*/

int merge(int arr[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    int cnt = 0;
    while (i <= leftend && j <= rightend)
    {
        cnt ++;
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
    return cnt;
}

int mSort(int arr[], int tmp[], int left, int right)
{
    int center;
    int cnt = 0;
    if (left < right)
    {
        center = (left + right) / 2;
        cnt += mSort(arr, tmp, left, center);
        cnt += mSort(arr, tmp, center + 1, right);
        cnt += merge(arr, tmp, left, center, right);
    }
    return cnt;
}
//二路归并排序，稳定排序，时间复杂度O(nlogn)，请调用此函数
int mergeSort(int arr[], int n)
{
    int *tmp;
    int cnt = 0;
    tmp = (int *)malloc(n * sizeof(int));
    if (tmp != NULL)
    {
        cnt = mSort(arr, tmp, 0, n - 1);
        free(tmp);
    }
    else
    {
        printf("Memory allocation failed!\n");
    }
    return cnt;
}

//快速排序，不稳定排序，时间复杂度O(nlogn)

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int quickSort(int k[ ],int left,int right)
{     
    int i, last;
    int cnt = 0;
    if(left<right)
    {
        last=left; 
        for(i=left+1;i<=right;i++)
        {
            cnt ++;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]); 
        }
            
        swap(&k[left],&k[last]);
        cnt += quickSort(k,left,last-1); 
        cnt += quickSort(k,last+1,right);   
    }
    return cnt;
}

int main()
{
    int list[105];
    int n, mode;
    scanf("%d %d", &n, &mode);
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &list[i]);
    }
    if (mode == 1)
    {
        int cnt = selectSort(list, n);
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        printf("%d\n", cnt);
    }
    else if (mode == 2)
    {
        int cnt = bubbleSort(list, n);
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        printf("%d\n", cnt);
    }
    else if (mode == 3)
    {
        int cnt = heapSort(list, n);
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        printf("%d\n", cnt);
    }
    else if (mode == 4)
    {
        int cnt = mergeSort(list, n);
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        printf("%d\n", cnt);
    }
    else if (mode == 5)
    {
        int cnt = quickSort(list, 0, n - 1);
        for (int i = 0; i < n; i ++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        printf("%d\n", cnt);
    }
    return 0;
}