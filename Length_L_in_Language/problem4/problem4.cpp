#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
int main() 
{
	int n, m,k,l;
	ifstream fin("problem4.in");
	ofstream fout("problem4.out");
	cin >>n>>m>>k>>l;
	vector<vector<int>> a(n,vector<int>(n)); //Исходная матрица
	vector<vector<int>> b(n,vector<int>(n)); //Вспомогательная матрица
	vector<vector<int>> c(n,vector<int>(n)); //Матрица в степени n
	vector<vector<int>> ans(n,vector<int>(n));//Результирующая матрица
	vector<int> lol(k);
	for (int i = 0; i < k; i++)
	{
		int f;
		cin >> f;
		lol[i] = f - 1;
	}
	for (int j = 0; j < m; j++)	
	{
		int f, r;
		cin >> f >> r;
		string s;
		fin >> s;
		a[f - 1][r - 1]++;
		c[f - 1][r - 1] = b[f - 1][r - 1] = ans[f - 1][r - 1] = a[f - 1][r - 1];
	}
	for (int it = 1; it < l; it++){
		//Возводим матрицу в след. степень
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				c[i][j] = 0;
				for (int k = 0; k < n; k++){
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				ans[i][j] += c[i][j]; //Добавляем к ответу
				b[i][j] = c[i][j]; //Заменяем вспомогательную матрицу
			}
		}
	}
	//Добавляем единичную матрицу
	for (int i = 0; i < n; i++){
		ans[i][i]++;
	}
	int answer = 0;
	for (int i = 0; i < lol.size(); i++)
		answer += ans[0][lol[i]];
	cout << answer << endl;
	system("pause");
	return 0;
}