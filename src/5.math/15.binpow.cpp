LL binpow(LL aa, LL nn, LL mod) {
	if (nn == 0)
		return 1ll;
	if (nn % 2 == 1)
		return (binpow(aa, nn - 1, mod) % mod * aa) % mod;
	else {
		LL bb = binpow(aa, nn / 2, mod) % mod;
		return (bb * bb) % mod;
	}
}