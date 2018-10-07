#include<iostream>
#include<vector>
#include<string>
using namespace std;
//letter struct is for every edge
struct letter
{
	//data for vertex, so when we create new edge it will refer to some vertex
	struct data
	{
		int pos;
		int terminal = 0;
	};
	string l;
	data* link = new data;
};

vector<vector<letter*>> graph;
vector<letter::data*> v;
int index = 0;

int build_graph(string re, int from, int to);

int brackets(string re, int from)
{
	return build_graph(re, from, -1);//to setted to the -1 because we haven't encountered any of the | if we do we will change to, ergo we gonna know that
}//we encountered | sing

int attach = 0;

void clini(int from, int to)
{
	letter *e= new letter;
	e->l = "";
	e->link = v[from];
	graph[to].push_back(e);
}

int build_graph(string re, int from,int to)
{
	attach = from;//то куда присоединяем граф
	for (int i = index; i < re.size(); i++)
	{
		if (re[i] == '(')// if encountered with bracket we pass the last added as "from" to the brackets function
		{
			index = i + 1;
			v.resize(v.size() + 1);
			graph.resize(v.size());
			letter::data* u = new letter::data;//creatin e edge in order to if after closing bracket there is a clini sign *, we would manage to refer to this vertex
			u->pos = v.size() - 1;
			v[u->pos] = u;
			letter *w= new letter;
			w->l = "";
			w->link = v[u->pos];
			graph[v.size() - 2].push_back(w);
			attach = brackets(re, v.size() - 1);
			i = index;
		}
		if (re[i] == '|')//mesmorizes from and the lats added vertex gonna be to
		{
			if (to == -1)
				to = v.size() - 1;//if encounter | change "to", to the last added 
			letter* w = new letter;
			w->l = "";
			w->link = v[to];//connecting last added to the to vertex
			graph[attach].push_back(w);
			continue;
		}
		if (re[i] == ')')
		{
			letter* w = new letter;
			w->l = "";
			w->link = v[to];
			graph[attach].push_back(w);
			letter *z = new letter;
			letter::data* u = new letter::data;//creating e edge
			v.resize(v.size() + 1);
			graph.resize(v.size());
			u->pos = v.size() - 1;
			v[u->pos] = u;
			z->l = "";
			z->link = v[u->pos];
			graph[to].push_back(z);//allegedly ve start from to hopefully/allegedly make sense, but then we need to change to to the last added an it is e edge
			index = i + 1;
			if (i + 1 < re.size() && re[i + 1] == '*')
			{
				index = i + 2;
				clini(from, to);
			}
			to = v.size() - 1;//вроде все работает, запилим функцию клини
			return to;// return to because we need to change attach in order to connect to the "to" from previous recursion
		}
			letter::data* u = new letter::data;
			if (i-1>0 && re[i - 1] == '|')
			{
				u->pos = v.size();
				v.resize(v.size() + 1);
				graph.resize(v.size());
				v[u->pos] = u;
				letter *w = new letter;
				w->l = re[i];
				w->link = v[u->pos];
				graph[from].push_back(w);
			}
			else
			{
				if (i + 1 < re.size())
				{
					if (re[i + 1] != '*')// if next isn't clini sign and it is not last element
					{
						graph.resize(graph.size() + 1);
						v.resize(v.size() + 1);
						u->pos = v.size() - 1;
						v[v.size() - 1] = u;
						if (v.size() > 1)
						{
							letter* w = new letter;
							w->l = re[i];
							w->link = v[v.size() - 1];
							graph[attach].push_back(w);
						}
					}
					else
					{
						letter *w = new letter;
						letter *kek = new letter;
						letter::data *z = new letter::data; // if we encounter a single letter with clini sign * we nedd to loop it, so we creating two more vertices
						graph.resize(graph.size() + 2);
						v.resize(v.size() + 2);
						u->pos = v.size() - 2;
						z->pos = v.size() - 1;
						v[u->pos] = u;
						v[z->pos] = z;
						w->l = "";
						kek->l = "";
						kek->link = v[z->pos];
						w->link = v[u->pos];
						graph[attach].push_back(w);
						letter *ch = new letter;
						ch->l = re[i];
						ch->link = v[u->pos];
						graph[v.size() - 2].push_back(ch);
						graph[v.size() - 2].push_back(kek);
						i++;
					}
				}
				else// if it is last element then there no chance that * is next char
				{
					graph.resize(graph.size() + 1);
					v.resize(v.size() + 1);
					u->pos = v.size() - 1;
					v[v.size() - 1] = u;
					if (v.size() > 1)
					{
						letter* w = new letter;
						w->l = re[i];
						w->link = v[v.size() - 1];
						graph[attach].push_back(w);
					}
				}
			}
			attach = v.size() - 1;//last added element
	}
}

int main()
{
	string re;
	cin >> re;//input: xab(xb|cl(xfk|rm)|l)
	v.resize(1);
	letter::data* u = new letter::data;
	v[0] = u;
	graph.resize(1);
	brackets(re, 0);//string  and initial from=0. as|ds|d branches go from 0 element
	v[v.size() - 1]->terminal = 1;//terminal vertex
	system("pause");
	return 0;
}