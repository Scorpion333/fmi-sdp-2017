void count_occs(char g[100][100], int n, int k, int start_vertex, map<string, int>& occs, string crr_word) {
    for (int j = 0; j < n; j++) {                           
        crr_word += g[start_vertex][j];     
        if (g[start_vertex][j] && crr_word.size() <= k) {
            if (crr_word.size() == k) {
                if (occs.count(crr_word) == 1)
                    occs[crr_word]++;
                else
                    occs[crr_word] = 1;
            }
            count_occs(g, n, k, j, occs, crr_word);
        }
        crr_word.pop_back();
    }
}

string mostCommon(char g[100][100], int n, int k) {
    map<string, int> occs;
    for (int i = 0; i < n; i++) {
        count_occs(g, n, k, i, occs, "");
    }
    int max = 0;
    string word;
    for (pair<string, int> _pair : occs) {
        if (_pair.second > max) {
            max = _pair.second;
            word = _pair.first;
        }
    }
    return word;
}