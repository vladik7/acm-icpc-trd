template<typename T, class F = function<T(const T &, const T &)>>
struct SegmentTree {
    int n{};
    vector<T> st;
    F merge;
    T neutral{};
    SegmentTree()= default;
    explicit SegmentTree(const vector<T> &a, F _merge, T _neutral) {
        n = (int) a.size();
        st.resize(2 * (int) a.size());
        merge = _merge;
        neutral = _neutral;
        for (int i = 0; i < n; i++) st[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) st[i] = merge(st[i << 1], st[i << 1 | 1]);
    }

    T get(int l, int r) {
        T res = neutral;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, st[l++]);
            if (r & 1) res = merge(res, st[--r]);
        }
        return res;
    }

    void upd(int p, T val) {
        for (st[p += n] = val; p > 1; p >>= 1) st[p >> 1] = merge(st[p], st[p ^ 1]);
    }
};

template<typename T, class F = function<T(const T &, const T &)>>
struct HLD {
    HLD(int n, vector<T> &values, vector<pair<int, int>> &edges) {
        this->timer = 0;
        this->n = n;
        this->g.resize(n);
        this->treeSize.resize(n);
        this->topId.resize(n);
        this->pos.resize(n);
        this->parent.resize(n);
        this->depth.resize(n);
        for (auto[u, v] : edges) {
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        Calculate(0, 0);
        for (int i = 0; i < n; i++) {
            std::sort(g[i].rbegin(), g[i].rend(), [&](int u, int v) {
                return treeSize[u] < treeSize[v];
            });
        }

        BuildHld(0, 0, 0);
        auto orderedValues = values;
        for (int i = 0; i < n; i++) {
            orderedValues[pos[i]] = values[i];
        }
        tree = SegmentTree<T>(orderedValues, merge, neutral);
    }

    T get(int u, int v) {
        T ans = neutral;
        while (topId[u] != topId[v]) {
            if (depth[topId[u]] < depth[topId[v]]) swap(u, v);
            int low = pos[topId[u]];
            int high = pos[u] + 1;
            ans = merge(ans, tree.get(low, high));
            u = parent[topId[u]];
        }

        int low = pos[u];
        int high = pos[v];
        if (low > high) swap(low, high);
        ans = merge(ans, tree.get(low, high + 1));
        return ans;
    }

    void upd(int v, T val) {
        tree.upd(pos[v], val);
    }

private:
    int n{};
    int timer{};
    vector<int> depth;
    vector<int> treeSize;
    vector<vector<int>> g;
    vector<int> topId;
    vector<int> pos;
    SegmentTree<T> tree{};
    vector<int> parent;

    void BuildHld(int v, int curTopId, int curParent = -1) {
        pos[v] = timer++;
        topId[v] = curTopId;
        bool heavyEdge = true;
        for (auto to : g[v]) {
            if (to == curParent) continue;
            if (heavyEdge) {
                BuildHld(to, curTopId, v);
                heavyEdge ^= 1;
            } else {
                BuildHld(to, to, v);
            }
        }
    }

    void Calculate(int v, int curParent) {
        parent[v] = curParent;
        treeSize[v] = 1;
        depth[v] = depth[curParent] + 1;
        for (auto to : g[v]) {
            if (to == curParent) continue;
            Calculate(to, v);
            treeSize[v] += treeSize[to];
        }
    }
    F merge = [&](const T &i, const T &j) { return i + j; };
    T neutral = 0;
};