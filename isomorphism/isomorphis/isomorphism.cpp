#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
struct letter
{
	struct data
	{
		string color = "white";
		int pos;
		int terminal=0;
	};
	string l;
	data* link = new data;
};
vector<vector<letter*>> graph1;
vector<vector<letter*>> graph2;
vector<letter::data*> v1;
vector<letter::data*> v2;
bool devil1(letter::data* u)
{
	bool check=true;
	for (int i = 0; i < graph1[u->pos].size(); i++)
	{
		if (graph1[u->pos][i]->link->pos == u->pos&&u->terminal==0)
			check &= true;
		else
			check = false;
	}
	return check;
}
bool devil2(letter::data* u)
{
	bool check = true;
	for (int i = 0; i < graph2[u->pos].size(); i++)
	{
		if (graph2[u->pos][i]->link->pos == u->pos && u->terminal == 0)
			check &= true;
		else
			check = false;
	}
	return check;
}
bool dfs(letter::data* u1, letter::data* u2)
{
	u1->color = "gray";
	u2->color = "gray";
	if (u1->terminal != u2->terminal)
		return false;
	bool result = true;
	for (int i = 0; i < graph1[u1->pos].size(); i++)
	{
		letter::data* t1 = graph1[u1->pos][i]->link;
		letter::data* t2 = new letter::data;
		bool any = false;
		for (int j = 0; j < graph2[u2->pos].size(); j++)
			if (graph2[u2->pos][j]->l == graph1[u1->pos][i]->l)
				t2 = graph2[u2->pos][j]->link,any=true;
		if (!any)
			t2 = u2;
		if (!any && !devil1(t1) && !devil2(u2))
			return false;
		if ((devil1(t1) && !devil2(t2)) || (!devil1(t1) && devil2(t2)))
			return false;
		if (t1->color == "white"&&t2->color == "white")
			result = result & dfs(t1, t2);
	}
	return result;
}
int main()
{
	ifstream fin("isomorphism.in");
	ofstream fout("isomorphism.out");
	int n, m, k,n1,m1,k1;
	fin >> n >> m >> k;
	n1 = n;
	m1 = m;
	k1 = k;
	graph1.resize(n);
	v1.resize(n);
	for (int i = 0; i < n; i++)
	{
		letter::data* u = new letter::data;
		u->pos = i;
		v1[i] = u;
	}
	for (int i = 0; i < k; i++)
	{
		int term;
		fin >> term;
		v1[term - 1]->terminal = 1;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b;
		string s;
		fin >> a >> b >> s;
		letter* u = new letter;
		u->l = s;
		u->link = v1[b - 1];
		graph1[a - 1].push_back(u);
	}

	fin >> n >> m >> k;
	graph2.resize(n);
	v2.resize(n);
	for (int i = 0; i < n; i++)
	{
		letter::data* u = new letter::data;
		u->pos = i;
		v2[i] = u;
	}
	for (int i = 0; i < k; i++)
	{
		int term;
		fin >> term;
		v2[term - 1]->terminal = 1;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b;
		string s;
		fin >> a >> b >> s;
		letter* u = new letter;
		u->l = s;
		u->link = v2[b - 1];
		graph2[a - 1].push_back(u);
	}
	if (n1 != n || m1 != m || k1 != k)
	{
		fout << "NO";
		return 0;
	}
	if (dfs(v1[0], v2[0]))
		fout << "YES";
	else
		fout << "NO";
	return 0;
}