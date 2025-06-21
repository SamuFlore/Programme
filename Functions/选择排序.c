void selectSort(int arr[], int n)
{
    for (int i = 1; i < n; i ++)
    {
        int index = 0;
        for (int j = 1; j <= n - i; j ++)
        {
            if (arr[j] > arr[index])
            {
                index = j;
            }
        }
        if (index != n - i)
        {
            int temp = arr[index];
            arr[index] = arr[n - i];
            arr[n - i] = temp;
        }
        
    }
}