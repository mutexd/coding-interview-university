#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if 0
bool exist(int value, int * vals, int valsSize) {
    for (int i = 0; i < valsSize ; i++) {
        if (value == vals[i]) {
            return true;
        }
    }
    return false;
}

int val_start = 0;

bool findPartitionEqual(int* nums, int numsSize, int* vals, int valsSize, int max) {
    if (numsSize == 1) {
        if (exist(nums[0], vals, valsSize)) return true;
        else return false;
    }
    // iterate over vals and add into set
    int size = valsSize;
    for (int i = val_start; i < size; i++) {
        if (vals[i] == -1) continue;
        int minus = abs(nums[numsSize-1] - vals[i]);
        int plus = nums[numsSize-1] + vals[i];
        //printf("plus = %d, minus = %d\n", plus, minus);
        vals[i] = -1;
        val_start = i + 1;
        if (plus == minus) {
            if (plus < max) {
                if (!exist(plus, vals, valsSize)) vals[valsSize++] = plus;
            }
        } else {
            if (plus < max) {
                if (!exist(plus, vals, valsSize)) vals[valsSize++] = plus;
            }
            if (!exist(minus, vals, valsSize)) vals[valsSize++] = minus;
        }       
    }
    /*for (int i = 0; i < valsSize; i++) {
        printf("%d,", vals[i]);
    }
    printf("\n");*/
    return findPartitionEqual(nums, numsSize - 1, vals, valsSize, max);
}

bool canPartition(int* nums, int numsSize) {
    int value[500000] = {0};
    int valSize = 1;
    value[0] = 0;
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    if ((sum & 0x1) == 1) {
        return false;
    }
    return findPartitionEqual(nums, numsSize, value, valSize, sum/2);
}
#endif

/*
 * The solution above cannot pass the Time Limit, but the idea is close
 * Here is the idea:
 * (1) for two subset from array to be equal, the equal value should be sum/2, so sum must be even
 * (2) Let us re-phrase the problem: among n0, n1 ... nN-1, find subset that summation to sum/2
 *     denoted as d[N][sum/2]. As we did above, we try to remove last item from array
 *     The problem becomes --> d[N-1][sum/2 - nums[N-1]] or d[N-1][sum/2] (another subset)
 * 
 * So we need to think it in Dynamic Programming
 * d[i][j] = d[i-1][j-nums[i]] || d[i-1][j]
 *
 */
bool canPartition(int *nums, int numsSize) {
    int sum = 0;
    bool **dp;
    for (int i = 0; i < numsSize; i++) sum+=nums[i];

    // sum must be even
    if ((sum & 0x1) == 0x1) {
        return false;
    }

    sum = sum >> 1;

    // initialize dp table
    dp = malloc(sizeof(bool*)*numsSize);
    for (int i = 0; i < numsSize; i++) {
        dp[i] = malloc(sizeof(bool)*(sum+1));
        //memset(dp[i], 0, sizeof(bool)*sum);
    }
    
    for (int i = 0; i < numsSize; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i < numsSize; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j - nums[i] >= 0) { 
                dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    bool ans = dp[numsSize-1][sum];
    for (int i = 0; i < numsSize; i++) {
        free(dp[i]);
    }
    free(dp);
    return ans;
}

int main(int argc, char ** argv) 
{
    //int q[] = { 1, 5, 11, 5 };
    //int q[] = { 3, 3, 3, 4, 5};
    int q[]= { 100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100 };
    //int q[] = { 28,63,95,30,39,16,36,44,37,100,61,73,32,71,100,2,37,60,23,71,53,70,69,82,97,43,16,33,29,5,97,32,29,78,93,59,37,88,89,79,75,9,74,32,81,12,34,13,16,15,16,40,90,70,17,78,54,81,18,92,75,74,59,18,66,62,55,19,2,67,30,25,64,84,25,76,98,59,74,87,5,93,97,68,20,58,55,73,74,97,49,71,42,26,8,87,99,1,16,79 };
    printf("ans = %d\n", canPartition(q, sizeof(q)/sizeof(int)));
    return 0;   
}
