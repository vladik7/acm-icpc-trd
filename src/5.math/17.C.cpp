const int maxn = 2000;
LL C[maxn + 1][maxn + 1];
void comb(LL mod = LLONG_MAX)
{
	for (int nn = 0; nn <= maxn; ++nn) {
		C[nn][0] = C[nn][nn] = 1;
		for (int kk = 1; kk < nn; ++kk)
			C[nn][kk] = (C[nn - 1][kk - 1] + C[nn - 1][kk]) % mod;
	}
}