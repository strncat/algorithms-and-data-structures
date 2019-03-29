//
// Find the intersection of two axis-aligned! rectangles
//

#include <iostream>
#include <unordered_map>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

class Rectangle {
public:
    int x;
    int y;
    int width;
    int height;
    Rectangle(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    Rectangle() {
    }
};

// assuming origin is at topleft of the screen
std::pair<int,int> overlap(int p1, int l1, int p2, int l2) { // intersection of two line segments
    int highest_start_point = max(p1, p2);
    int lowest_end_point = min(p1 + l1, p2 + l2);
    
    if (highest_start_point >= lowest_end_point) {
        return std::pair<int, int>(INT_MAX, INT_MAX); // undefined
    }
    return std::pair<int, int>(highest_start_point, lowest_end_point - highest_start_point);
}

Rectangle intersection(Rectangle rect1, Rectangle rect2) {
    Rectangle rect;
    std::pair<int, int> xintersection = overlap(rect1.x, rect1.width, rect2.x, rect2.width);
    std::pair<int, int> yintersection = overlap(rect1.y, rect1.height, rect2.y, rect2.height);
    rect.x = xintersection.first;
    rect.width = xintersection.second;
    rect.y = yintersection.first;
    rect.height = yintersection.second;
    return rect;
}

int main() {
    //unitTests();
    return 0;
}
