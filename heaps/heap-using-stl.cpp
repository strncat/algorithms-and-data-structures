#include <iostream>
#include <queue>

struct comparator {
    bool operator() (int i, int j) {
        return i > j;
    }
};

int main() {
    // max heap
    std::priority_queue<int, std::vector<int>> maxHeap;

    // min heap
    std::priority_queue<int, std::vector<int>, comparator> minHeap;
    // or
    // std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    // or
    // use a max heap with each entry x = -x

    minHeap.push(5);
    minHeap.push(4);
    minHeap.push(3);
    minHeap.push(2);
    minHeap.push(1);
    minHeap.push(0);

    maxHeap.push(5);
    maxHeap.push(4);
    maxHeap.push(3);
    maxHeap.push(2);
    maxHeap.push(1);
    maxHeap.push(0);

    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;

    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    return 0;
}
