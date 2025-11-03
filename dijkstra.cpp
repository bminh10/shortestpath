#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Edge {
	int u, v, w;
};

struct Node {
	int u, w;
};


void push(pair<int, int>* &a, int &n,pair<int, int>x) {
	if (n==0) {
		n = 1;
		a = new pair<int,int>[n];
		a[0] = x;
		return;
	}
	pair<int, int>* newarr = new pair<int, int>[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	}
	newarr[n] = x;
	delete[]a;
	a = newarr;
	n++;
}

void init(Edge*&a , int&n , int&m,pair<int,int>**&e,int*&sz,int  *&d,int*&visited) {
	ifstream fin;
	fin.open("shortestpath.txt");
	fin >> n >> m;
	a = new Edge[m];
	for (int i = 0; i < m; i++) {
		fin >> a[i].u >> a[i].v >> a[i].w;
	}
	sz = new int[n+1];
	for (int i = 0; i <= n; i++) {
		sz[i] = 0;
	}
	d = new int[n + 1];
	for (int i = 0; i <= n; i++) {
		d[i] = 1e7;
	}
	visited = new int[n + 1];
	for (int i = 0; i <= n; i++) {
		visited[i] = 0;
	}
	

	e = new pair<int,int>*[n+1];
	for (int i = 0; i < m; i++) {
		pair<int, int>xv;
		pair<int, int>xu;
		int u = a[i].u;
		int v = a[i].v;
		int w = a[i].w;
		xv.first = v;
		xv.second = w;
		xu.first = u;
		xu.second = w;
		int szu = sz[u];
		int szv = sz[v];
		push(e[u], szu, xv);
		push(e[v],szv, xu);
		sz[u] = szu;
		sz[v] = szv;
	}

	fin.close();
}

int findmin(int* d, int n,int*visited) {
	int min = d[0];
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		if (min > d[i] && visited[i] == 0) {
			min = d[i];
			idx = i;
		}
	}
	return idx;
}


void dijkstra(pair<int,int>**e,int n,int*&d, int *&visited,int *sz,int s , int g) {
	d[s] = 0;
	for (int u = 1; u <= n; u++) {
		int min = findmin(d, n,visited);
		if (visited[min] == 0) {
			visited[min] = 1;
			int size = sz[min];
			for (int x = 0; x < size; x++) {
				int v = e[min][x].first;
				int w = e[min][x].second;
				if (visited[v] == 0 && d[v] > d[min] + w) {
					d[v] = d[min] + w;
				}
			}
		}
	}
	
}


void del(Edge*& a,int n,pair<int, int>**&e,int *&sz,int*&d,int*&visited) {
	for (int i = 0; i <= n; i++) {
		delete[]e[i];
	}
	delete[]e;
	delete[]a;
	delete[]sz;
	delete[]d;
	delete[]visited;
}

int main() {
	int n, m;
	Edge* a = nullptr;
	pair<int, int>**e;
	int* sz = nullptr;
	int* d = nullptr;
	int* visited = nullptr;
	init(a, n, m,e,sz,d,visited);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < sz[i]; j++) {
			cout << e[i][j].first << "-" << e[i][j].second << "\t";
		}
		cout << endl;
	}

	int s, g;
	cout << "Nhap start: ";
	cin >> s;
	cout << "Nhap goal: ";
	cin >> g;
	dijkstra(e,n, d, visited,sz,s,g);
	/*for (int i = 0; i <= n; i++) {
		cout << d[i] << " ";
	}*/
	cout << d[6];
	del(a, n, e, sz,d,visited);
	return 0;
}