#include <stdio.h>

/* Interval Scheduling from the Algorithms Design
 Input 3 0 6 5 7 8 9 5 9 1 2 3 4 0 5Output
 4 4 1
 */

#define N 25
#define maximum(a, b) a > b ? a : b

void merge(int a[N][2], int begin, int end, int mid) {
    
    int b[N][N], c[N][N];
    int i, j, k, m, index;
    
    for (i = 0; begin + i <= mid; i++) {
        b[i][0] = a[begin + i][0];
        b[i][1] = a[begin + i][1];
    }
    
    for (j = 0; mid + 1 + j <= end; j++) {
        c[j][0] = a[mid + 1 + j][0];
        c[j][1] = a[mid + 1 + j][1];
    }

    k = 0, m = 0, index = begin;
    while (k < i && m < j) {
        if (b[k][1] < c[m][1]) {
            a[index][0] = b[k][0];
            a[index][1] = b[k][1];
            index++;
            k++;
        }
        else {
            a[index][0] = c[m][0];
            a[index][1] = c[m][1];
            index++;
            m++;
        }
    }
    /* left overs */
    while (k < i) {
        a[index][0] = b[k][0];
        a[index][1] = b[k][1];
        index++;
        k++;
    }
    while (m < j) {
        a[index][0] = c[m][0];
        a[index][1] = c[m][1];
        index++;
        m++;
    }
}

void merge_sort(int a[N][2], int begin, int end) {
    
    int mid = (end + begin) / 2;
    
    if (end - begin > 0) {
        merge_sort(a, begin, mid);
        merge_sort(a, mid + 1, end);
        merge(a, begin, end, mid);
    }
    return;
}

/* let p(j) be the (largest) index i < j such that i & j are disjoint */
void disjoint(int a[N][2], int p[N], int n) {
    
    int i, j;
    
    p[1] = 0;
    for (i = 2; i < n; i++)
        for (j = i - 1; j >= 1; j--)
            if (a[i][0] >= a[j][1]) {
                p[i] = j;
                break;
            }
}

void build_table(int a[N][2], int M[N], int v[N], int p[N], int n) {
    
    int j;
    
    M[0] = 0;
    for (j = 1; j < n; j++)
        M[j] = maximum(v[j] + M[p[j]], M[j - 1]);
    
}

void print_solution(int j, int events[N][2], int M[], int v[], int p[]) {
    
    if (j != 0) {
        if (v[j] + M[p[j]] >= M[j - 1]) {
            printf("(%d %d) ", events[j][0], events[j][1]);
            print_solution(p[j], events, M, v, p);
        }
        else {
            print_solution(j - 1, events, M, v, p);
        }
    }
}

int main() {
    
    int i, n, events[N][2], value[N], p[N] = {0}, M[N];
    
    events[1][0] = 0;
    events[1][1] = 6;
    
    events[2][0] = 5;
    events[2][1] = 7;
    
    events[3][0] = 8;
    events[3][1] = 9;
    
    events[4][0] = 5;
    events[4][1] = 9;
    
    events[5][0] = 1;
    events[5][1] = 2;
    
    events[6][0] = 3;
    events[6][1] = 4;
    
    events[7][0] = 0;
    events[7][1] = 5;
    
    n = 8;
    
    value[1] = 1;
    value[2] = 1;
    value[3] = 1;
    value[4] = 1;
    value[5] = 1;
    value[6] = 1;
    value[7] = 1;
    
    merge_sort(events, 0, n - 1);
        
    disjoint(events, p, n);
    
    build_table(events, M, value, p, n);
    
    printf("Tasks sorted by finish time: \n");
    for (i = 1; i < n; i++) {
        printf("(%d %d) ", events[i][0], events[i][1]);
    }
    
    printf("\n\nDisjoint table:\n");
    for (i = 1; i < n; i++) {
        printf("%d ", p[i]);
    }
    
    printf("\n\nM Table:\n");
    for (i = 1; i < n; i++) {
        printf("%d ", M[i]);
    }

    printf("\n\nMaximum number of tasks: %d\n", M[n - 1]);
    
    printf("\nTasks Chosen: \n");
    print_solution(n - 1, events, M, value, p);
    printf("\n");
    
    return 0;
}