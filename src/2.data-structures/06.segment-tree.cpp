template<typename T, class F = function<T(const T &, const T &)>>
struct SegmentTree {
    int n{};
    vector<T> st;
    F merge = [&](const T &i, const T &j) {
        return i ^ j;
    };
    T neutral = 0;

    SegmentTree() = default;

    explicit SegmentTree(const vector<T> &a) {
        n = (int) a.size();
        st.resize(2 * (int) a.size());
        for (int i = 0; i < n; i++) st[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) st[i] = merge(st[i << 1], st[i << 1 | 1]);
    }

    T get(int l, int r) {
        T resl = neutral, resr = neutral;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = merge(resl, st[l++]);
            if (r & 1) resr = merge(st[--r], resr);
        }
        return merge(resl, resr);
    }

    void upd(int p, T val) {
        for (st[p += n] = val; p > 1; p >>= 1) {
            if (p & 1) {
                st[p >> 1] = merge(st[p ^ 1], st[p]);
            } else {
                st[p >> 1] = merge(st[p], st[p ^ 1]);
            }
        }
    }
};