int binarySearch(int arr[], int low, int high, int key)//前提是已经排序好了，low是数组的第一个元素的索引，high是数组的最后一个元素的索引
{
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            return mid;//返回索引
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;// key not found
}

// 二分法求解方程
double eps = 1e-9;

double binarySolve(double low, double high)
{
    double mid = low + (high - low) / 2;
    if (high - low < eps)
    {
        return mid;
    }
    else if (f(mid) > 0)
    {
        return binarySolve(low, mid);// 左半边
    }
    else
    {
        return binarySolve(mid, high);// 右半边
    }

}