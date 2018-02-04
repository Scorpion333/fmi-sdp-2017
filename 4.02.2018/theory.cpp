template<typename T>
struct Node { /*...*/ };

template<typename T>
class BinTree {
    Node<T>* root;

public:
    class I {
        Node<T>* ptr;
    public:
        I(Node<T>* _ptr) : ptr(_ptr) {}
        bool operator != (I other) {}

        T operator*() { /*...*/ }
        I& operator++() {
            // Moves the iterator to the right subtree of the current node
        }
        I& operator--() {
            // Moves the iterator to the left subtree of the current node
        }
    };
    
    I iterator() {
        return I(root);
    }
    I end() {
        return I(nullptr);
    }

    bool search(T const& x) {
        I it = iterator();
        while (it != end()) {
            if (*it == x)
                return true;
            if (*it < x)
                ++it;
            if (x < *it)
                --it;
        }
        return false;
    }
};

class Dictionary { /*...*/ };
class ArrayDictionary : public Dictionary { /*...*/ };
class AVLDictionary : public Dictionary { /*...*/ };
class HashDictionary : public Dictionary { /*...*/ };

class Taxi {
private:
    char company[50];
    double rate;
public:
    friend istream& operator >> (istream& in, Taxi& taxi);
    friend ostream& operator << (ostream& out, const Taxi& taxi);
};
ostream& operator << (ostream& out, const Taxi& taxi) {
    return out << taxi.company << ' ' << taxi.rate << '\n';
}
istream& operator >> (istream& in, Taxi& taxi) {
    return in >> taxi.company >> taxi.rate;
}