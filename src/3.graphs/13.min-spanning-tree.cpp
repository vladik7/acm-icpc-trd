class DSU
{
private:
	vector<int> p;
public:
	DSU(int sz) { p.resize(sz); }

	void make_set(int v) {
		p[v] = v;
	}

	int get(int v) {
		return (v == p[v]) ? v : (p[v] = get(p[v]));
	}

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (rand() & 1)
			swap(a, b);
		if (a != b)
			p[a] = b;
	}
};

vector<pair<pii, LL>> min_spanning_tree(vector<pair<pii, LL>>& edges, LL n)
{
	vector<pair<pii, LL>> res;
	sort(all(edges), [](pair<pii, LL>& x1, pair<pii, LL>& x2) { return x1.second < x2.second; });
	DSU dsu(n + 1);

	for (int i = 1; i < n + 1; i++) dsu.make_set(i);

	for (auto &cur_edge : edges)
	{
		int u = cur_edge.first.first;
		int v = cur_edge.first.second;
		LL w = cur_edge.second;
		auto p1 = dsu.get(u);
		auto p2 = dsu.get(v);
		if (p1 != p2)
		{
			res.push_back(cur_edge);
			dsu.unite(u, v);
		}
	}

	return res;
}