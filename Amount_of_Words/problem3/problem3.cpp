#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct data
{
	int pos;
	int out = 0;
	int count = 1;
	data* ancestor=NULL;
	string color = "white";
};

vector<data*> v;
vector<vector<data*>> graph;
vector<vector<data*>> reversed;
vector<string> words;
int check;
long long answer=0;
long long add = 1;

void dfs1(data* u)
{
	u->color = "gray";
	if (u->out == 1)
	{
		data* m = new data;
		m = u;
		while (u)
		{
			u->color = "yellow";
			u = u->ancestor;
		}
		u = m;
	}
	for (int i = 0; i < graph[u->pos].size(); i++)
	{
		if (graph[u->pos][i]->color == "white")
		{
			graph[u->pos][i]->ancestor = u;
			dfs1(graph[u->pos][i]);
		}
		if (graph[u->pos][i]->color == "gray")
			check = -1;
	}
	if (u->color != "yellow")
		u->color = "black";
}

void dfs2(data* u)
{
	u->out++;
	u->color = "orange";
	for (int i = 0; i < graph[u->pos].size(); i++)
	{
		if (graph[u->pos][i]->color == "yellow")
			dfs2(graph[u->pos][i]);
		if (graph[u->pos][i]->color == "orange")
			check = -1;
		if (graph[u->pos][i]->color == "red" && (graph[u->pos][i]->out + 1)>2)
			graph[u->pos][i]->count++;
		if (graph[u->pos][i]->color == "red")
			graph[u->pos][i]->out++;
	}
	u->color = "red";
}

void dfs3(data* u)
{
	u->color = "orange";
	add *= u->count;
	for (int i = 0; i < reversed[u->pos].size(); i++)
	{
		if (reversed[u->pos][i]->color == "yellow")
			dfs3(reversed[u->pos][i]);
	}
	u->color = "red";
}

int main()
{
	ifstream fin("problem3.in");
	ofstream fout("problem3.out");
	int n, m, k;
	cin >> n >> m >> k;
	v.resize(n);
	graph.resize(n);
	reversed.resize(n);
	for (int i = 0; i < n; i++)
	{
		data* u = new data;
		v[i] = u;
	}
	vector<int>terminal;
	for (int i = 0; i < k; i++)
	{
		int a;
		cin >> a;
		terminal.push_back(a - 1);
		v[a-1]->out=1;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		string k;
		cin >> k;
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		graph[a - 1].push_back(v[b - 1]);
		reversed[b - 1].push_back(v[a - 1]);
	}
	dfs1(v[0]);
	for (int i = 0; i < n; i++)
		v[i]->out = 0;
	dfs2(v[0]);
	if (check == -1)
	{
		cout << -1;
		system("pause");
		return 0;
	}
	for (int i = 0; i < n; i++)
		if (v[i]->color == "red")
			v[i]->color = "yellow";
	for (int i = 0; i < terminal.size(); i++)
	{
		dfs3(v[terminal[i]]);
		answer += add;
		add = 1;
		for (int j = 0; j< n; j++)
			if (v[j]->color == "red")
				v[j]->color = "yellow";
	}
	long long a = pow(10, 9);
	cout << answer%(a+7);
	system("pause");
	return 0;
}