#ifndef SORT_H
#define SORT_H

#include <utility> 

template <class T>
class Sort
{
public:

    
    static long insertionSort(T* arr[], int n)
    {
        long comp = 0;

        for (int i = 1; i < n; i++)
        {
            T* key = arr[i];
            int j = i - 1;

            while (j >= 0)
            {
                comp++;
                if (*arr[j] > *key)
                {
                    arr[j + 1] = arr[j];
                    j--;
                }
                else
                    break;
            }

            arr[j + 1] = key;
        }

        return comp;
    }

    
    static long shellSort(T* arr[], int n)
    {
        long comp = 0;

        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i++)
            {
                T* temp = arr[i];
                int j = i;

                while (j >= gap)
                {
                    comp++;
                    if (*arr[j - gap] > *temp)
                    {
                        arr[j] = arr[j - gap];
                        j -= gap;
                    }
                    else
                        break;
                }

                arr[j] = temp;
            }
        }

        return comp;
    }

    
    static long quickSort(T* arr[], int left, int right)
    {
        long comp = 0;

        while (left < right)
        {
            int i = left;
            int j = right;
            T* pivot = arr[(left + right) / 2];

            while (i <= j)
            {
                while (*arr[i] < *pivot)
                {
                    comp++;
                    i++;
                }

                while (*arr[j] > *pivot)
                {
                    comp++;
                    j--;
                }

                if (i <= j)
                {
                    std::swap(arr[i], arr[j]);
                    i++;
                    j--;
                }
            }

            
            if (j - left < right - i)
            {
                if (left < j)
                    comp += quickSort(arr, left, j);
                left = i;
            }
            else
            {
                if (i < right)
                    comp += quickSort(arr, i, right);
                right = j;
            }
        }

        return comp;
    }

   
    static bool isSorted(T* arr[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            if (*arr[i - 1] > *arr[i])
                return false;
        }
        return true;
    }
};

#endif