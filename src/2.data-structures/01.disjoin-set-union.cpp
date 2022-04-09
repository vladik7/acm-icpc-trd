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