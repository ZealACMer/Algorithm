//基础排序：冒泡排序、选择排序、插入排序、希尔排序
#include <iostream>

//冒泡排序算法O(n^2) 空间复杂度O(1) 稳定
void bubbleSort(int arr[], int size)
{
    //将n-1个较大元素沉底
    for(int i = 0; i < size - 1; ++i)
    {
        bool flag = false;
        //一次排序处理
        for(int j = 0; j < size - 1 - i; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
            }
        }
        //一次排序中没有数据交换，说明数组已经有序，直接返回
        if(!flag)
        {
            return;
        }
    }
}

//选择排序算法O(n^2) 空间复杂度O(1) 不稳定
void choiceSort(int arr[], int size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        int min = arr[i];
        int k = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        if(k != i)
        {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

//插入排序算法O(n^2)，空间复杂度O(1) 稳定，在数组元素有序的情况下，性能最好
void insertSort(int arr[], int size)
{
    for(int i = 1; i < size; ++i)
    {
        int val = arr[i];
        int j = i - 1;
        for(; j >= 0; --j)
        {
            if(arr[j] <= val)
            {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
    }
}

//希尔排序
void shellSort(int arr[], int size)
{
    for(int gap = size / 2; gap > 0; gap /= 2) //100w -> 19 1000w->24
    {
        for(int i = gap; i < size; ++i) //起点
        {
            int val = arr[i];
            int j = i - gap;
            for(; j >= 0; j -= gap)
            {
                if(arr[j] <= val)
                {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}

void show(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    // srand(time(0));
    // int arr[10]{};
    // for(int i = 0; i < 10; ++i)
    // {
    //     arr[i] = rand() % 100;
    // }
    //bubbleSort(arr, 10);
    //choiceSort(arr, 10);
    //insertSort(arr, 10);
    //shellSort(arr, 10);
    //show(arr, 10);

    const int COUNT = 10000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    int* drr = new int[COUNT];

    srand(time(0));
    for(int i = 0; i < COUNT; ++i)
    {
        int val = rand() % COUNT;
        arr[i] = brr[i] = crr[i] = drr[i] = val;
    }

    clock_t begin, end;
    
    begin = clock();
    bubbleSort(arr, COUNT);
    end = clock();
    //static_cast是类型安全的，它不会执行不安全的转换，比如从float到int（这可能会丢失信息）
    std::cout << "bubbleSort spend:" << static_cast<double>(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    
    begin = clock();
    choiceSort(arr, COUNT);
    end = clock();
    //static_cast是类型安全的，它不会执行不安全的转换，比如从float到int（这可能会丢失信息）
    std::cout << "choiceSort spend:" << static_cast<double>(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    
    begin = clock();
    insertSort(arr, COUNT);
    end = clock();
    //static_cast是类型安全的，它不会执行不安全的转换，比如从float到int（这可能会丢失信息）
    std::cout << "insertSort spend:" << static_cast<double>(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    
    begin = clock();
    shellSort(arr, COUNT);
    end = clock();
    //static_cast是类型安全的，它不会执行不安全的转换，比如从float到int（这可能会丢失信息）
    std::cout << "shellSort spend:" << static_cast<double>(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    
    /*
        bubbleSort spend:0.30822s
        choiceSort spend:0.12342s
        insertSort spend:4.4e-05s
        shellSort spend:0.000574s
    */

    return 0;
}
