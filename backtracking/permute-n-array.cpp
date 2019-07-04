//
//
//  Given n arrays generate all permutations such as each element comes from a different array
//  Given {1,2}, {3,4}, {5,6}
//  We generate {1,3,5}, {1,4,6}, {1,3,6}, {1,4,5}, {2,3,5}, {2,3,6}, {2,4,5}, {2,4,6}
//
//

#include <iostream>
#include <stack>

void permute_core(int a[3][2], int m, int n, std::stack<int> &s, int index) {
    if (index >= m) {
        std::stack<int> temp;
        while (!s.empty()) {
            printf("%d ", s.top());
            temp.push(s.top());
            s.pop();
        }
        printf("\n");
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        s.push(a[index][i]);
        permute_core(a, m, n, s, index+1);
        s.pop();
    }
}

void permute(int a[3][2], int m, int n) {
    std::stack<int> s;
    permute_core(a, m, n, s, 0); // starting at index = 0
}


int main() {
    int a[3][2] = {1,2,3,4,5,6}; // three arrays
    permute(a,3,2);
    return 0;
}
