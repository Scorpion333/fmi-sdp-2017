struct Node {
    char data;
    Node *left, *right;
    Node(char _data, Node* _left, Node* _right) : data(_data), left(_left), right(_right) {}
};

Node* buildTree(const string& s) {
    if (s == "") {
        return nullptr;
    }
    return new Node(
        s[s.length() / 2],
        buildTree(s.substr(0, s.length() / 2)),
        buildTree(s.substr(s.length() / 2 + 1))
    );
}