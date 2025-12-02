#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <queue>
#include <stack>
#define ll long long
using namespace std;

struct Graph {
	int n;
	int chose;
	int type;
	int ts;
	int** matrix;
	int** list;
	int* sz;
	int** check;
	bool* canuse;
	int* visited;
	int* label;
	int* parent;
	string namefile;
};

void init(Graph& m) {
	m.n = 0;
	m.sz = nullptr;
	m.check = nullptr;
	m.matrix = nullptr;
	m.list = nullptr;
	m.canuse = nullptr;
	m.visited = nullptr;
	m.label = nullptr;
}

void output1(Graph m) {
	for (int i = 0; i < m.n; i++) {
		if (m.canuse[i] == true) {
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.n; j++) {
				if (m.canuse[j] == true) {
					cout << m.matrix[i][j] << "\t";
				}
			}
			cout << endl;
		}

	}
}

void output2(Graph m) {

	for (int i = 0; i < m.n; i++) {
		if (m.canuse[i] == true) {
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.canuse[dinh] == true) {
					cout << dinh + 1 << "\t";
				}
			}
			cout << endl;
		}
	}
}

void push(int*& a, int& n, int x) {
	if (a == nullptr) {
		n = 1;
		a = new int[n];
		a[0] = x;
		return;
	}
	int* newarr = new int[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	}
	newarr[n] = x;
	delete[]a;
	a = newarr;
	n++;

}


void createGraph(Graph& m) {


	switch (m.chose)
	{
	case 1: {
		ifstream fin;
		cout << "Nhap ten file can tao do thi: ";
		cin >> m.namefile;
		fin.open(m.namefile);
		fin >> m.n;
		if (m.type == 1) {

			m.matrix = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.matrix[i] = new int[m.n];
			}
			for (int i = 0; i < m.n; i++) {
				for (int j = 0; j < m.n; j++) {
					fin >> m.matrix[i][j];
				}
			}
		}
		else {

			m.sz = new int[m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
			}

			m.list = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.list[i] = nullptr;
			}
			for (int i = 0; i < m.n; i++) {
				for (int j = 0; j < m.n; j++) {
					int x;
					fin >> x;
					if (x > 0) {
						push(m.list[i], m.sz[i], j);
					}

				}
			}
		}
		fin.close();
		break;
	}
	case 2: {
		cout << "Moi ban nhap so dinh: ";
		cin >> m.n;
		if (m.type == 1) {
			m.matrix = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.matrix[i] = new int[m.n];
			}
			for (int i = 0; i < m.n; i++) {
				for (int j = 0; j < m.n; j++) {
					m.matrix[i][j] = 0;
				}
			}
		}
		else {

			m.sz = new int[m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
			}

			m.list = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.list[i] = nullptr;
			}
		}

		break;
	}
	case 3: {

		srand(time(NULL));
		m.n = rand() % 6 + 1;
		if (m.type == 1) {

			m.matrix = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.matrix[i] = new int[m.n];
			}
			if (m.ts == 1) {
				for (int i = 0; i < m.n; i++) {
					for (int j = 0; j < m.n; j++) {
						if (i == j) {
							m.matrix[i][j] = 0; continue;
						}
						m.matrix[i][j] = rand() % 30 + 1;
						m.matrix[j][i] = m.matrix[i][j];
					}
				}
			}
			else {
				for (int i = 0; i < m.n; i++) {
					for (int j = 0; j < m.n; j++) {
						if (i == j) {
							m.matrix[i][j] = 0; continue;
						}
						m.matrix[i][j] = 1;
						m.matrix[j][i] = m.matrix[i][j];
					}
				}
			}

		}
		else {
			m.sz = new int[m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
			}

			m.list = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.list[i] = nullptr;
			}
		}
		break;
	}
	default:
		break;
	}

	m.check = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.check[i] = new int[m.n];
	}

	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}


	m.canuse = new bool[m.n];
	for (int i = 0; i < m.n; i++) {
		m.canuse[i] = true;
	}

	m.visited = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}

	m.parent = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.parent[i] = 0;
	}

}

