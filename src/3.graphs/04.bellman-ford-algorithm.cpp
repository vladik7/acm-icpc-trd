/* Finds SSSP with negative edge weights.
 * Possible optimization: check if anything changed in a relaxation step. If not - you can break early.
 * To find a negative cycle: perform one more relaxation step. If anything changes - a negative cycle exists.
 */
set<int> ford_bellman(vector<pair<pll, LL>> &edges, vll &d, vi &p, int start, LL n)
{
	d[start] = 0;
	set<int> cycle_vertexes;
	for (int i = 0; i < n; i++)
	{
		cycle_vertexes.clear();
		for (auto &cur_edge : edges)
		{
			auto from = cur_edge.first.first;
			auto to = cur_edge.first.second;
			auto dist = cur_edge.second;
			if (d[from] < LLONG_MAX && d[to] > d[from] + dist)
			{
				d[to] = d[from] + dist;
				p[to] = from;
				cycle_vertexes.insert(to);
			}
		}
	}
	set<int> res;
	for (auto& v : cycle_vertexes)
	{
		int cur_v = v;
		for (int i = 0; i < n; i++) cur_v = p[cur_v];
		res.insert(cur_v);
	}

	return res;
}