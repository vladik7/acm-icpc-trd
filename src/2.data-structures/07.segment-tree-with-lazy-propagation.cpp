template<typename T = int, typename TU = int>
struct SegmentTree {
    SegmentTree() = default;
    explicit SegmentTree(const vector<T> &a) {
        n = (int) a.size();
        st.resize(4 * n);
        upd_val.resize(4 * n);
        upd_fl.resize(4 * n);
        build(1, 0, n, a);
    }

    explicit SegmentTree(int _n) {
        n = _n;
        st.resize(4 * n);
        upd_val.resize(4 * n);
        upd_fl.resize(4 * n);
    }

    T get(int l, int r) {
        return get(1, 0, n, l, r);
    }

    T get(int p) {
        return get(p, p + 1);
    }

    void upd(int p, TU val) {
        upd(p, p + 1, val);
    }

    void upd(int l, int r, TU val) {
        upd(1, 0, n, l, r, val);
    }

private:
    void push(int tv, int tl, int tr) {
        if (upd_fl[tv] == 1 && tr - tl > 1) {
            int tm = (tl + tr) >> 1;
            st[tv * 2] = recalc_on_segment(st[tv * 2], upd_val[tv], tl, tm);
            st[tv * 2 + 1] = recalc_on_segment(st[tv * 2 + 1], upd_val[tv], tm, tr);
            if (upd_fl[tv * 2]) upd_val[tv * 2] = upd_push_val(upd_val[tv * 2], upd_val[tv]);
            else upd_val[tv * 2] = upd_val[tv];
            if (upd_fl[tv * 2 + 1]) upd_val[tv * 2 + 1] = upd_push_val(upd_val[tv * 2 + 1], upd_val[tv]);
            else upd_val[tv * 2 + 1] = upd_val[tv];
            upd_fl[tv * 2] = upd_fl[tv * 2 + 1] = 1;
            upd_fl[tv] = 0;
        }
    }

    inline bool intersect(int l1, int r1, int l2, int r2) {
        return l1 < r2 && l2 < r1;
    }

    T get(int tv, int tl, int tr, int l, int r) {
        if (tl >= l && tr <= r) return st[tv];
        push(tv, tl, tr);
        int tm = (tl + tr) >> 1;
        if (!intersect(tl, tm, l, r)) return get(tv * 2 + 1, tm, tr, l, r);
        if (!intersect(tm, tr, l, r)) return get(tv * 2, tl, tm, l, r);
        return merge_nodes(get(tv * 2, tl, tm, l, r), get(tv * 2 + 1, tm, tr, l, r), tl, tr);
    }

    void build(int tv, int tl, int tr, const vector<T> &a) {
        if (tr - tl == 1) {
            st[tv] = a[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build(tv * 2, tl, tm, a);
            build(tv * 2 + 1, tm, tr, a);
            st[tv] = merge_nodes(st[tv * 2], st[tv * 2 + 1], tl, tr);
        }
    }

    void upd(int tv, int tl, int tr, int l, int r, TU val) {
        if (tl >= l && tr <= r) {
            st[tv] = recalc_on_segment(st[tv], val, tl, tr);
            if (upd_fl[tv]) upd_val[tv] = upd_push_val(upd_val[tv], val);
            else upd_val[tv] = val;
            upd_fl[tv] = 1;
        } else {
            push(tv, tl, tr);
            int tm = (tl + tr) >> 1;
            if (intersect(tl, tm, l, r)) upd(tv * 2, tl, tm, l, r, val);
            if (intersect(tm, tr, l, r)) upd(tv * 2 + 1, tm, tr, l, r, val);
            st[tv] = merge_nodes(st[tv * 2], st[tv * 2 + 1], tl, tr);
        }
    }

    int n{};
    vector<T> st;
    vector<TU> upd_val;
    vector<char> upd_fl;
    T merge_nodes(const T &i, const T &j, int tl, int tr) {
        return i + j;
    };
    T recalc_on_segment(const T &i, const TU &j, int tl, int tr) {
        return i + (tr - tl) * j;
    };
    TU upd_push_val(const TU &i, const TU &j, int tl = 0, int tr = 1){
        return i + j;
    }
};