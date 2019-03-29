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
// https://github.com/fbroom/algorithms-and-data-structures/blob/master/geometry/lines.cpp
#include "lines.h"

typedef struct circle {
    point c; // center
    double r; // radius
    circle(point c, double r) {
        this->c = c; this->r = r;
    }
} circle;

// all the derivation of this was on paper ... seems too long? am I do it the ugly way?
bool intersection_line_circle(circle t, line l, point *p1_out, point *p2_out) {
    // (x - cx)^2 + (y - cy)^2 = r^2
    // ax + by + c = 0

    if (l.b <= EPSILON) { // vertical line case

        double asquared = l.a*l.a;
        double a = asquared;
        double b = -2.0*asquared*t.c.y;
        double c = l.c*l.c + 2.0*l.a*t.c.x*l.c + asquared*t.c.x*t.c.x +
                    asquared*t.c.y*t.c.y - t.r*t.r*asquared;

        double st = b*b - 4*a*c;
        if (st < 0.0) {  return false; } // no solutions

        st = sqrt(b*b - 4*a*c);
        double sol1 = (-b + st) / (2*a);
        double sol2 = (-b - st) / (2*a);

        p1_out->y = sol1;
        p2_out->y = sol2;
        p1_out->x = -l.c/l.a;
        p2_out->x = -l.c/l.a;
        return true;
    }

    // normal case

    double bsquared = l.b*l.b;
    double w = l.c + (l.b * t.c.y);
    double a = bsquared + l.a*l.a;
    double b = 2.0 * ((l.a * w) - (bsquared * t.c.x));
    double c = (bsquared * t.c.x* t.c.x) + w*w - (bsquared * t.r * t.r);

    double st = b*b - 4*a*c;

    if (st < 0.0) { return false; } // no solutions

    st = sqrt(st);
    double sol1 = (-b + st) / (2*a);
    double sol2 = (-b - st) / (2*a);

    p1_out->x = sol1;
    p2_out->x = sol2;
    p1_out->y = ((-l.c) - l.a*sol1) / l.b;
    p2_out->y = ((-l.c) - l.a*sol2) / l.b;
    return true; // 2 solutions
}

void tests() {
    // test 1 intersection
    // (x - 2)2 + (y + 3)2 = 4 and 2x + 2y = -1
    // ~~~ (3.64 , - 4.14) and (0.86 , -1.36)
    circle t1(point(2,-3), 2.0);
    line l1(2, 2, 1);
    point p1, p2;
    assert(intersection_line_circle(t1, l1, &p1, &p2) == true);
    assert(fabs(p1.x - 3.64194) <= EPSILON && fabs(p1.y - -4.14194) <= EPSILON);
    assert(fabs(p2.x - 0.85805) <= EPSILON && fabs(p2.y - -1.35805) <= EPSILON);

    // test 3 intersection horizontal line
    circle t2(point(0,0), 1.0); // unit circle
    line l2(0.0, 1.0, -1.0); // y = 1
    assert(intersection_line_circle(t2, l2, &p1, &p2) == true);
    assert(fabs(p1.x - 0.0) <= EPSILON && fabs(p1.y - 1.0) <= EPSILON);
    assert(fabs(p2.x - 0.0) <= EPSILON && fabs(p2.y - 1.0) <= EPSILON);

    // test 4 intersection horizontal line
    line l3(0.0, 1.0, -5.0); // y = 5
    assert(intersection_line_circle(t2, l3, &p1, &p2) == false);
    assert(fabs(p1.x - 0.0) <= EPSILON && fabs(p1.y - 1.0) <= EPSILON);
    assert(fabs(p2.x - 0.0) <= EPSILON && fabs(p2.y - 1.0) <= EPSILON);

    // test 5 intersection vertical line
    circle t4(point(0,5), 1.0); //
    line l4(1.0, 0.0, -1.0); // x = 1
    assert(intersection_line_circle(t2, l4, &p1, &p2) == true);
    assert(fabs(p1.x - 1.0) <= EPSILON && fabs(p1.y - 0.0) <= EPSILON);
    assert(fabs(p2.x - 1.0) <= EPSILON && fabs(p2.y - 0.0) <= EPSILON);
}

int main() {
    tests();
    return 0;
}
