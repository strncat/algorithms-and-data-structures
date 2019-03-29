#include <stdio.h>
#include <string.h>

// Dynamic Programming
// Find the maximum sum subarray in a 2D array
// Source: geeksforgeeks but changed slightly

#define ROW 4
#define COL 5

int kadane(int* a, int n, int* begin, int* end) {

    int sum = 0, max_sum = a[0], i, restart = 0;
    
    for (i = 0; i < n; i++) {
        
        sum += a[i];
        
        if (sum < 0) {
            sum = 0;
            restart = i + 1;
        } else if (sum > max_sum) {
            max_sum = sum;
            *begin = restart;
            *end = i;
        }
    }
    
    if (max_sum > 0) {
        return max_sum;
    }
    
    // negative array case
    max_sum = a[0];
    *begin = *end = 0;
    
    for (i = 1; i < n; i++) {
        if (a[i] > max_sum) {
            max_sum = a[i];
            *begin = *end = i;
        }
    }
    return max_sum;
}

void maximum_sum_2d(int a[ROW][COL]) {

    int max_sum = a[0][0], top_x = 0, top_y = 0, bottom_x = 0, bottom_y = 0;
    int i, j, k;
    int temp[COL], sum, begin, end;
    
    for (i = 0; i < ROW; i++) { // for each row i
        
        memset(temp, 0, sizeof(temp));
        
        for (j = i; j < ROW; j++) { // try these sums row (1) rows (1 + 2), (1 + 2 + 3)
                                    // in the second iteration row (2) then rows (2 + 3) and so on
            for (k = 0; k < COL; k++)
                temp[k] += a[j][k];
            
            sum = kadane(temp, COL, &begin, &end); // from this array for exmaple rows (1+2) summed, find the largest
            
            if (sum > max_sum) {
                max_sum = sum;
                top_x = i; // starting row number
                bottom_x = j; // ending row number
                top_y = begin; // starting col number
                bottom_y = end; // ending col number
            }
        }
    }
    
    printf("(top x, top y) (%d, %d)\n", top_x, top_y);
    printf("(bottom x, bottom y) (%d, %d)\n", bottom_x, bottom_y);
    printf("max sum is: %d\n", max_sum);
}

int main() {
    
    int a[ROW][COL] = {1, 2, -1, -4, -20,
                      -8, -39, 89, 2, 1,
                       3, -81, 10, 1, -3,
                      -4, -1, 1, -7, -6};
    
    maximum_sum_2d(a);
    
    return 0;
}
