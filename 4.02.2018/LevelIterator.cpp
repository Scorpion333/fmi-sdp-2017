struct Node {
    int x;
    Node *left, *right;
};

class LevelIterator {
    queue<const Node*> q;

public:
    LevelIterator(const Node* ptr) : q() {
        if(ptr)
            q.push(ptr);
    }
    
    // Returns the sum of current level's elements
    int currentSum() const {
        queue<const Node*> copy_of_q = q;
        int sum = 0;
        while (!copy_of_q.empty()) {
            sum += copy_of_q.front()->x;
            copy_of_q.pop();
        }
        return sum;
    }
    
    void next() {
        int size = q.size();
        while (size > 0) {
            if (q.front()->left)  q.push(q.front()->left);
            if (q.front()->right) q.push(q.front()->right);
            q.pop();
            size--;
        }
    }
    
    bool end() const {
        return q.empty();
    }
};