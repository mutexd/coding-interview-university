/*
 * merge sort implementatioin
 *
 * The idea of merge sort is to divide the input array into two half.
 * and sort them respectively and merge them back to one sorted array
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
_swap(int *array, size_t idx_a, size_t idx_b)
{
    int tmp = array[idx_a];
    array[idx_a] = array[idx_b];
    array[idx_b] = tmp;
}

void
merge(int* nums1, int m, int* nums2, int n)
{
    int i = 0, j = 0;
    int *data = malloc(sizeof(int) * (m + n));
/*    for (i = 0, j = 0; i < m && j < n;) {
        if (nums1[i] <= nums2[j]) {
            i++;
        } else {
            int hold = nums2[j];
            memmove(nums1 + i + 1, nums1 + i, m - i);
            nums1[i] = hold;
            i++;
            m++;
            j++;
        }
    }*/
    for (i = 0, j = 0; i < m && j < n;) {
        if (nums1[i] <= nums2[j]) {
            data[i+j] = nums1[i];
            i++;
        } else {
            data[i+j] = nums2[j];
            j++;
        }
    }
    // if there any m left
    for (; i < m; i++) {
        data[i+j] = nums1[i];
    }
    for (; j < n; j++) {
        data[i+j] = nums2[j];
    }

    memcpy(nums1, data, sizeof(int)*(m+n));
    free(data);
}

void
merge_sort(int *array, int size)
{
    // divide array
    if (size <= 1) {
        return;
    }
    int k = size / 2;
    merge_sort(array, k);
    merge_sort(array + k, size - k);
    merge(array, k, array + k, size - k);
    return;
}

int
main(int argc, char** argv)
{
    //int question[] = { 19, 2, 3, 4, 2, 22, 43, 7 };
    int question[] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7};

    // input array
    merge_sort(question, sizeof(question)/sizeof(int));    

    //printf("length of array = %d\n", sizeof(question) / sizeof(int) );
    // output result
    for (int i = 0; i < sizeof(question) / sizeof(int); i++) {
        printf("%d, ", question[i]);
    }
    printf("\n");
}