void addVertex(Graph& m) {
	cout << "Nhap so dinh can them: ";
	int num;
	cin >> num;
	int newsize = num + m.n;
	switch (m.type)
	{

	case 1: {
		int** newarr = new int* [newsize];
		for (int i = 0; i < newsize; i++)
		{
			newarr[i] = new int[newsize];
		}
		for (int i = 0; i < newsize; i++) {
			for (int j = 0; j < newsize; j++) {
				newarr[i][j] = 0;
			}
		}

		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				newarr[i][j] = m.matrix[i][j];
			}
		}
		for (int i = 0; i < m.n; i++)
		{
			delete[]m.matrix[i];
		}
		delete[]m.matrix;
		m.matrix = newarr;

		break;
	}
	case 0: {
		int** newarr = new int* [newsize];
		for (int i = 0; i < newsize; i++)
		{
			newarr[i] = nullptr;
		}
		for (int i = 0; i < m.n; i++) {
			newarr[i] = m.list[i];
		}
		for (int i = 0; i < m.n; i++) {
			delete[] m.list[i];
		}
		delete[]m.list;
		m.list = newarr;
		int* newarr2 = new int[newsize];
		for (int i = 0; i < newsize; i++) {
			newarr2[i] = 0;
		}

		for (int i = 0; i < m.n; i++) {
			newarr2[i] = m.sz[i];
		}
		delete[]m.sz;
		m.sz = newarr2;


		break;
	}
	default:
		break;
	}
	int** newcheck = new int* [newsize];
	for (int i = 0; i < newsize; i++) {
		newcheck[i] = new int[newsize];
	}
	for (int i = 0; i < newsize; i++) {
		for (int j = 0; j < newsize; j++) {
			newcheck[i][j] = 0;
		}
	}

	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			newcheck[i][j] = m.check[i][j];
		}
	}

	for (int i = 0; i < m.n; i++) {
		delete[]m.check[i];
	}
	delete[]m.check;
	m.check = newcheck;

	bool* newcanuse = new bool[newsize];
	for (int i = 0; i < newsize; i++) {
		newcanuse[i] = true;
	}
	for (int i = 0; i < m.n; i++) {
		newcanuse[i] = m.canuse[i];
	}
	delete[]m.canuse;
	m.canuse = newcanuse;

	int* newvisited = new int[newsize];
	for (int i = 0; i < m.n; i++) {
		newvisited[i] = m.visited[i];
	}

	

	m.n = newsize;
}

void addEdge(Graph& m) {
	cout << "Moi ban nhap canh can them ( tu 1 -> " << m.n << " ): ";
	int a, b;
	cin >> a >> b;
	if (a > m.n || b > m.n) {
		cout << "Dinh vuot pham vi \n";
		return;
	}
	bool flag = true; --a; --b;
	if (a > b) {
		if (m.check[b][a] != 0) {
			cout << "Canh da co trong do thi ! \n";
			flag = false;
		}
	}
	else if(m.check[a][b]!=0 ) {
		cout << "Canh da co trong do thi ! \n";
		flag = false;
	}
	




	if (flag == true) {
		switch (m.type)
		{
		case 1: {
			if (m.ts == 1) {
				int val = 0;
				cout << "Moi ban nhap trong so cho canh: ";
				cin >> val;
				m.matrix[a][b] = val;
				m.matrix[b][a] = val;
			}
			else {
				m.matrix[a][b] = 1;
				m.matrix[b][a] = 1;
			}
			break;
		}
		case 0: {
			push(m.list[a], m.sz[a], b);
			push(m.list[b], m.sz[b], a);
			break;
		}
		default:
			break;
		}


	}

}



int calGiaiThua(int n) {

	if (n == 1) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n == 3) {
		return 3;
	}
	n--;
	int res = 0;
	for (int i = 1; i <= n; i++) {
		res += i;
	}
	return res;
}

//khong dem nhung canh da bi xoa
int isGraph(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}

	int res = 0;
	for (int i = 0; i < m.n; i++) {
		if (m.canuse[i] == true) {
			if (m.type == 1) {
				for (int j = 0; j < m.n; j++) {
					if (m.canuse[j] == true && m.matrix[i][j] != 0 && m.check[j][i] == 0) {
						res++;
						m.check[i][j] = 1;
					}
				}
			}
			else {
				for (int j = 0; j < m.sz[i]; j++) {
					int dinh = m.list[i][j];
					if (m.canuse[dinh] == true && m.check[dinh][i] == 0) {
						res++;
						m.check[i][dinh] = 1;
					}

				}
			}
		}
	}

	int flag = calGiaiThua(m.n);
	if (res <= flag) {
		return res;
	}
	return -1;
}

//khong xoa nhung dinh da xoa r
void delVertex(Graph& m) {
	int v;
	cout << "Nhap dinh can xoa: ";
	cin >> v;
	if (v > m.n || v < 0) {
		cout << "Dinh can xoa khong ton tai !\n"; return;
	}

	v--;
	if (m.canuse[v] == false) {
		cout << "Dinh nay da bi xoa !\n";
		return;
	}
	m.canuse[v] = false;


}

