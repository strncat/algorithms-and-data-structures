//
//  BFS on a matrix
//  Example Problem http://codeforces.com/contest/616/problem/C
//
//  Created by Fatima B on 1/11/16.
//  Copyright © 2016 Fatima B. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <queue>

#define MAX 1006

int n, m;
char a[MAX][MAX];
bool visited[MAX][MAX];

// example problem: "two empty cells are adjacent if they share a side"
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int x, int y) {
    std::queue<int> qx;
    std::queue<int> qy;
    int d = 0; // counting the number of nodes that are connected to x,y

    qx.push(x);
    qy.push(y);
    visited[x][y] = true;

    while(!qx.empty()) {
        int topx = qx.front();
        int topy = qy.front();
        qx.pop();
        qy.pop();

        d++;

        for(int i = 0; i < 4; i++) {
            x = topx + dx[i];
            y = topy + dy[i];
            // out of range
            if (x < 0 || x >= n || y < 0 || y >= m) { continue; }
            if (visited[x][y] == false) {
                visited[x][y] = true;
                qx.push(x);
                qy.push(y);
            }
        }
    }
    return d;
}

void connected_components() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j] == false) {
                bfs(i, j);
                // do stuff
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }
    connected_components();
    return 0;
}
