#include <iostream>
#include <math.h>

/* resource: programming problems advanced algorithms */

struct vector {
    double x;
    double y;

    vector operator*(const double& scalar) const {
        return {x * scalar, y * scalar};
    }

    vector operator+(const vector& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    double dot(const vector& rhs) const {
        return (x * rhs.x) + (y * rhs.y);
    }

    double length() const {
        return sqrt(x * x + y * y);
    }
};

vector unit_vector(const vector& v) {
    if (v.x == 0 && v.y == 0) {
        return v;
    }
    auto length = v.length();
    return {v.x / length, v.y / length};
}

typedef struct line { // = a + t*u
    vector a;
    vector u;
} line;

double distance(const vector& a, const vector& b) {
    return sqrt(pow (a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/* distance from a point p to the line a + tu
(1) find vector (a - p) (not perpendicular to the line)
(2) the projection of (a - p) onto u gives the distance from (a) to the intersection
    where it's perpendicular to the line
    the length of the projection is calculated by the dot product between u and a-p
(3) vector (n) then can be calculated as the dot product * vector u
(4) given vector (n) and vector (a - p) then the perpendicular direction is just ((a - p) - n)
(5) the length of that is the distance from a point to a line
*/
double distance_point_to_line(const vector& p, const line& l) {
    vector a_minus_p = l.a + (p * -1.0);
    vector n  = l.u * a_minus_p.dot(l.u);
    vector prep = a_minus_p + (n * -1);
    return prep.length();
}

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}