void pop(int*& a, int& n, int x) {
	if (n == 1) {
		n = 0;
		a = nullptr;
		return;
	}
	int* newarr = new int[n - 1];
	int idx = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == x)continue;
		int dinh = a[i];
		newarr[idx] = dinh;
		idx++;
	}
	delete[]a;
	a = newarr;
	n--;
}



void delEdge(Graph& m) {
	int a, b;
	cout << "Nhap canh can xoa: ";
	cin >> a >> b;
	if (a > m.n || b > m.n) {
		cout << "Dinh vuot pham vi: ";
		return;
	}
	a--; b--;
	if (m.canuse[a] == false || m.canuse[b] == false) {
		cout << "Khong the xoa canh nay \n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		m.matrix[a][b] = 0;
		m.matrix[b][a] = 0;
		break;
	}
	case 0: {
		pop(m.list[a], m.sz[a], b);
		pop(m.list[b], m.sz[b], a);
		break;
	}
	default:
		break;
	}


}


void checkLT(Graph& m,int start,int &total) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	queue<int>q;
	q.push(start);
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		m.visited[r] = 1;
		total++;
		if (m.type == 1) {
			for (int i = 0; i < m.n; i++) {
				if (m.matrix[r][i] > 0 && m.visited[i] == 0 && m.canuse[i] == true) {
					q.push(i);
					m.visited[i] = -1;
				}
			}
		}
		else {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if ( m.visited[dinh] == 0 && m.canuse[dinh] == true) {
					q.push(dinh);
					m.visited[dinh] = -1;
				}
			}
		}
	}

}



bool isLienThong(Graph& m) {
	int res = 0;
	checkLT(m, 0, res);
	if (res == m.n) {
		return true;
	}
	return false;

}


void bfs(Graph& m,int start , int goal) {
	int res = 0;
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	queue<pair<int, int>>q;
	q.push({ start,0 });
	while (!q.empty()) {
		int r = q.front().first;
		if (m.ts == 1) {
			res += q.front().second;
		}
		q.pop();
		if (m.canuse[r] == false)continue;
		
		if (r == goal) {
			cout << goal + 1 << endl;
			return;
		}
		cout << r + 1 << " -> ";
		m.visited[r] = 1;
		
			if (m.type == 1) {
				for (int i = 0; i < m.n; i++) {
					if (m.matrix[r][i] > 0 && m.visited[i] == 0 && m.canuse[i] == true) {
						if (m.ts == 1) {
							q.push({ i,m.matrix[r][i] });
						}
						else {
							q.push({ i,0 });
						}
						m.visited[i] = -1;
						m.parent[i] = r;
					}
				}
			}
			else {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canuse[dinh] == true) {
						
						q.push({ dinh,0 });
						m.visited[dinh] = -1;
						m.parent[dinh] = r;
					}
				}
			}
	}

	if (m.ts == 1) {
		cout << "Tong trong so duyet: " << res << endl;
	}
	
}

void dfs(Graph& m, int start, int goal) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	stack<int>q;
	q.push(start);
	while (!q.empty()) {
		int r = q.top();
		if (m.canuse[r] == false) {
			q.pop();
			continue;
		}
		if (r == goal) {
			cout << goal + 1 << endl;
			return;
		}
		if (m.visited[r] == 0) {
			cout << r + 1 << " -> ";
		}
		m.visited[r] = 1;
		bool flag = false;
			if (m.type == 1) {
				
				for (int i = 0; i < m.n; i++) {
					if (m.matrix[r][i] > 0 && m.visited[i] == 0 && m.canuse[i] == true) {
						q.push(i);
						m.parent[i] = r;
						flag = true;
						break;
					}
				}
				
			}
			else {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canuse[dinh] == true) {
						q.push(dinh);
						m.parent[dinh] = r;
						flag = true;
						break;
					}
				}
			}
			if (flag == false) {
				q.pop();
			}
		
	}
}

void display(Graph& m,int start , int goal) {
	int* res = nullptr;
	int size = 0;
	int idx = m.parent[goal];
	while (idx !=start) {
		push(res, size, idx);
		idx = m.parent[idx];
	}
	push(res, size, start);
	for (int i = size - 1; i >= 0; i--) {
		cout << res[i]+1 << " -> ";
	}
	cout << goal + 1 << endl;
}

void del(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		if (m.matrix != nullptr) {
			delete[]m.matrix[i];
		}
		if (m.list != nullptr) {
			delete[]m.list[i];
		}
		if (m.check != nullptr) {
			delete[]m.check[i];
		}
	}

	delete[]m.sz;
	delete[]m.check;
	delete[] m.matrix;
	delete[]m.list;
	delete[]m.canuse;
	delete[]m.visited;
	delete[]m.label;


	m.sz = nullptr;
	m.check = nullptr;
	m.matrix = nullptr;
	m.list = nullptr;
	m.canuse = nullptr;
	m.visited = nullptr;
	m.label = nullptr;
	bool res = m.sz == nullptr && m.check == nullptr && m.matrix == nullptr && m.list == nullptr && m.canuse == nullptr && m.visited == nullptr && m.label == nullptr ? true : false;

	if (res) {
		cout << "Giai phong thanh cong \n";
	}

}


