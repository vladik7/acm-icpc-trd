template<typename T>
class rope
{
public:
	int size() { if (root) return root->cnt; else return 0; }
private:
	struct item
	{
		~item(void) { if (left) { delete left; left = nullptr; } if (right) { delete right; right = nullptr; } };
		item(void) : left(nullptr), right(nullptr), cnt(0), prior(0), rev(false) {};
		item(T val) : left(nullptr), right(nullptr), cnt(0), prior(rand()), rev(false), value(val), res(val) {};
		
		T value;
		T res;
		item *left, *right;
		int prior;
		int cnt;
		bool rev;
	};
	using pitem = item*;

	pitem root;

	int cnt(pitem it) {
		return it ? it->cnt : 0;
	}

	void upd_vals(pitem it) {
		if (it)
		{
			it->cnt = cnt(it->left) + cnt(it->right) + 1;
			it->res = it->value;
			if (it->left) it->res += it->left->res;
			if (it->right) it->res += it->right->res;
		}
	}

	friend void push(pitem it) {
		if (it && it->rev) {
			it->rev = false;
			swap(it->left, it->right);
			if (it->left)  it->left->rev ^= true;
			if (it->right)  it->right->rev ^= true;
		}
	}

	void merge(pitem& t, pitem l, pitem r) {
		push(l);
		push(r);
		if (!l || !r) t = l ? l : r;
		else if (l->prior > r->prior) merge(l->right, l->right, r), t = l;
		else merge(r->left, l, r->left), t = r;
		upd_vals(t);
	}

	void split(pitem t, pitem& l, pitem& r, int key, int add = 0) {
		if (!t) return void(l = r = 0);
		push(t);
		int cur_key = add + cnt(t->left);
		if (key <= cur_key) split(t->left, l, t->left, key, add), r = t;
		else split(t->right, t->right, r, key, add + 1 + cnt(t->left)), l = t;
		upd_vals(t);
	}

	void erase(pitem& t, int pos) {
		if (t->cnt == pos) merge(t, t->left, t->right);
		else erase(pos < t->cnt ? t->left : t->right, pos);
	}

	void heapify(pitem t) {
		if (!t) return;
		pitem mx = t;
		if (t->left && t->left->prior > mx->prior) mx = t->left;
		if (t->right && t->right->prior > mx->prior) mx = t->right;
		if (mx != t) {
			swap(t->prior, mx->prior);
			heapify(mx);
		}
	}

	pitem build(const T* a, int n) {
		if (n == 0) return nullptr;
		int mid = n / 2;
		pitem t = new item(a[mid]);
		t->left = build(a, mid);
		t->right = build(a + mid + 1, n - mid - 1);
		heapify(t);
		upd_vals(t);
		return t;
	}

public:
	rope() { root = nullptr; }
	~rope() { if (root) { delete root; root = nullptr; } }
	rope(int n, const T* a)
	{
		root = build(a, n);
	}

	void insert(int pos, T val) {
		pitem new_item = new item(val);
		pitem t1, t2;
		split(root, t1, t2, pos);
		merge(t1, t1, new_item);
		merge(root, t1, t2);
	}

	void insert(int pos, rope<T> *t) {
		pitem new_item = t->root;
		pitem t1, t2;
		split(root, t1, t2, pos);
		merge(t1, t1, new_item);
		merge(root, t1, t2);
	}

	void push_back(T val) { insert(size(), val); }
	void push_back(rope<T> *t) { insert(size(), t); }

	void erase(int pos) { erase(root, pos); }

	rope<T>* erase(int l, int r) {
		pitem t1, t2, t3;
		split(root, t1, t2, l);
		split(t2, t2, t3, r - l + 1);
		merge(root, t1, t3);
		auto t = new rope<T>;
		t->root = t2;
		return t;
	}

	void reverse(int l, int r) {
		pitem t1, t2, t3;
		split(root, t1, t2, l);
		split(t2, t2, t3, r - l + 1);
		t2->rev ^= true;
		merge(root, t1, t2);
		merge(root, root, t3);
	}

	T get_val(int l, int r) {
		pitem t1, t2, t3;
		split(root, t1, t2, l);
		split(t2, t2, t3, r - l + 1);
		auto cur_res = t2->res;
		merge(root, t1, t2);
		merge(root, root, t3);
		return cur_res;
	}

	rope<T>* substr(int l, int r)
	{
		auto t = new rope<T>;
		pitem t1, t2, t3;
		split(root, t1, t2, l);
		split(t2, t2, t3, r - l + 1);
		auto cur_res = t2;
		merge(root, t1, t2);
		merge(root, root, t3);
		t->root = t2;
		return t;
	}

	friend ostream& operator<< (ostream& out, pitem t) {
		if (!t)  return out;
		push(t);
		out << t->left;
		out << t->value;
		out << t->right;
		return out;
	}

	friend ostream& operator<< (ostream& out, rope<T> &t) {
		out << t.root;
		return out;
	}

};