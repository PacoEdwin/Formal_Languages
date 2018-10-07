#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<queue>
using namespace std;
struct letters
{
	struct data
	{
		int pos;
	};
	data *link;
	char letter;
};
vector<letters::data*> v;
vector<int> accept;
vector<vector<letters*>> graph;
string s;
vector<char> alphabet;
int ans = 0;
letters::data *dfs(int ind, letters::data *u)
{
	for (int i = 0; i < graph[u->pos].size(); i++)
	{
		if (graph[u->pos][i]->letter == s[ind])
			return graph[u->pos][i]->link;
	}
	return NULL;
}
vector<letters::data*> P;
vector<vector<letters*>> Q;
vector<letters*> q;
vector<letters::data*> PP;
void getDFAbyNFA()
{
	P.push_back(v[0]);
	while (!P.empty())
	{
		PP.clear();
		for (int i = 0; i < P.size(); i++)
			PP.push_back(P[i]);
		P.clear();
		for (int k = 0; k < alphabet.size(); k++)
		{
			q.clear();
			for (int i = 0; i < PP.size(); i++)
			{
				for (int j = 0; j < graph[PP[i]->pos].size(); j++)
					if (graph[PP[i]->pos][j]->letter==alphabet[k])
						q.push_back(graph[PP[i]->pos][j]);
				int lel = 0;
				for (int j = 0; j < Q.size(); j++)
				{
					if (Q[j].size() == q.size())
					{
						int mek = 0;
						for (int l = 0; l < q.size(); l++)
							if (q[l]->letter != Q[j][l]->letter)
								mek = 1;
						if (mek == 0)
						{
							lel = 1;
							break;
						}
					}
				}
				if (lel == 0&&q.size()>0)
				{
					Q.resize(Q.size()+1);
					Q[Q.size() - 1] = q;
					for (int j = 0; j < q.size(); j++)
						P.push_back(q[j]->link);
				}
			}
		}
	}
}

int main()
{
	ifstream fin("problem1.in");
	ofstream fout("problem1.out");
	int n, m, k;
	cin>>s >>n >> m >> k;
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
		int mek = 0;
		for (int j = 0; j < alphabet.size(); j++)
			if (letter == alphabet[j])
				mek = 1;
		if (mek == 0)
			alphabet.push_back(letter);
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		letters *m = new letters;
		m->link = v[b - 1];
		graph[a - 1].push_back(m);
		graph[a - 1].back()->letter = letter;
	}
	getDFAbyNFA();
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