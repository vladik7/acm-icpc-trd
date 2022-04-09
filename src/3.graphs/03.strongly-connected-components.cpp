void dfs(int v, vvi& g, vi& used, vi &topsort)
{
	used[v] = 1;
	for (auto& to : g[v])
	{
		if (!used[to]) dfs(to, g, used, topsort);
	}
	topsort.push_back(v);
}


void dfs(int v, vvi& g, vi& used, vvi &components)
{
	used[v] = 1;
	components.back().push_back(v);
	for (auto& to : g[v])
	{
		if (!used[to]) dfs(to, g, used, components);
	}
}

vvi build_scc(vvi& g, vvi &rg)
{
	vi used(g.size(), 0);
	vi rused(rg.size(), 0);
	vvi components;
	vi topsort;
	int n = g.size();

	for (int i = 1; i < n; i++)
	{
		if (used[i]) continue;
		dfs(i, g, used, topsort);
	}

	reverse(all(topsort));

	for (int i = 0; i < topsort.size(); i++)
	{
		int v = topsort[i];
		if (rused[v]) continue;
		components.push_back(vi());
		dfs(v, rg, rused, components);
	}

	return components;
}