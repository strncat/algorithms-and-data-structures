//
//  triangles
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

typedef struct triangle {
    point a;
    point b;
    point c;
    triangle(point a, point b, point c) {
        this->a = a; this->b = b; this->c = c;
    }
} line;

// using points a, b and c
double signed_triangle_area(triangle t) {
    return ((t.a.x*t.b.y - t.a.y*t.b.x + t.a.y*t.c.x -
             t.a.x*t.c.y + t.b.x*t.c.y - t.c.x*t.b.y) / 2.0);
}

double triangle_area(triangle t) {
    return fabs(signed_triangle_area(t));
}

//using sides a, b and c
double triangle_area(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    double asquared = p * (p - a) * (p - b) * (p - c);
    return sqrt(asquared);
}

//using sides a, b and c
double circumscribed_circle_radius(double a, double b, double c) {
    double area = triangle_area(a, b, c);
    return (a * b * c) / (4 * area);
}

//using sides a, b and c
double inscribed_circle_radius(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    double rsquared = (p - a) * (p - b) * (p - c) / p;
    return sqrt(rsquared);
}

void tests() {
    // signed area of (-2,2), (1,3) and (3,0) = -5.5
    point a(-2,2), b(1,3), c(3,0);
    triangle t(a, b, c);
    assert(signed_triangle_area(t) == -5.5);
    assert(triangle_area(t) == 5.5);
}

int main() {
    tests();
    return 0;
}
