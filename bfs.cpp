#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;


void init(int ** &a,int &m,int *&parent, int *&visited, int*&thutu, int &s , int &g) {
	ifstream fin;
	fin.open("bfstest.txt");
	int n;
	fin >> n;
	a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> a[i][j];
		}
	}

	
	fin >> s >> g;
	m = n;
	parent = new int[n];
	visited = new int[n];
	thutu = new int[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}

	fin.close();
}


void bfs(int **a,int n,int * &parent, int * &visited,int * &thutu, int s , int g) {
	queue<int>q;
	q.push(s);
	int j = 0;
	while (!q.empty()) {
		int r = q.front();
		thutu[j++] = r+1;
		q.pop();
		visited[r] = 1;
		if (r == g) {
			break;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (visited[i] == 0 && a[r][i] > 0) {
					q.push(i);
					visited[i] = -1;
					parent[i] = r;
				}
			}
		}

	}

	stack<int>st;
	int idx = parent[g];
	while (idx != s) {
		st.push(idx + 1);
		idx = parent[idx];
	}
	st.push(s + 1);
	while (!st.empty()) {
		cout << st.top() << "->";
		st.pop();
	}
	cout << g + 1 << endl;
	

}



void del(int**& a, int n ,int*& parent, int*& visited,int *&thutu) {
	for (int i = 0; i < n; i++) {
		delete[]a[i];
	}
	delete[]a;
	delete[]parent;
	delete[]visited;
	delete[]thutu;
	a = nullptr, parent = nullptr , visited = nullptr, thutu = nullptr;
	if (a == nullptr && parent == nullptr && visited == nullptr && thutu == nullptr) {
		cout << "giai phong thanh cong \n";
	}
}


int main() {
	int** a = nullptr;
	int* parent = nullptr;
	int* visited = nullptr;
	int* thutu = nullptr;
	int n;
	int s, g;
	init(a,n,parent,visited, thutu,s,g);
	bfs(a, n, parent, visited,thutu, s, g);

	for (int i = 0; i < n; i++) {
		cout << thutu[i] << " ";
	}
	cout << endl;


	del(a, n,parent,visited,thutu);
	return 0;
}