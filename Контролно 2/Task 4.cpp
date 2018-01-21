struct Node {
    int data;
    Node *left, *right;
    Node(int _data, Node* _left, Node* _right) :data(_data), left(_left), right(_right) {}
};

Node* buildTree(const vector<int>& v) {
    if (v.size() == 0) {
        return nullptr;
    }
    return new Node(
        v[v.size() / 2],
        buildTree(vector<int>(v.begin(), v.begin() + v.size() / 2)),
        buildTree(vector<int>(v.begin() + v.size() / 2 + 1, v.end()))
    );
}