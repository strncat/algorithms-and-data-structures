//
//  main.cpp
//  circles intersection
//  source: http://paulbourke.net/geometry/circlesphere/
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
    point() { this->x = 0; this->y = 0; }
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
} circle;


// derivation is easy using the source above
int intersection_circles(circle r1, circle r2, point *i_out, point *j_out) {
    double dx = r2.c.x - r1.c.x;
    double dy = r2.c.y - r1.c.y;

    double d = sqrt((dy*dy) + (dx*dx)); // distance between two circles

    if (d > r2.r + r1.r) { // no solution
        return 0;
    }

    if (d < fabs(r2.r - r1.r)) { // circle contained in the other
        return 0;
    }

    if (d <= EPSILON && fabs(r2.r - r1.r) <= EPSILON) { // many solutions
        return 2;
    }

    // considering the right angle triangles in the figure in the link
    // p0p2p3 and p1p2p3
    // a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2

    // distance from p2 to p0
    double a = (r2.r*r2.r - r1.r*r1.r + d*d) / (2.0*d);

    // subtitute back to find h
    double h = r1.r*r1.r - a*a;

    // find p2
    point p2;
    p2.x = r1.c.x + (dx * a/d);
    p2.y = r1.c.y + (dy * a/d);

    // find the intersection points
    double ry = h * (r2.c.y - r1.c.y)/d;
    double rx = h * (r2.c.x - r1.c.x)/d;

    i_out->x = r1.c.x + rx;
    j_out->x = r2.c.x - rx;
    i_out->y = r1.c.y - ry;
    j_out->y = r2.c.y - ry;
    return 1;
}

void tests() {
    circle t(point(0,0),3), s(point(0,0),4);
    point p1, p2;
    int b = intersection_circles(t, s, &p1, &p2);
    assert(b == 0);

    s.r = 3;
    b = intersection_circles(t, s, &p1, &p2);
    assert(b == 2);

    s.r = 3;
    s.c.x = -10;
    s.c.y = 10;
    b = intersection_circles(t, s, &p1, &p2);
    assert(b == 0);
}

int main() {
    tests();
    return 0;
}
