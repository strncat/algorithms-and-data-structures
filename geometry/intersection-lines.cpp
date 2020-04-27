//
//  lines
//  source: programming challanges
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

// line forms:
// point-slope: y-y1=m(x-x1)
// slope-intercept: y=mx+b
// standard form: ax + by + c = 0

typedef struct line { // the standard form
    // ax + by + c = 0
    double a;
    double b;
    double c;
    line() { this->a = 0; this->b = 0; this->c = 0; }
    line(double a, double b, double c) {
        this->a = a; this->b = b; this->c = c;
    }
} line;

void points_to_line(point p1, point p2, line *l) {
    // m = p2.y - p1.y / p2.x - p1.x
    // (y - p1.y) = m (x - p1.x)
    // y - mx - p1.y + p1.x*m
    // a = -m, b = 1, c = (a*p1.x) - (b*p1.y)
    if (p1.x == p2.x) { // vertical line
        l->a = 1;
        l->b = 0;
        l->c = -p1.x;
    } else {
        double m = (p2.y-p1.y)/(p2.x-p1.x);
        l->a = -m;
        l->b = 1;
        l->c = m*p1.x - p1.y;
        //l->c = -(l->a * p1.x) - (l->b * p1.y);
    }
}

void point_and_slope_to_line(point p1, double m, line *l) {
    // (y - y1) = m(x - x1)
    // y - y1 - m*x + m*x1 = 0
    // y - m*x - y1 + m*x1 = 0
    l->a = -m;
    l->b = 1;
    //-((l->a*p1.x) + (l->b*p1.y))
    l->c = m*p1.x - p1.y;
}

bool parallel(line l1, line l2) {
    return (fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON);
}

bool same_line(line l1, line l2) {
    return (fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON
            && fabs(l1.c - l2.c) <= EPSILON);
}

int intersection(line l1, line l2, point *p) {
    if (same_line(l1, l2)) {
        return 2; // infinitely many points
    }

    if (parallel(l1, l2)) { // parallel don't intersect
        return 0;
    }

    // ax + by + c = 0 and a'x + b'y + c' = 0
    // by = -ax - c and b'y = - a'x - c'
    // (- ax - c) * b'  = (- a'x - c') * b
    // -b'ax - b'c = - ba'x - bc'
    // ba'x - b'ax = b'c - bc'
    // x = (b'c - bc') / (ba' - b'a)

    p->x = (l2.b*l1.c - l1.b*l2.c) / (l1.b*l2.a - l2.b*l1.a);

    // we need to test for the case if one of the two lines is vertical
    // they can't be both vertical at the same time
    // ax + by + c = 0
    // y = -(ax - c) / b

    if (fabs(l1.b) > EPSILON) { // plug in x in the first line
        p->y = ((-l1.a*p->x) - l1.c) / l1.b;
    } else { // plugin x in the second line
        p->y = ((-l2.a*p->x) - l2.c) / l2.b;
    }
    return 1;
}

double angle_intersection(line l1, line l2) {
    double theta = atan2((l1.a*l2.b - l2.a*l1.b),(l1.a*l2.a + l1.b*l2.b));
    theta = theta * (180 / M_PI);
    if (theta < 0) { theta = 180 + theta; }
    return theta;
}

double angle_intersection_slope(double m1, double m2) {
    double theta = atan2((m2 - m2),(1 - m2*m1));
    return theta * (180 / M_PI);
}

void closest_point(point p_in, line l, point *p_out) {
    line prep;

    if (fabs(l.b) <= EPSILON) { // vertical line
        p_out->x = -(l.c/l.a); // book says only -l.c hmmmmm
        p_out->y = p_in.y; // share the same y
        return;
    } else if (fabs(l.a) <= EPSILON) { // horizontal line
        p_out->x = p_in.x;
        p_out->y = -(l.c/l.b); // book says only -l.c hmmmmm
        return;
    }

    // slope is -a, so the prependicular slope is -1/-a = 1/a
    point_and_slope_to_line(p_in, 1/l.a, &prep);
    intersection(l, prep, p_out);
}

void tests() {
    // test 1
    // Convert y-3 = 5(x-4) to standard form = y - 5x + 17 = 0
    point p(4,3);
    double m = 5;
    line l;
    point_and_slope_to_line(p, m, &l);
    assert(l.a == -5 && l.b == 1 && l.c == 17);

    // test 2
    // convert (1,6), (3,-4) to y + 5x - 11 = 0;
    // (y-6) = -5(x-1) => y - 6 + 5x - 5 = 0 => y
    point p1(1,6);
    point p2(3,-4);
    points_to_line(p1, p2, &l);
    assert(l.a == 5 && l.b == 1 && l.c == -11);

    // test 3
    // y + 3x - 5 = 0 && y + 3x - 10 = 0
    line l1(3, 1, -5);
    line l2(3, 1, -1);
    assert(parallel(l1, l2) == true);

    // test 4
    point pi;
    assert(intersection(l1, l2, &pi) == 0); // parallel lines don't intersect

    // test 5
    // y - 3x + 3 = 0
    // y - 2.3x - 4 = 0
    line l3(-3, 1, 3);
    line l4(-2.3, 1, -4);
    assert(intersection(l3, l4, &pi) == 1);
    assert(fabs(pi.x - 10.0) <= EPSILON && fabs(pi.y - 27.0) <= EPSILON);

    // test 6
    line l5(-4, 1, -2);
    line l6(1, 1, -3);
    assert(fabs(angle_intersection(l5, l6) - 59.036243) <= EPSILON);

    // test 7 prependicular lines
    line l7(-2, 1, -1);
    line l8(0.5, 1, -4);
    assert(fabs(angle_intersection(l7, l8) - 90.00) <= EPSILON);

    // test 8 parallel lines
    assert(fabs(angle_intersection(l1, l2) - 0.00) <= EPSILON);

    // test 9 closest point
    line l9(2, 0, -5);
    point p9(4,2);
    point p_out;
    closest_point(p9, l9, &p_out);
    assert(fabs(p_out.x - 2.5) <= EPSILON && fabs(p_out.y - 2.0) <= EPSILON);
}

int main() {
    tests();
    return 0;
}
