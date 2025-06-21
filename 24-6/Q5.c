#include <stdio.h>

void output(int nums[], int length)
{
    for (int i = 0; i < length; i ++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap2(int nums[], int s, int e)//数组整个倒序
{
    while (s < e)
    {
        swap(&nums[s], &nums[e]);
        s ++;
        e --;
    }
}

int array(int nums[], int n)
{
    int i = n - 2;
    while (i >= 0 && nums[i] > nums[i + 1])
    {
        i --;
    }
    if (i < 0)
    {
        return 0;
    }
    int j = n - 1;
    while (nums[j] < nums[i])
    {
        j --;
    }

    swap(&nums[i], &nums[j]);
    swap2(nums, i + 1, n - 1);
    return 1;
}

int main()
{
    int n;
    scanf("%d", &n);
    int nums[10000];
    for (int i = 0; i < n; i ++)
    {
        nums[i] = i + 1;
    }
    output(nums, n);
    while (array(nums, n))
    {
        output(nums, n);
    }
    return 0;
}