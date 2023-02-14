#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
abs(int num)
{
    if (num < 0)
    {
        return num * (- 1);
    }
    return num;
}

// Сравнение по невозрастанию модулей
// Variable for counting amount of comparisons
int comp_counter = 0;

// Compare elements in array
int
comparand(int a, int b)
{
    comp_counter ++;
    if (abs(a) < abs(b))
    {
        return 1;
    }
    return 0;
}

// Variable for counting amount of swaps
int swap_counter = 0;

// Swap of elements in array
void
swap(int *a, int *b)
{
    swap_counter ++;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Array generator
void
array_gen(int *a, int n, int param)
{
    switch (param) {
        case 1:
            // Elements are ordered (with alternating sign)

            for (int i = 1; i <= n; i ++)
            {
                a[n - i] = i * (-1  + 2 * (i % 2));
            }
            break;
        case 2:
            // Elements are sorted in reverse order (with alternating sign)

            for (int i = 1; i <= n; i ++)
            {
                a[i] = i * (-1  + 2 * (i % 2));
            }
            break;
        case 3:
            // Placement of elements is random (with alternating sign)
            for (int i = 0; i < n; i ++)
            {
                a[i] = rand() * (-1  + 2 * (i % 2));
            }
            break;
        default:
            break;
    }
}

// Straight selection sort function
void
straigtsort(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int k = i;
        int min_num = a[i];
        for (int j = i + 1; j < n; j ++)
        {
            if (comparand(min_num, a[j]) == 1)
            {
                min_num = a[j];
                k = j;
            }
        }
        swap(&a[i], &a[k]);
    }
}

// Block of functions for heapsort
// Adapted from https://lib.fbtuit.uz/assets/files/.-by.......z-lib.org.pdf

// Index of left child
int
left(int i)
{
    return 2 * i;
}

// Index of right child
int
right(int i)
{
    return 2 * i + 1;
}

// Makes correct order in heap (with i - index of root)
void
max_heapify(int * a, int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= heap_size && comparand(a[l - 1], a[i - 1]) == 1)
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if (r <= heap_size && comparand(a[r - 1], a[largest - 1]) == 1)
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(&a[i - 1], &a[largest - 1]);
        max_heapify(a, largest, heap_size);
    }
}

// Build heap from array a
void
build_max_heap(int *a, int n)
{
    for (int i = n / 2; i >= 1; i --)
    {
        max_heapify(a, i, n);
    }
}

// Heapsort function
void
heapsort(int *a, int n)
{
    int heap_size = n;
    build_max_heap(a, n);
    for (int i = n; i >= 2; i --)
    {
        swap(&a[0], &a[i - 1]);
        heap_size --;
        max_heapify(a, 1, heap_size);
    }
}

int
main(void)
{
    srand(time(NULL));
    int n = 1000;
    int * a = malloc(n * sizeof (int));
    array_gen(a, n, 2);
    // for (int i = 0; i < n; i ++)
    // {
    //     printf("%d ", a[i]);
    // }
    // printf("\n\n");
    straigtsort(a, n);
    // for (int i = 0; i < n; i ++)
    // {
    //     printf("%d ", a[i]);
    // }
    free(a);
    printf("swaps: %d\ncomparisons: %d", swap_counter, comp_counter);
    return 0;
}