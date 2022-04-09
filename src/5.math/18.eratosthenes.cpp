const LL max_er = 1e7;
vll min_div(max_er + 1, 0);
vi er_used(max_er + 1, 1);
vll primes;
vector<pii> divs;
 
void eratosthenes()
{
	er_used[0] = er_used[1] = 0;
	for (LL i = 2; i <= max_er; ++i)
	{
		if (!er_used[i]) continue;
		primes.push_back(i);
		min_div[i] = i;
		for (LL j = i * i; j <= max_er; j += i)
		{
			er_used[j] = 0;
			if (!min_div[j]) min_div[j] = i;
		}
	}
}
 
void get_divs(LL n)
{
	while (n != 1)
	{
		LL cur = min_div[n];
		LL cnt = 0;
		while (n % cur == 0)
		{
			n /= cur;
			cnt++;
		}
		divs.push_back({ cur, cnt });
	}
}