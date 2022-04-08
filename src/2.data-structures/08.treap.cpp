mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
struct Treap {
    struct Node {
        Node *l, *r;
        T x;
        int y, size;

        Node() {}

        Node(T _x) : x(_x), y(rng()), l(nullptr), r(nullptr), size(1) {}
    };

    typedef Node *NodePtr;
    NodePtr root;

    Treap() : root(nullptr) {}

    inline int sz(NodePtr a) const {
        return a ? a->size : 0;
    }

    inline void recalc(NodePtr a) {
        if (!a) return;
        a->size = sz(a->l) + sz(a->r) + 1;
    }


private:
    void merge(NodePtr a, NodePtr b, NodePtr &c) {
        if (!a) c = b;
        else if (!b) c = a;
        else {
            if (a->y > b->y) {
                merge(a->r, b, a->r);
                c = a;
            } else {
                merge(b->l, a, b->l);
                c = b;
            }
            recalc(c);
        }
    }

    void split(NodePtr c, T k, NodePtr &a, NodePtr &b) {
        if (!c) { a = b = nullptr; }
        else {
            if (c->x < k) {
                split(c->r, k, c->r, b);
                a = c;
            } else {
                split(c->l, k, a, c->l);
                b = c;
            }
        }
        recalc(c);
    }

    void insert(NodePtr &ptr, NodePtr val) {
        if (!ptr) ptr = val;
        else if (ptr->x != val->x) {
            if (val->y > ptr->y) {
                split(ptr, val->x, val->l, val->r);
                ptr = val;
            } else {
                if (val->x > ptr->x) insert(ptr->r, val);
                else insert(ptr->l, val);
            }
        }
        recalc(ptr);
    }

    void erase(NodePtr ptr, T k) {
        if (!ptr) return;
        if (ptr->x == k) {
            merge(ptr->l, ptr->r, ptr);
        } else if (ptr->x > k) erase(ptr->l, k);
        else erase(ptr->r, k);
        recalc(ptr);
    }

    int count(NodePtr ptr, T k) {
        if (!ptr) return 0;
        if (ptr->x == k) return 1;
        if (ptr->x > k) return count(ptr->l, k);
        else return count(ptr->r, k);
    }

    int order_of_key(NodePtr ptr, T k) {
        if (!ptr) return 0;
        if (ptr->x < k) return sz(ptr->l) + 1 + order_of_key(ptr->r, k);
        else return order_of_key(ptr->l, k);
    }

    T get_by_id(const NodePtr ptr, int id) const {
        if (sz(ptr->l) == id) return ptr->x;
        if (id < sz(ptr->l)) return get_by_id(ptr->l, id);
        else return get_by_id(ptr->r, id - sz(ptr->l) - 1);
    }

public:
    inline unsigned int size() {
        return sz(root);
    }

    inline void insert(T k) {
        insert(root, new Node(k));
    }

    inline void erase(T k) {
        erase(root, k);
    }

    inline int count(T k) {
        return count(root, k);
    }

    inline int order_of_key(T k) {
        return order_of_key(root, k);
    }

    inline T operator[](int pos) const {
        return get_by_id(root, pos);
    }
};