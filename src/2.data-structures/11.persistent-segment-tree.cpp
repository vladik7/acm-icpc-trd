template<class T>
class Vertex
{
public:
	Vertex* left, * right;
	T val;
	Vertex(T _val) { left = right = nullptr; val = _val; }
	Vertex(Vertex* _left, Vertex* _right, function<T(T, T)> BinF, T _val)
	{
		left = _left;
		right = _right;
		val = _val;
		if (left) val = BinF(val, left->val);
		if (right) val = BinF(val, right->val);
	}
};


template<class T, int sz, class ArrT>
class SegTree
{
private:
	T SideVal;
	function<T(T, T)> BinF;
	function<T(ArrT)> BuildLF;
public:
	SegTree(T _SideVal, function<T(T, T)> _BinF, function<T(ArrT)> _BuildLF) {
		SideVal = _SideVal;
		BinF = _BinF;
		BuildLF = _BuildLF;
	}

	Vertex<T>* build(vector<ArrT>& a, int tl, int tr) {
		if (tl == tr) return new Vertex<T>(BuildLF(a[tl]));
		else {
			int tm = (tl + tr) / 2;
			return new Vertex<T>(build(a, tl, tm), build(a, tm + 1, tr), BinF, SideVal);
		}
	}

	Vertex<T>* update(Vertex<T> *t, int tl, int tr, int pos, ArrT val)
	{
		if (tl == tr) return new Vertex<T>(BuildLF(val));
		else
		{
			int tm = (tl + tr) / 2;
			if (pos <= tm) return new Vertex<T>(update(t->left, tl, tm, pos, val), t->right, BinF, SideVal);
			else return new Vertex<T>(t->left, update(t->right, tm + 1, tr, pos, val), BinF, SideVal);
		}
	}

	T get_val(Vertex<T>* t, int tl, int tr, int l, int r)
	{
		if (l > r) return SideVal;
		if (tl == l && tr == r) return t->val;
		int tm = (tl + tr) / 2;
		auto left = get_val(t->left, tl, tm, l, min(tm, r));
		auto right = get_val(t->right, tm + 1, tr, max(tm + 1, l), r);
		return BinF(left, right);
	}
};

auto BinF = [](LL left, LL right) -> $SegTreeType$ {
};

auto BuildLeaf = [](LL val) -> $SegTreeType$ {
	
};

SegTree<LL, 200100, LL> st(0, BinF, BuildLeaf);