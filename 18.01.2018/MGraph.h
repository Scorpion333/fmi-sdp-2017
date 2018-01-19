#pragma once
#include<iostream>
#include<queue>
#include<set>
#include<vector>
using std::cout;
using std::queue;
using std::set;
using std::vector;

// "Matrix" graph. Its vertexes' values are the numbers: 0, 1, 2, ...

class MGraph {
    vector<vector<bool>> matr;
    
public:
    int size() const {
        return matr.size();
    }

    bool has_vertex(int v) const {
        return v < size();            // <=> v is index in matr
    }

    bool has_edge(int a, int b) const {
        return matr[a][b];
    }

    // Pushes a row and a column in the matrix
    void add_one_vertex() {
        matr.push_back(vector<bool>(size(), false));
        for (int i = 0; i < size(); i++) {
            matr[i].push_back(false);
        }
    }

    // If the vertexes are: 0, 1, 2, 3, 4, and we want to add 8, we need to add 5, 6 and 7 too.
    // (This is a little stupid, but whatever.)
    void add_vertex(int v) {
        while (!has_vertex(v))
            add_one_vertex();
    }

    // Works only if both vertexes are in the graph
    void add_edge(int a, int b) {
        matr[a][b] = true;
    }

    // Works only if both vertexes are in the graph
    void remove_edge(int a, int b) {
        matr[a][b] = false;
    }

    vector<int> neighbours_of(int v) const {
        vector<int> result;
        for (int i = 0; i < size(); i++) {
            if(has_edge(v, i))
                result.push_back(i);
        }
        return result;
    }

    void print_bfs(int start) const {
        set<int> visited;
        visited.insert(start);

        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int crr = q.front();
            q.pop();
            cout << crr << ' ';

            vector<int> neighbours = neighbours_of(crr);

            for (unsigned i = 0; i < neighbours.size(); i++) {
                if (visited.count(neighbours[i]) == 0) {          // if neighbours[i] is visited
                    q.push(neighbours[i]);
                    visited.insert(neighbours[i]);                // I had to move the insertion here,
                }                                                 // we'll see why today (18.01.2018)
            }
        }
    }

    void print_dfs(int start) const {
        // ...
    }
};