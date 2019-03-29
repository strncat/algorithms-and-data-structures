//
//  Generic Tree
//  Each node has a vector of children
//  I know I used this definition for one competitive programmnig problem
//  But I don't remember which one and I don't think this is useful?
//  Also this implementation is very restrictive 1-2 implies 1 is the parent of 2
//  Consider removing this file?
//

#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <set>
#include <map>

class Vertex {
public:
    long value;
    int depth;
    Vertex *parent; // parent pointer
    std::vector<Vertex*> children; // list of children
    int name; // not needed, for debugging purposes
    Vertex() {
        value = depth = 0;
        parent = NULL;
    }
};

class Tree {
public:
    int nvertices;
    Vertex *vertices; // fast access to all nodes
    Tree(int nvertices) {
        this->nvertices = nvertices;
        vertices = new Vertex[nvertices + 1];
    }
    void insertEdge(int x, int y) {
        vertices[x].children.push_back(&vertices[y]);
        vertices[y].parent = &vertices[x];
        vertices[y].depth = vertices[x].depth + 1;
        vertices[x].name = x;
        vertices[y].name = y;
    }
    void print() {
        for (int i = 1; i <= nvertices; i++) {
            std::cout << "vertex: " << i << ": ";
            std::vector<Vertex*> vc = vertices[i].children;
            for (auto child = vc.begin(); child != vc.end(); child++) {
                std::cout << (*child)->name << " (" << (*child)->depth << ") ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    /* Example Input / Output
     5
     1 2
     1 3
     1 4
     2 5
     vertex: 1: 2 (1) 3 (1) 4 (1)
     vertex: 2: 5 (2)
     vertex: 3:
     vertex: 4:
     vertex: 5:
     */
    int N, x, y;
    scanf("%d", &N);
    Tree g = Tree(N);
    g.vertices[1].depth = 0; // 1 is always the root
    for (int i = 0; i < N - 1; i++) { // a tree has only N-1 edges
        scanf("%d %d", &x, &y);
        g.insertEdge(x, y);
    }
    g.print();
    return 0;
}
