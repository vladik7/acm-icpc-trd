void dijkstra(vector<vector<pll>>& g, vi& p, vll& d, int start)
{
	priority_queue<pll, vector<pll>, greater<pll>> q;
	d[start] = 0;
	q.push({ 0, start });
	while (!q.empty())
	{
		auto from = q.top().second;
		auto dist = q.top().first;
		q.pop();
		if (dist > d[from]) continue;
		for (auto& cur : g[from])
		{
			auto to = cur.second;
			auto to_dist = cur.first;
			if (d[from] + to_dist < d[to])
			{
				d[to] = d[from] + to_dist;
				p[to] = from;
				q.push({ d[to], to });
			}
		}
	}
}