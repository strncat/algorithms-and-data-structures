//
// DFS (Strongly Connected Components Kosaraju)
// some parts are from geeksforgeeks
// 2014
//

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using std::vector;

void print(vector<vector<int>>& g) {
    for (int i = 0; i < g.size(); i++) {
        printf("%d: ", i);
        for (int j = 0; j < g[i].size(); j++) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

vector<vector<int>> transpose(vector<vector<int>>& g) {
    vector<vector<int>> t;
    for (int i = 0; i < g.size(); i++) {
        t.push_back(vector<int>());
    }
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            t[g[i][j]].push_back(i);
        }
    }
    return t;
}

void reset(bool *visited, int n) {
    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }
}

// first pass calculate finishing times
void dfs(vector<vector<int>>& g, int start, bool *visited, std::stack<int> *finished) {
    std::stack<int> s;
    std::stack<int> t;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int v = s.top();
        t.push(v); // another stack to maintain finishing times
        s.pop();
        for (auto i = g[v].begin(); i != g[v].end(); i++) {
            if (visited[*i] == false) {
                visited[*i] = true;
                s.push(*i);
            }
        }
    }
    while (!t.empty()) {
        finished->push(t.top());
        t.pop();
    }
}

int dfs(vector<vector<int>>& g, int start, bool *visited) {
    std::stack<int> s;
    s.push(start);
    int count = 1;
    visited[start] = true;

    while (!s.empty()) {
        int v = s.top();
        s.pop();
        for (auto i = g[v].begin(); i != g[v].end(); i++)
            if (visited[*i] == false) {
                visited[*i] = true;
                s.push(*i);
                count++;
            }
    }
    return count;
}

void strongly_connected_components(vector<vector<int>>& g) {
    std::stack<int> finished;
    std::vector<int> counts;
    bool visited[g.size()];

    // (1) transose of g
    vector<vector<int>> t = transpose(g);

    // (2) order vertices by their finishing times
    reset(visited, (int)t.size());
    for(int i = (int)t.size()-1; i >= 0; i--) {
        if (visited[i] == false) {
            dfs(t, i, visited, &finished);
        }
    }

    // (3) DFS again use the order computed using the stack finished
    reset(visited, (int)g.size());
    while (finished.empty() == false) {
        int v = finished.top();
        finished.pop();

        // print strongly connected component of the popped vertex
        if (visited[v] == false) {
            int count = dfs(g, v, visited);
            counts.push_back(count);
        }
    }

    sort(counts.begin(), counts.end());
    for (auto i = counts.rbegin(); i != counts.rend(); i++) {
        printf("%d\n", *i);
    }
}

// Test Cases
// SSC1.txt 9 Answer: 3,3,3,0,0
// SCC2.txt 8 Answer: 3,3,2,0,0
// SCC3.txt 8 Answer: 3,3,1,1,0
// SSC4.txt 8 Answer: 7,1,0,0,0
// SSC5.txt 12 Answer: 6,3,2,1,0
// SSC6.txt 15 Answer: 5,4,3,2,1

int main() {
    freopen("sample.in", "r", stdin);

    vector<vector<int>> graph;
    for (int i = 0; i < 9; i++) {
        graph.push_back(vector<int>());
    }

    graph[0].push_back(3);
    graph[1].push_back(7);
    graph[2].push_back(5);
    graph[3].push_back(6);
    graph[4].push_back(1);
    graph[5].push_back(8);
    graph[6].push_back(0);
    graph[7].push_back(4);
    graph[7].push_back(5);
    graph[8].push_back(6);
    graph[8].push_back(2);

    // SSC1.txt 9 Answer: 3,3,3,0,0
    strongly_connected_components(graph);
    return 0;
}
