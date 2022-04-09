class Matrix
{
public:
	int cols, rows;
	vvll data;
	int mod;
	Matrix(int _rows, int _cols, int _mod, bool ones = false)
	{
		rows = _rows; cols = _cols;
		mod = _mod;
		data.clear();
		data.resize(rows, vll(cols, 0));
		if (ones)
		{
			for (int i = 0; i < min(rows, cols); i++) data[i][i] = 1;
		}
	}

	vll& operator[] (int idx)
	{
		return data[idx];
	}

	Matrix operator*(Matrix& b)
	{
		Matrix res(rows, b.cols, mod);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < b.cols; ++j)
			{
				for (int k = 0; k < cols; ++k)
				{
					res[i][j] += data[i][k] * b[k][j] % mod;
				}
				res[i][j] %= mod;
			}
		}
		return res;
	}

	Matrix operator%(int mod)
	{
		Matrix res = *this;
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				res[i][j] %= mod;
		return res;
	}

	Matrix binpow(int nn) {
		if (nn == 0)
			return Matrix(rows, cols, mod, true);
		if (nn % 2 == 1)
			return (binpow(nn - 1) % mod * (*this)) % mod;
		else {
			auto bb = binpow(nn / 2) % mod;
			return (bb * bb) % mod;
		}
	}
};