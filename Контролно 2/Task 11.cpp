void find_unique(int g[100][100], int n, int m, int start_vertex, set<int>& results, int crr_sum) {
    for (int j = 0; j < n; j++) {                           // If j is not a neighbour of start_vertex, nothing happens.
        crr_sum += g[start_vertex][j];                      // If it is, we add the edge to the sum. 
        if (g[start_vertex][j] && crr_sum <= m) {           // If the sum is still small enough,
            results.insert(crr_sum);                        // we add it in the set of unique results.
            find_unique(g, n, m, j, results, crr_sum);      // And we add the sums that we can reach by going though j's neoghbours.
        }
    }
}
int countUnique(int g[100][100], int n, int m) {
    set<int> results;
    for (int i = 0; i < n; i++) {               // For each vertex, find all the numbers
        find_unique(g, n, m, i, results, 0);    // that we can reach if we start from this vertex
    }
    return results.size();
}
