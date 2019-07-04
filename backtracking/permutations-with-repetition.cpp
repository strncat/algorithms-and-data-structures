//
//  permutations with repetitions n^n
//

#include <iostream>
#include <vector>

void print(std::vector<int> a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void permutationsWithRepetition(std::vector<int> a, std::vector<int> current, int index, int last, std::vector<std::vector<int>> &list) {
    for (int i = 0; i <= last; i++) {
        current[index] = a[i];
        if (index == last) { // last possible index
            list.push_back(current);
        } else {
            permutationsWithRepetition(a, current, index+1, last, list);
        }
    }
}

int main() {
    std::vector<std::vector<int>> list;
    std::vector<int> a = {1, 2, 3}, current = {0, 0, 0};
    permutationsWithRepetition(a, current, 0, 2, list);
    for (auto t = list.begin(); t != list.end(); t++) {
        print(*t, 3);
    }

    // prints
    // 1 1 1
    // 1 1 2
    // 1 1 3
    // 1 2 1
    // 1 2 2
    // 1 2 3
    // 1 3 1
    return 0;
}
