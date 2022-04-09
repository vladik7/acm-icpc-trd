class SuffFSM
{
private:
	vector<SuffFSMState> st;
	vector<SuffFSMState> sorted_st;
	vector<LL> dp;
	int last_state;

	void extend(char c)
	{
		int cur_state = st.size();
		st.push_back(SuffFSMState(cur_state, st[last_state].len + 1, -1, 1, st[last_state].len));
		int p;
		for (p = last_state; p != -1 && !st[p].next.count(c); p = st[p].link)
			st[p].next[c] = cur_state;
		if (p == -1) st[cur_state].link = 0;
		else
		{
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len) st[cur_state].link = q;
			else
			{
				int clone_state = st.size();
				st.push_back(SuffFSMState(clone_state, st[p].len + 1, st[q].link, 0, 0));
				st[clone_state].next = st[q].next;
				st[clone_state].first_pos = st[q].first_pos;
				for (; p != -1 && st[p].next[c] == q; p = st[p].link)
					st[p].next[c] = clone_state;
				st[q].link = st[cur_state].link = clone_state;
			}
		}
		last_state = cur_state;
	}

	void build(string& s)
	{
		for (int i = 0; i < s.length(); i++) extend(s[i]);
	}

	void calc_cnts()
	{
		sorted_st = st;
		sort(all(sorted_st), [](SuffFSMState& st1, SuffFSMState& st2) { return st1.len > st2.len; });
		vi id_map(st.size());

		for (int i = 0; i < sorted_st.size(); i++)
		{
			id_map[sorted_st[i].id] = i;
		}


		for (auto &cur_state : sorted_st)
		{
			if (cur_state.link != -1)
			{
				st[cur_state.link].cnt += cur_state.cnt;
				sorted_st[id_map[cur_state.link]].cnt = st[cur_state.link].cnt;
			}
		}
	}


	LL fsm_dfs(int v)
	{
		if (dp[v] != -1) return dp[v];
		LL sum = 0;
		for (auto& to : st[v].next)
		{
			sum += fsm_dfs(to.second);
		}
		dp[v] = sum + 1;
		return dp[v];
	}


public:
	SuffFSM() : last_state(0) { st.push_back(SuffFSMState()); }
	SuffFSM(string &s) : last_state(0) {
		st.push_back(SuffFSMState()); 
		build(s);
		calc_cnts();
	}	
	
	bool check_occurrence(string& t)
	{
		int cur_state = 0;
		for (int i = 0; i < t.length(); i++)
		{
			if (st[cur_state].next.count(t[i]) == 0) return false;
			cur_state = st[cur_state].next[t[i]];
		}
		return true;
	}

	LL calc_occurrence(string& t)
	{
		int cur_state = 0;
		for (int i = 0; i < t.length(); i++)
		{
			if (st[cur_state].next.count(t[i]) == 0) return 0;
			cur_state = st[cur_state].next[t[i]];
		}
		return st[cur_state].cnt;
	}

	int get_pos(string& t)
	{
		int cur_state = 0;
		for (int i = 0; i < t.length(); i++)
		{
			if (st[cur_state].next.count(t[i]) == 0) return -1;
			cur_state = st[cur_state].next[t[i]];
		}
		return st[cur_state].first_pos - t.length() + 1;
	}

	LL distinct_substrs_cnt()
	{
		dp.clear();
		dp.resize(st.size(), -1);
		fsm_dfs(0);
		return dp[0] - 1;
	}

	string get_kth_substr(LL k)
	{
		distinct_substrs_cnt();
		string res = "";
		int cur_state = 0;
		while (k)
		{
			for (auto& cur : st[cur_state].next)
			{
				if (k <= dp[cur.second])
				{
					res.push_back(cur.first);
					cur_state = cur.second;
					k--;
					break;
				}
				else k -= dp[cur.second];
			}
		}
		return res;
	}
};