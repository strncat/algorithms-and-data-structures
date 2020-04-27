//
//  CLRS: Chapter 33 - Computational Geometry
//  Determine whether two line segments intersect
//
//  Created by FB on 4/26/20.
//  tested against https://practice.geeksforgeeks.org/problems/check-if-two-line-segments-intersect/
//

#include <iostream>

typedef struct point {
    long long x;
    long long y;
} point;

// check whether p-p1 is on the left or right of segment p2-p1
int direction(point p, point q, point t) {
    // find t-p x q-p
    // t-p = (t.x-p.x, t.y-p.y)
    // q-p = (q.x-p.x, q.y-p.y)
    long long cross_product = (t.x - p.x) * (q.y - p.y) -
                              (t.y - p.y) * (q.x - p.x);

    if (cross_product > 0) {
        return 1; // t-p is clockwise from q-p
    } else if (cross_product < 0) {
        return -1; // anticlockwise
    }
    return 0; // colinear
}

bool on_segment(point p, point q, point t) {
    if (t.x >= std::min(p.x, q.x) &&
        t.x <= std::max(p.x, q.x) &&
        t.y >= std::min(p.y, q.y) &&
        t.y <= std::max(p.y, q.y)) {
        return true;
    }
    return false;
}

bool segment_intersection(point p1, point p2, point p3, point p4) {
    int d1 = direction(p3, p4, p1); // which side is p1 on?
    int d2 = direction(p3, p4, p2); // same for p2
    int d3 = direction(p1, p2, p3);
    int d4 = direction(p1, p2, p4);

    // this means each line segment straddles the line containing the
    // other segment so they intersect
    if  (d1 != d2 && d3 != d4) {
        return true;
    }

    // d1 = 0 means that p1,p3,p4 are colinear, we check if p1
    // is between the segment p3, p4
    if (d1 == 0 and on_segment(p3, p4, p1)) {
        return true;
    }
    if (d2 == 0 and on_segment(p3, p4, p2)) {
        return true;
    }
    if (d3 == 0 and on_segment(p1, p2, p3)) {
        return true;
    }
    if (d4 == 0 and on_segment(p1, p2, p4)) {
        return true;
    }
    return false;
}

int main() {
    freopen("in.txt" , "r" , stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        point p1, p2, p3, p4;
        scanf("%lld %lld %lld %lld", &p1.x, &p1.y, &p2.x, &p2.y);
        scanf("%lld %lld %lld %lld", &p3.x, &p3.y, &p4.x, &p4.y);
        printf("%d\n", segment_intersection(p1,p2,p3,p4));
    }
    return 0;
}
