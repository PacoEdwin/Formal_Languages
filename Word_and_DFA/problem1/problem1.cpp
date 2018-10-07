#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
struct letters
{
	struct data
	{
		int pos;
	};
	data *link;
	string letter;
};
vector<letters::data*> v;
vector<int> accept;
vector<vector<letters*>> graph;
string s;
int ans = 0;
letters::data *dfs(int ind, letters::data *u)
{
	for (int i = 0; i < graph[u->pos].size(); i++)
	{
		for (int j = 0; j < graph[u->pos][i]->letter.size(); j++)
			if (graph[u->pos][i]->letter[j] == s[ind])
				return graph[u->pos][i]->link;
	}
	return NULL;
}
int main()
{
	ifstream fin("problem1.in");
	ofstream fout("problem1.out");
	int n, m, k;
	cin >> s >> n >> m >> k;
	v.resize(n);
	for (int i = 0; i < k; i++)
	{
		int pos;
		cin >> pos;
		accept.push_back(pos);
	}
	graph.resize(n);
	for (int i = 0; i < n; i++)
	{
		letters::data *u = new letters::data;
		v[i] = u;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		char letter;
		cin >> letter;
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		letters *m = new letters;
		m->link = v[b - 1];
		graph[a - 1].push_back(m);
		graph[a - 1].back()->letter += letter;
	}
	letters::data *u = NULL;
	for (int i = 0; i < s.size(); i++)
	{
		if (i == 0)
			u = dfs(i, v[0]);
		else
			if (u == NULL)
			{
				cout << "Rejects";
				system("pause");
				return 0;
			}
			else
				u = dfs(i, u);
	}
	if (u == NULL)
	{
		cout << "Rejects";
		system("pause");
		return 0;
	}
	for (int i = 0; i < accept.size(); i++)
		if (u->pos + 1 == accept[i])
		{
			cout << "Accepts";
			system("pause");
			return 0;
		}
	cout << "Rejects";
	system("pause");
	return 0;
}