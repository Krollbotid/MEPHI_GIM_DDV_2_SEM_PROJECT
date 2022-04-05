#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void BubbleSort(int *num, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[j - 1] > num[j]) {
                int tmp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = tmp;
            }
        }
    }
}

void BubbleSort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    int i=0;
    for (i=0; i<number-1; i++) {
    int j;
        for (j=(number-1); j>i; j--) {
            if (comparator(first+(j-1)*size, first+j*size)>0) {
                swap(first+(j-1)*size, first+j*size, size);
            }
        }
    }
}


void GnomeSort(int *num, int size) {
    int i = 1;
    int j = 2;
    while (i < size) {
        if (num[i] > num[i - 1]) {
            i = j;
            j++;
        }
        else {
            int tmp = num[i - 1];
            num[i - 1] = num[i];
            num[i] = tmp;
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
        }
    }
}


void GnomeSort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    int i=1;
    int j=2;
    while (i<number) {
        if (comparator(first+i*size, first+(i-1)*size)>0) {
            i=j;
            j++;
        }
        else {
            swap(first+(i-1)*size, first+i*size, size);
            i--;
            if (i==0) {
                i=j;
                j++;
            }
        }
    }
}



void Merge(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    int mid=number/2;
    if (number%2==1)
        mid++;
    int a=1;
    int *newarr = (int*)malloc(number * sizeof(int));
    int st;
    while (a<number) {
        st=a;
        int k=0;
        int l=mid;
        int m=0;
        while (st<=mid) {
            while ((k<st) && (l<number) && (l<(mid+st))) {
                if (comparator(first+l*size, first+k*size)>0) {
                    newarr[m] = first+k*size;
                    k++; m++;
                }
                else {
                    newarr[m] = first+l*size;
                    l++; m++;
                }
            }
            while (k<st) {
                newarr[m] = first+k*size;
                k++; m++;
            }
            while ((j<(mid+st)) && (j<n)) {
                newarr[m] = first+l*size;
                l++; m++;
            }
            st=st+a;
        }
        a=a*2;
        for (k=0; k<number; k++)
            first+k*size = newarr[k];
        }
    }
}


int main()
{
    int size, i, *arr;
    time_t start, end;
    srand(getpid());

    printf("Input size: ");
    scanf_s("%d", &size);
    arr = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
        arr[i] = rand() % 10000;

    printf("Input array:\n");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    start = time(NULL);
    //BubbleSort(arr, size);
    GnomeSort(arr, size);
    end = time(NULL);

    printf("Sorted array:\n");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("time: %f\n", difftime(end, start));

    free(arr);
    return 0;
}



















// ���������� ���������
void BubbleSort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int i = 0;
    for (i = 0; i < number - 1; i++) {
        int j;
        for (j = (number - 1); j > i; j--) {
            if (comparator(first + (j - 1) * size, first + j * size) > 0) {
                swap(first + (j - 1) * size, first + j * size, size);
            }
        }
    }
}


// ������ ����������
void GnomeSort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int i = 1;
    int j = 2;
    while (i < number) {
        if (comparator(first + i * size, first + (i - 1) * size) > 0) {
            i = j;
            j++;
        }
        else {
            swap(first + (i - 1) * size, first + i * size, size);
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
        }
    }
}


// ���������� ��������
void Merge(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int mid = number / 2;
    if (number % 2 == 1)
        mid++;
    int a = 1;
    int* newarr = (int*)malloc(number * sizeof(int));
    int st;
    while (a < number) {
        st = a;
        int k = 0;
        int l = mid;
        int m = 0;
        while (st <= mid) {
            while ((k < st) && (l < number) && (l < (mid + st))) {
                if (comparator(first + l * size, first + k * size) > 0) {
                    newarr[m] = first + k * size;
                    k++; m++;
                }
                else {
                    newarr[m] = first + l * size;
                    l++; m++;
                }
            }
            while (k < st) {
                newarr[m] = first + k * size;
                k++; m++;
            }
            while ((l < (mid + st)) && (l < n)) {
                newarr[m] = first + l * size;
                l++; m++;
            }
            st = st + a;
        }
        a = a * 2;
        for (k = 0; k < number; k++)
            *((int*) (first + k * size)) = newarr[k];
    }
}