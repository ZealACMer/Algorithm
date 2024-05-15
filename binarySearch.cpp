#include <iostream>
using namespace std;

//二分搜索递归代码
int binarySearch(int arr[], int i, int j, int val)
{
    if(i > j) return -1;
    int mid = i + (j - i) / 2;

    if(arr[mid] == val)
    {
        return mid;
    }
    else if(arr[mid] > val)
    {
        return binarySearch(arr, i, mid - 1, val);
    }
    else
    {
        return binarySearch(arr, mid + 1, j, val);
    }
}

int BinarySearchRecursive(int arr[], int size, int val)
{
    return binarySearch(arr, 0, size - 1, val);
}

int BinarySearchNonRecursive(int arr[], int size, int val)
{
    int l = 0, r = size - 1;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        if(arr[mid] == val)
        {
            return mid;
        }
        else if(arr[mid] > val)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {11, 24, 57, 9, 7, 33, 233, 533, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    sort(arr, arr + size);
    cout << BinarySearchRecursive(arr, size, 57) << endl;
    cout << BinarySearchNonRecursive(arr, size, 57) << endl;

    cout << BinarySearchRecursive(arr, size, 58) << endl;
    cout << BinarySearchNonRecursive(arr, size, 58) << endl;

    return 0;
}

