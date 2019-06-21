//
//  main.cpp
//  multi-source-bfs
//
//  Created by FB on 6/20/19.
//  Example Problem: https://www.spoj.com/problems/BITMAP/
//  This is just Dijkstra!!!! but add multiple sources initially
//

#include <iostream>
#include <set>
#include <queue>
#include <vector>

#define INF 100000
#define MAX 3004

int R, C;
char m[MAX][MAX];
int distance[MAX][MAX];
int dx[4] = {1 , 0 , -1 , 0};
int dy[4] = {0 , 1 , 0 , -1};
std::vector<std::pair<int,int>> sources;

void dijkstra() {
    std::priority_queue<std::pair<int,std::pair<int,int>>,
    std::vector<std::pair<int, std::pair<int,int>>>,
    std::greater<std::pair<int, std::pair<int,int>>>> q; // min priority queue

    // init distances to INF or INT_MAX for now
    std::vector<std::vector<int>> distance(MAX, std::vector<int>(MAX));
    std::vector<std::vector<int>> visited(MAX, std::vector<int>(MAX));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            distance[i][j] = INF;
            visited[i][j] = false;
        }
    }

    // all sources have distance 0
    for (int i = 0; i < sources.size(); i++) {
        q.push({0, sources[i]});
        distance[sources[i].first][sources[i].second] = 0;
    }

    while (!q.empty()) {
        std::pair<int,int> u = q.top().second;
        int x = u.first, y = u.second;
        q.pop();

        // In Dijkstra, we visit each node once
        // but priority_queue doesn't support a decrease key
        // operation, so we use a visited array

        if (visited[x][y]) { continue; }
        visited[x][y] = true;

        for (int k = 0; k < 4; k++) {
            int next_x = x + dx[k];
            int next_y = y + dy[k];
            if (next_x < 0 || next_x >= R || next_y < 0 || next_y >= C) {
                continue;
            }

            if (distance[next_x][next_y] > distance[x][y] + 1) {
                distance[next_x][next_y] = distance[x][y] + 1;
                q.push({distance[next_x][next_y], {next_x, next_y}});
            }
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
        dijkstra();
    }
    return 0;
}
