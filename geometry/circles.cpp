//
//  main.cpp
//  circles
//  source: programming challenges
//
//  Created by Fatima B on 10/8/15.
//  Copyright © 2015 nemo. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <assert.h>

const static double EPSILON = 0.00005;

typedef struct point {
    double x;
    double y;
    point() {this->x = 0; this->y = 0;}
    point(double x, double y) { this->x = x; this->y = y; }
    bool operator==(const point &p2) const {
        return (fabs(x - p2.x) <= EPSILON && fabs(y - p2.y) <= EPSILON);
    }
} point;

typedef struct circle {
    point c; // center
    double r; // radius
    circle(point c, double r) {
        this->c = c; this->r = r;
    }
} line;

double area(circle t) {
    return M_PI * t.r * t.r;
}

double circumference(circle t) {
    return 2.0 * M_PI * t.r;
}

void tests() {
    // test 1
    // circle area
    circle t(point(0,0), 3.0);
    assert(fabs(area(t) - 3*3*M_PI) <= EPSILON);
    assert(fabs(circumference(t) - 2*3*M_PI) <= EPSILON);
}

int main() {
    tests();
    return 0;
}
