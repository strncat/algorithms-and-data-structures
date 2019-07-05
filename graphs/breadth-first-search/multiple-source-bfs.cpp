//
//  main.cpp
//  multi-source-bfs
//
//  Created by FB on 6/20/19.
//  Example Problem: https://www.spoj.com/problems/BITMAP/
//  This is just BFS with multiple sources
//

#include <iostream>
#include <set>
#include <queue>
#include <vector>

#define INF 100000
#define MAX 3004

int R, C;
char m[MAX][MAX];
int dx[4] = {1 , 0 , -1 , 0};
int dy[4] = {0 , 1 , 0 , -1};
std::vector<std::pair<int,int>> sources;

void multi_bfs() {
    std::queue<std::pair<int,int>> q;
    int distance[R][C];

    // init distances to INF or INT_MAX for now
    std::vector<std::vector<int>> visited(MAX, std::vector<int>(MAX));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            visited[i][j] = false;
        }
    }

    // all sources have distance 0
    for (int i = 0; i < sources.size(); i++) {
        q.push(sources[i]);
        visited[sources[i].first][sources[i].second] = true;
        distance[sources[i].first][sources[i].second] = 0;
    }

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            int next_x = x + dx[k];
            int next_y = y + dy[k];
            if (next_x < 0 || next_x >= R || next_y < 0 || next_y >= C) {
                continue;
            }

            if (visited[next_x][next_y]) { continue; }
            visited[next_x][next_y] = true;

            distance[next_x][next_y] = distance[x][y] + 1;
            q.push({next_x, next_y});
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", distance[i][j]);
        }
        printf("\n");
    }
}

void read_board() {
    scanf("%d %d\n", &R, &C);
    char line[MAX];
    for (int i = 0; i < R; i++) {
        fgets(line, MAX, stdin);
        for (int j = 0; j < C; j++) {
            m[i][j] = line[j]; // put each char in its cell
            if (line[j] == '1') { // Joe's position
                sources.push_back({i,j});
            }
        }
    }
}

int main() {
    //freopen("in.txt" , "r" , stdin);
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        sources.clear();
        read_board();
        multi_bfs();
    }
    return 0;
}