int main() {
	Graph m;
	init(m);

	cout << "===========MENU=========\n";
	cout << "1.Tao do thi bang file\n";
	cout << "2. Tao do thi do user nhap\n";
	cout << "3. Automatic Graph\n";
	cout << "========================\n";
	cout << "Chon cach tao do thi (1-3): ";
	cin >> m.chose;
	cout << "Ban dung ma tran ke (bam 1)/ danh sach ke(bam 0): ";
	cin >> m.type;
	bool canUse = true;

	int chose = 0;
	if (m.type == 1 && m.chose != 1) {
		cout << "Ban muon ma tran ke co trong so khong ? (Yes(1)/No(0)): ";
		cin >> m.ts;
	}
	createGraph(m);
	if (m.type == 1) {
		output1(m);
	}
	else {
		output2(m);
	}

	cout << "Ban muon them dinh khong ? (Yes: (bam 1)/ No: (bam 0)): ";
	cin >> chose;
	if (chose == 1) {
		int cont = 0;
		do
		{
			addVertex(m);
			if (m.type == 1) {
				output1(m);
			}
			else {
				output2(m);
			}

			cout << "Tiep tuc(bam 1)/ ket thuc(bam 0): ";
			cin >> cont;
		} while (cont == 1);
	}



	cout << "Ban muon them canh khong ? (Yes: (bam 1)/ No: (bam 0)): ";
	cin >> chose;

	if (chose == 1) {
		int cont2 = 0;
		do
		{
			addEdge(m);
			if (m.type == 1) {
				output1(m);
			}
			else {
				output2(m);
			}
			int res1 = isGraph(m);
			if (res1 != -1) {
				cout << "So canh do thi hien tai: " << res1 << endl;
				cout << "Do thi hop le \n";
			}
			else {
				cout << "Do thi khong hop le ! \n";
				canUse == false;
			}
			cout << "Tiep tuc(bam 1)/ ket thuc(bam 0): ";
			cin >> cont2;
		} while (cont2 == 1);
	}

	cout << "Ban muon xoa dinh khong ? (Yes: (bam 1)/ No: (bam 0)): ";
	cin >> chose;

	if (chose == 1) {
		int cont3 = 0;
		do
		{
			delVertex(m);
			if (m.type == 1) {
				output1(m);
			}
			else {
				output2(m);
			}
			int res1 = isGraph(m);
			if (res1 != -1) {
				cout << "So canh do thi hien tai: " << res1 << endl;
				cout << "Do thi hop le \n";
			}
			else {
				cout << "Do thi khong hop le ! \n";
				canUse == false;
			}
			cout << "Tiep tuc(bam 1)/ ket thuc(bam 0): ";
			cin >> cont3;
		} while (cont3 == 1);
	}

	cout << "Ban muon xoa canh khong ? (Yes: (bam 1)/ No: (bam 0)): ";
	cin >> chose;

	if (chose == 1) {
		int cont4 = 0;
		do
		{
			delEdge(m);
			if (m.type == 1) {
				output1(m);
			}
			else {
				output2(m);
			}
			int res1 = isGraph(m);
			if (res1 != -1) {
				cout << "So canh do thi hien tai: " << res1 << endl;
				cout << "Do thi hop le \n";
			}
			else {
				cout << "Do thi khong hop le ! \n";
				canUse == false;
			}
			cout << "Tiep tuc(bam 1)/ ket thuc(bam 0): ";
			cin >> cont4;
		} while (cont4 == 1);
	}

	if (canUse == true) {
		bool res1 = isLienThong(m);
		if (res1 == true) {
			cout << "Do thi lien thong ! \n";
		}
		else {
			cout << "Do thi khong lien thong \n";
		}
		int t = 0;
		do
		{
			int s, g;
			cout << "Dinh bat dau: ";
			cin >> s;
			cout << "Dinh ket thuc: ";
			cin >> g;
			s--; g--;
			cout << "Thu tu duyet BFS: ";
			bfs(m, s, g);
			cout << "TThu tu duyet DFS: ";
			dfs(m, s, g);


			cout << "Duong di tu start -> goal : ";
			display(m, s, g);
			cout << "Tiep tuc(bam 1)/ ket thuc(bam 0): ";
			cin >> t;
		} while (t==1);
		
	}


	del(m);
	return 0;
}