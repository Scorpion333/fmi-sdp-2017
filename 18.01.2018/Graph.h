#pragma once
#include<iostream>
#include<queue>
#include<set>
#include"ExtendedVector.h"
using std::cout;
using std::queue;
using std::set;

// Some notes:
// - I've used some functions for vectors, written in 'ExtendedVector.h'
// - In a const method, we can call only const methods, that's why we need 2 versions of 'neighbours_of'

template<typename T>
class Graph {
    vector<T> vertexes;                             // Vector, containing all the vertexes in the graph
    vector<vector<T>> lists;                        // Adjacency lists - for each i, 
                                                    // lists[i] contains the neighbours of vertexes[i]
public:
                                                    // 'Getters' for the neighbours of a vertex - 2 because:
    vector<T>& neighbours_of(const T& v) {          // - this version allows us to change the returned vector
        return lists[index_of(v, vertexes)];
    }
    vector<T> neighbours_of(const T& v) const {     // - this version allows us to use 'neighbours_of' in const methods
        return lists[index_of(v, vertexes)];
    }                                               // GOOD NEWS: Compiler is clever and it always calls the right version,
                                                    //            we don't need to think about it.

    bool has_vertex(const T& v) const {
        return has_element(v, vertexes);
    }

    bool has_edge(const T& a, const T& b) const {
        return has_vertex(a) && has_vertex(b) && has_element(b, neighbours_of(a));
    }

    void add_vertex(const T& v) {                   // Adds the vertex and creates a list of neighbours for it,
        if (!has_vertex(v)) {                       // if it needs to be added.
            vertexes.push_back(v);
            lists.push_back({});                    // {} == empty vector 
        }
    }

    void add_edge(const T& a, const T& b) {
        add_vertex(a);                              // We add A and B, if needed.
        add_vertex(b);
        if (!has_element(b, neighbours_of(a)))      // If B is not in neighbours_of(a),
            neighbours_of(a).push_back(b);          // we put it there.
    }

    void remove_edge(const T& a, const T& b) {
        if(has_vertex(a))                               // If there's no A, there is no such edge
            remove_from_vector(b, neighbours_of(a));    // If there is A, we make sure b is not a neighbour of it.
    }

    bool has_path(const T& a, const T& b) const {
        set<T> visited;
        return has_path(a, b, visited);
    }
    bool has_path(const T& a, const T& b, set<T>& visited) const {
        if (a == b) {
            return true;
        }
        visited.insert(a);
        vector<T> neighbours = neighbours_of(a);
        for (int i = 0; i < neighbours.size(); i++) {
            if (visited.count(neighbours[i]) == 0 && has_path(neighbours[i], b))
                return true;
        }
        return false;
    }

    void print_bfs(const T& start) const {
        set<T> visited;
        visited.insert(start);

        queue<T> q;
        q.push(start);

        while (!q.empty()) {
            T crr = q.front();
            q.pop();
            cout << crr << ' ';

            vector<T> neighbours = neighbours_of(crr);
            
            for (unsigned i = 0; i < neighbours.size(); i++) {
                if (visited.count(neighbours[i]) == 0) {          // if neighbours[i] is visited
                    q.push(neighbours[i]);
                    visited.insert(neighbours[i]);                // I had to move the insertion here,
                }                                                 // we'll see why today (18.01.2018)
            }
        }
    }
    
    void print_dfs(const T& start) {
        set<T> visited;
        print_dfs(start, visited);
    }
    
    void print_dfs(const T& start, set<T>& visited) {
        visited.insert(start);
        cout << start << ' ';
        vector<T> neighbours = neighbours_of(start);

        for (unsigned i = 0; i < neighbours.size(); i++) {
            if (visited.count(neighbours[i]) == 0) {            // if neighbours[i] is visited
                print_dfs(neighbours[i], visited);
            }
        }
    }

    // Prints the graph in the fromat from g.txt
    void print() {
        cout << vertexes.size() << ' ';

        int edges_number = 0;
        for (int i = 0; i < vertexes.size(); i++) {
            edges_number += neighbours_of(vertexes[i]).size();
        }
        cout << edges_number << '\n';

        for (int i = 0; i < vertexes.size(); i++) {
            cout << vertexes[i] << '\n';
        }
        for (int i = 0; i < vertexes.size(); i++) {
            for (int j = 0; j <= neighbours_of(vertexes[i]).size(); j++) {
                cout << vertexes[i] << ' '
                    << neighbours_of(vertexes[i])[j] << '\n';
            }
        }
    }
};


// Test time!

#include<fstream>
#include<string>
#include"expect.h"
using std::ifstream;
using std::string;

int test_graph() {
    cout << "--- --- TESTING THE GRAPH --- ---\n\n";

    Graph<string> g;

    ifstream in("g.txt");
    int vertexes, edges;
    in >> vertexes >> edges;
    
    for (int i = 0; i < vertexes; i++) {
        string crr_vertex;
        in >> crr_vertex;
        g.add_vertex(crr_vertex);
    }
    for (int i = 0; i < edges; i++) {
        string a, b;
        in >> a >> b;
        g.add_edge(a, b);
    }

    cout << "has_path:\n\n"
        << g.has_path("Lovech", "Plovdiv")
        << g.has_path("Montana", "Burgas")
        << g.has_path("Sofia", "Ruse");
    expect("110");

    cout << "BFS:\n\n";
    g.print_bfs("Montana");
    expect("Montana Sofia Lovech Dupnica Tarnovo Ruse Plovdiv Varna Burgas");

    cout << "DFS:\n\n";
    g.print_dfs("Montana");
    expect("Montana Sofia Dupnica Plovdiv Burgas Tarnovo Varna Lovech Ruse");
    return 0;
}