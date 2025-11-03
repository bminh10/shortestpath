#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
using namespace std;



void init(int**& a, int &n, int*& visited, int*& parent) {
	a = nullptr;
	visited = nullptr;
	parent = nullptr;
	ifstream fin;
	fin.open("bfstest.txt");
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

	visited = new int[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
	parent = new int[n];
	for (int i = 0; i < n; i++) {
		parent[i] = 0;
	}

	fin.close();
}


int bfs(int **a , int n,int *&visited , int *&parent , int x) {
	stack<int>q;
	q.push(0);
	while (!q.empty()) { //stack use for dfs
		int r = q.top();
		q.pop();
		visited[r] = 1;
		if (r == x) {
			return 1;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (visited[i] == 0 && a[r][i] > 0) {
					visited[i] = -1;
					q.push(i);
					parent[i] = r;
				}
			}
		}
	}
	return -1;

}

void del(int**& a, int n ,int*& visited, int*& parent) {
	for (int i = 0; i < n; i++) {
		delete[]a[i];
	}
	delete[]a;
	delete[]visited;
	delete[]parent;
	a = nullptr;
	visited = nullptr;
	parent = nullptr;
}
void push(int* &a, int& n, int x) {
	if (a == nullptr) {
		n = 1;
		a = new int[n];
		a[0] = x;
		return;
	}
	int* newarr = new int[n+1];
	for (int i = 1; i <= n; i++) {
		newarr[i] = a[i-1];
	}
	newarr[0] = x;
	delete[]a;
	a = newarr;
	n++;

}

int main() {
	int** a;
	int* visited, * parent;
	int n =0 ;
	init(a, n, visited, parent);
	int x;
	cout << "Nhap gia tri x: ";
	cin >> x;
	if (bfs(a,n,visited,parent,x) != -1) {
		cout << "Co ton tai !\n";
		cout << "Duong di tu 1 -> x: ";
		int size;
		int* res = nullptr;
		int idx = parent[x];
		while (idx != 0) {
			push(res, size,idx);
			idx = parent[idx];
		}
		push(res, size, 0);
		for (int i = 0; i < size; i++) {
			cout << res[i] << " ";
		}
		cout << x << endl;
		delete[]res;
	}
	else {
		cout << "Khong ton tai !\n";
	}

	del(a, n, visited, parent);
	return 0;
}