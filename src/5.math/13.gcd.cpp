LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}