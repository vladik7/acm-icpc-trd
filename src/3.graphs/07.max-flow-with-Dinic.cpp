struct flow_graph {
    struct edge {
        int u, v, f = 0, c;
        edge(int u, int v, int c) : u(u), v(v), c(c) {}
    };
    int n, s{}, t{};
    vector<edge> edges;
    vector<vector<int>> gr;
    vector<int> ptr, d;
    long long max_flow = 0;
    explicit flow_graph(int n) : n(n){
        gr.resize(n);
    }
    void add_edge(int u, int v, int c, int back = 0) {
        gr[u].emplace_back(edges.size());
        edges.emplace_back(u, v, c);
        gr[v].emplace_back(edges.size());
        edges.emplace_back(v, u, back);
    }
    bool bfs() {
        d.assign(n, -1);
        d[s] = 0;
        vector<int> q = {s};
        for (int i = 0; i < q.size(); ++i) {
            for (auto &id: gr[q[i]]) {
                edge &e = edges[id];
                if (edges[id].f < edges[id].c && d[e.v] == -1) {
                    d[e.v] = d[e.u] + 1;
                    q.emplace_back(e.v);
                }
            }
        }
        return d[t] != -1;
    }
    int dfs(int v, int flow) {
        if (flow == 0) return 0;
        if (v == t) return flow;
        for (; ptr[v] < gr[v].size(); ptr[v]++) {
            int id = gr[v][ptr[v]];
            edge &e = edges[id];
            if (d[e.v] != d[e.u] + 1) continue;
            int delta = dfs(e.v, min(flow, e.c - e.f));
            if (delta){
                e.f += delta;
                edges[id ^ 1].f -= delta;
                return delta;
            }
        }
        return 0;
    }
    long long get_flow(int _s, int _t) {
        s = _s, t = _t;
        max_flow = 0;
        while (bfs()) {
            ptr.assign(n, 0);
            while(int cur = dfs(s, 2e9)) max_flow += cur;
        }
        return max_flow;
    }
};