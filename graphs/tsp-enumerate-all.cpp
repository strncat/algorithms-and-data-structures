//
//  main.cpp
//  uhunt
//
//  Traveling Sales Man
//  Example Problem https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=152
//  2017/03/14
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <math.h>

using std::vector;
using std::pair;
using std::unordered_map;

double dist(vector<int>& a, unordered_map<int,pair<int,int>>& m) {
    double sum = 0.0;
    for (int i = 1; i < a.size(); i++) {
        double x1 = m[a[i-1]].first, x2 = m[a[i]].first;
        double y1 = m[a[i-1]].second, y2 = m[a[i]].second;
        sum += sqrt ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        sum += 16.0;
    }
    return sum;
}

int main() {
    freopen("sample.in", "r", stdin);

    int n, x, y;
    vector<int> a;
    unordered_map<int,pair<int,int>> m;

    while (scanf("%d", &n) && n != 0) {
        a.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            m[i] = pair<int,int>(x,y);
            a.push_back(i);
        }

        double d, min = 10000.0;
        do {
            // calculate current distance
            d = dist(a, m);
            if (d < min) {
                min = d;
            }
        } while (std::next_permutation(a.begin(), a.end()));

        printf("Number of feet of cable required is %.2lf.\n", min);
    }
    return 0;
}
