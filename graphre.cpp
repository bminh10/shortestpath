#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <ctime>
using namespace std;

struct graph {
	int n;
	//ma tran ke
	int** matrix;
	//danh sach ke
	int** list;
	//cach luu tru do thi
	int type;
	//do thi co hoac khong co trong so
	int ts;
	//cach tao do thi
	int chose;
	//kich thuoc danh sach ke tung dinh
	int* sz;
	//ma tran de dem canh va kiem tra canh da ton tai trong do thi hay chua
	int** check;
	//mang dung de xoa dinh
	bool* canUseV;
	//nhan dan dung de kiem tra lien thong 
	int* label;
	//mang dung de danh dau dinh da tham
	int* visited;
	//mang dung de xuat duong di tu dinh s -> g
	int* parent;
	//ten file
	string namefile;

};

//khoi tao do thi
void init(graph& m) {
	m.matrix = nullptr;
	m.list = nullptr;
	m.sz = nullptr;
	m.check = nullptr;
	m.canUseV = nullptr;
	m.label = nullptr;
	m.visited = nullptr;
	m.parent = nullptr;
}

//them 1 phan tu vao mang
void push(int*&a , int*&sz , int x, int v) {
	if (a == nullptr) {
		sz[v] = 1;
		a = new int[sz[v]];
		a[0] = x;
		return;
	}
	int* newarr = new int[sz[v]+1];
	for (int i = 0; i < sz[v]; i++) {
		newarr[i] = a[i];
	}
	newarr[sz[v]] = x;
	delete[]a;
	a = newarr;
	sz[v]++;

}

//xuat ma tran ke
void output1(graph m) {
	cout << "=========MA TRAN KE HIEN TAI===========\n";
	for (int i = 0; i < m.n; i++) {
		if (m.canUseV[i] == true) {
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.n; j++) {
				if (m.canUseV[j] == false)continue;
				cout << m.matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
}
//xuat danh sach ke
void output2(graph m) {
	cout << "=========DANH SACH KE HIEN TAI===========\n";
	for (int i = 0; i < m.n; i++) {
		if (m.canUseV[i] == true) {
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.sz[i]; j++) {
				if (m.list[i] != nullptr) {
					int dinh = m.list[i][j];
					if (m.canUseV[dinh] == false)continue;
					cout << m.list[i][j] + 1 << "\t";
				}
			}
			cout << endl;
		}	
	}
}

//tao do thi
void createGraph(graph& m) {
	switch (m.chose)
	{
	case 1: {
		ifstream fin;
		cout << "Nhap ten file: ";
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
		else if (m.type == 0) {
			m.list = new int* [m.n];
			m.sz = new int[m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
				m.list[i] = nullptr;
			}
			
			for (int i = 0; i < m.n; i++) {
				for (int j = 0; j < m.n; j++) {
					int x;
					fin >> x;
					if (x > 0) {
						push(m.list[i],m.sz,j,i);
					}
				}
			}
		}
		fin.close();
		break;
	}
	case 2: {
		cout << "Nhap so dinh: ";
		cin >> m.n;
		if (m.type == 1) {
			m.matrix = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.matrix[i] = new int[m.n];
			}
			for(int i = 0 ; i < m.n ; i++){
				for (int j = 0; j < m.n; j++) {
					m.matrix[i][j] = 0;
				}
			}
		}
		else if (m.type == 0) {
			m.sz = new int[m.n];
			m.list = new int* [m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
				m.list[i] = nullptr;
			}
			
		}
		break;
	}
	case 3: {
		cout << "Nhap so dinh: ";
		cin >> m.n;
		srand(time(NULL));
		if (m.type == 1) {
			m.matrix = new int*[m.n];
			for (int i = 0; i < m.n; i++) {
				m.matrix[i] = new int[m.n];
			}
			for (int i = 0; i < m.n; i++) {
				for (int j = 0; j < m.n; j++) {
					if (i == j) {
						m.matrix[i][j] = 0;
						continue;
					}
					if (m.ts == 0) {
						m.matrix[i][j] = (rand() % 2);
						m.matrix[j][i] = m.matrix[i][j];
					}
					else if (m.ts == 1) {
						m.matrix[i][j] = (rand() % 50)+1;
						m.matrix[j][i] = m.matrix[i][j];
					}
					

				}
			}
		}
		else if (m.type == 0) {
			m.sz = new int[m.n];
			m.list = new int*[m.n];
			for (int i = 0; i < m.n; i++) {
				m.sz[i] = 0;
				m.list[i] = nullptr;
			}
		}
		break;
	}

	default:
		cout << "Chuc nang khong co trong chuong trinh!\n";
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
	m.canUseV = new bool[m.n];
	m.parent = new int[m.n];
	m.visited = new int[m.n];
	m.label = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.label[i] = 0;
		m.visited[i] = 0;
		m.parent[i] = 0;
		m.canUseV[i] = true;
	}
	
	//neu tao do thi tu dong 
	if (m.chose == 3) {
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				if (m.matrix[i][j] > 0) {
					m.check[i][j] = 1;
				}
			}
		}
	}
	

}

//void delOldData(graph& m) {
//	for (int i = 0; i < m.n; i++) {
//		delete[]m.check[i];
//	}
//	delete[]m.check;
//	delete[]m.canUseV;
//	delete[]m.label;
//	delete[]m.visited;
//	delete[]m.parent;
//	delete[]m.sz;
//	m.check = nullptr; m.canUseV = nullptr; m.visited = nullptr; m.parent = nullptr; m.sz = nullptr; m.label = nullptr;
//}

//void push(int*& a, int n, int x) {
//	if (a == nullptr) {
//		n = 1;
//		a = new int[n];
//		a[0] = x;
//		return;
//	}
//	int* newarr = new int[n + 1];
//	for (int i = 0; i < n; i++) {
//		newarr[i] = a[i];
//	}
//	newarr[n] = x;
//	delete[]a;
//	a = newarr;
//	n++;
//}
//void push(bool*& a, int n) {
//	if (a == nullptr) {
//		n = 1;
//		a = new bool[n];
//		a[0] = true;
//		return;
//	}
//	bool* newarr = new bool[n + 1];
//	for (int i = 0; i < n; i++) {
//		newarr[i] = a[i];
//	}
//	newarr[n] = true;
//	delete[]a;
//	a = newarr;
//	n++;
//} 



//them 1 dinh vao ma tran ke/ danh sach ke
void addVertex(graph& m) {
	cout << "Nhap so dinh can them vao do thi: ";
	int numV;
	cin >> numV;
	if (numV < 1) {
		return;
	}
	int** newarr = new int* [m.n + numV];
	switch (m.type)
	{
	case 1: {
		for (int i = 0; i < m.n + numV; i++) {
			newarr[i] = new int[m.n + numV];
		}

		for (int i = 0; i < m.n + numV; i++) {
			for (int j = 0; j < m.n + numV; j++) {
				newarr[i][j] = 0;
			}
		}


		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				newarr[i][j] = m.matrix[i][j];
			}
		}
		for (int i = 0; i < m.n; i++) {
			delete[]m.matrix[i];
		}
		delete[]m.matrix;
		m.matrix = newarr;


		break;
	}
	case 0: {
		for (int i = 0; i < m.n+numV; i++) {
			newarr[i] = nullptr;
		}
		for (int i = 0; i < m.n; i++) {
			for(int j = 0 ; j < m.sz[i] ; j++){
				push(newarr[i], m.sz, m.list[i][j], i);
			}
		}
		for (int i = 0; i < m.n; i++) {
			delete[] m.list[i];
		}
		delete[]m.list;
		m.list = newarr;
		break;
	}
	default:
		break;
	}
	m.n += numV;
	int oldsz = m.n - numV;
	int** newmatrix = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		newmatrix[i] = new int[m.n];
	}
	for (int i = 0; i <m.n; i++) {
		for (int j = 0; j <m.n; j++) {
			newmatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < oldsz; i++) {
		for (int j = 0; j < oldsz; j++) {
			newmatrix[i][j] = m.check[i][j];
		}
	}
	for (int i = 0; i < oldsz; i++) {
		delete[]m.check[i];
	}
	delete[]m.check;
	m.check = newmatrix;
	
	
	bool* newarr2 = new bool[oldsz + numV];
	int* newarr3 = new int[oldsz + numV];
	int* newarr4 = new int[oldsz + numV];
	int* newarr5 = new int[oldsz + numV];
	if (m.type == 0) {
		int* newarr1 = new int[oldsz + numV];
		for (int i = 0; i < oldsz + numV; i++) {
			newarr1[i] = 0;
		}
		for (int i = 0; i < oldsz; i++) {
			newarr1[i] = m.sz[i];
		}
		delete[]m.sz;
		m.sz = newarr1;
	}
	

	for (int i = 0; i < oldsz + numV; i++) {
		newarr2[i] = true;
	}
	
	for (int i = 0; i < oldsz; i++) {
		newarr2[i] = m.canUseV[i];
	}
	//sua lai m.sz vi ko dung ds ke
	delete[]m.canUseV;
	m.canUseV = newarr2;
	
	for (int i = 0; i < oldsz + numV; i++) {
		newarr3[i] = 0;
	}
	for (int i = 0; i < oldsz; i++) {
		newarr3[i] = m.label[i];
	}
	delete[]m.label;
	m.label = newarr3;

	for (int i = 0; i < oldsz + numV; i++) {
		newarr4[i] = 0;
	}
	for (int i = 0; i < oldsz; i++) {
		newarr4[i] = m.parent[i];
	}
	delete[]m.parent;
	m.parent = newarr4;
	for (int i = 0; i < oldsz + numV; i++) {
		newarr5[i] = 0;
	}
	for (int i = 0; i < oldsz; i++) {
		newarr5[i] = m.visited[i];
	}
	delete[]m.visited;
	m.visited = newarr5;

}

//xoa 1 dinh trong ma tran ke/ danh sach ke
void delVertex(graph& m) {
	bool flag = false;
	for (int i = 0; i < m.n; i++) {
		if (m.canUseV[i] == false) {
			flag = true;
			break;
		}
	}
	if (flag == true) {
		cout << "! luu y khong duoc xoa cac dinh sau day vi da xoa truoc do: ";
		for (int i = 0; i < m.n; i++) {
			if (m.canUseV[i] == false) {
				cout << i + 1 << " ";
			}
		}
	}
	cout << endl;
	cout << "Nhap dinh can xoa (pham vi tu 1 -> " << m.n << "): ";
	
	int v;
	cin >> v;
	if (v < 1)return;
	v--;
	if (m.canUseV[v] == true && (v < m.n && v >= 0)) {
		m.canUseV[v] = false;
	}
	else {
		cout << "Khong the xoa dinh nay vi chua co trong do thi !\n";
	}
	
}

//them canh vao ma tran ke/ danh sach ke
void addEdge(graph& m) {
	cout << "Nhap dinh a noi dinh b (vd: 1 2 ~ dinh 1 noi dinh 2) (pham vi: tu dinh 1 -> "<< m.n << "): ";
	int a, b;
	cin >> a >> b;
	if (a == b && m.ts==1) {
		cout << "Khong nhap trong so cho 2 dinh trung nhau !\n";
		return;
	}
	if ((a > m.n || b > m.n) || (a<1 || b < 1)) {
		cout << "Vuot pham vi dinh trong do thi ! \n";
		return;
	}
	a--;
	b--;
	if (m.check[a][b] > 0 || m.check[b][a] > 0) {
		cout << "Canh nay da ton tai khong them lai duoc !\n";
		return;
	}
	if (m.canUseV[a] == false && m.canUseV[b] == false) {
		cout << "Dinh " << a+1 << " va " << " dinh " << b+1 << " da bi xoa nen khong them canh nay vao do thi duoc !\n";
		return;
	}
	if (m.canUseV[a] == false) {
		cout << "Dinh " << a+1 << " da bi xoa khoi do thi nen khong dung duoc dinh nay !\n";
		return;
	}
	if (m.canUseV[b] == false) {
		cout << "Dinh " << b+1 << " da bi xoa khoi do thi nen khong dung duoc dinh nay !\n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		if (m.ts == 0) {
			m.matrix[a][b] = 1;
			m.matrix[b][a] = 1;
		}
		else if (m.ts == 1) {
			cout << "Nhap trong so cho canh " << a+1 << "->" << b+1 << ": ";
			cin >> m.matrix[a][b];
			m.matrix[b][a] = m.matrix[a][b];
		}

		break;
	}
	case 0: {
		push(m.list[a], m.sz, b, a);
		push(m.list[b], m.sz, a, b);

		break;
	}
	default:
		break;
	}

}

//ham dung de ho tro cho viec xoa canh trong danh sach ke
void pop(graph&m, int v1 ,int v2) {
	if (m.sz[v2] == 1) {
		m.sz[v2] = 0;
		m.list[v2] = nullptr;
		return;
	}
	int* newarr = new int[m.sz[v2] - 1];
	int sz = 0;
	for (int i = 0; i < m.sz[v2]; i++) {
		int dinh = m.list[v2][i];
		if (dinh == v1) {
			continue;
		}
		newarr[sz] = dinh;
		sz++;
	}
	delete[] m.list[v2];
	m.list[v2] = newarr;
	m.sz[v2]--;
}

//xoa canh trong ma tran ke/ danh sach ke
void delEdge(graph& m) {
	cout << "Nhap canh can xoa (vd: 1 2 ~ xoa canh 1 2): ";
	int a, b;
	cin >> a >> b;
	if ((a > m.n || b > m.n) || (a < 1 || b < 1)) {
		cout << "Vuot pham vi dinh trong do thi ! \n";
		return;
	}
	a--; b--;
	if (a < b) {
		if (m.check[a][b] == 0) {
			cout << "khong the xoa canh nay vi chua co trong do thi ! \n";
			return;
		}
	}
	if (a > b) {
		if (m.check[b][a] == 0) {
			cout << "khong the xoa canh nay vi chua co trong do thi ! \n";
			return;
		}
	}
	
	if (m.canUseV[a] == false && m.canUseV[b] == false) {
		cout << "Dinh " << a << " va " << " dinh " << b << " da bi xoa truoc do!\n";
		return;
	}
	if (m.canUseV[a] == false) {
		cout << "Dinh " << a << " da bi xoa truoc do!\n";
		return;
	}
	if (m.canUseV[b] == false) {
		cout << "Dinh " << b << " da bi xoa truoc do!\n";
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
		pop(m, a, b);
		pop(m, b, a);
		break;
	}
	default:
		break;
	}
	

}

// tinh giai thua
int calGiaiThua(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n == 3) {
		return 2;
	}
	n--;
	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}

//kiem tra do thi lien thong hop le 
int isGraph(graph m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}
	int res = 0;
	for (int i = 0; i < m.n; i++) {
		if (m.canUseV[i] == false)continue;
		if (m.type == 1) {
			for (int j = 0; j < m.n; j++) {
				if (m.matrix[i][j] > 0 && m.check[j][i] == 0 && m.canUseV[j] == true) {
					res++;
					m.check[i][j] = 1;
				}
			}
		}
		else if (m.type == 0) {
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.check[dinh][i] == 0 && m.canUseV[dinh] == true) {
					res++;
					m.check[i][dinh] = 1;
				}
			}
		}
	}
	if (res <= calGiaiThua(m.n)) {
		return res;
	}
	return -1;
}


//cach 1: do thi lien thong neu label chi bang 1, gia su label = 2 nghia la co 2 do thi con => khong lien thong
//ham tim thanh phan lien thong
void isLienThong(graph&m,int start,int label) {
	//dung dfs hoac bfs de duyet cac dinh
	queue<int>q;
	q.push(start);
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		if (m.canUseV[r] == false)continue;
		m.label[r] = label;
		m.visited[r] = 1;
		if (m.type == 1) {
			for (int i = 0; i < m.n; i++) {
				if (m.matrix[r][i] > 0 && m.label[i] == 0 && m.visited[i]==0 && m.canUseV[i] == true) {
					q.push(i);
					m.visited[i] = -1;
				}
			}
		}
		else if (m.type == 0) {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if ( m.label[dinh] == 0 && m.visited[dinh] == 0 && m.canUseV[dinh] == true) {
					q.push(dinh);
					m.visited[dinh] = -1;
				}
			}
		}
	}
}

//ham kiem tra lien thong
void checkLT(graph& m) {
	for (int i = 0; i < m.n; i++) {
		m.label[i] = 0;
		m.visited[i] = 0;
	}
	//label la so do thi con
	int label = 0;
	for (int i = 0; i < m.n; i++) {
		if (m.label[i] == 0) {
			//tim tat ca do thi con
			label++;
			isLienThong(m, i, label);
		}
	}
	if (label == 1) {
		cout << "Do thi lien thong !\n";
	}
	else {
		cout << "Do thi khong lien thong !\n";
	}

}


//cach 2: so sanh so dinh duyet duoc trong bfs/dfs voi tap hop dinh ban dau, neu bang nhau => do thi lien thong. Nguoc lai => khong lien thong
int isLienThong2(graph&m, int start) {
	queue<int>q;
	q.push(start);
	int res = 0;
	
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		if (m.canUseV[r] == false)continue;
		m.visited[r] = 1;
		res++;
		if (m.type == 1) {
			for (int i = 0; i < m.n; i++) {
				if (m.matrix[r][i] > 0&& m.visited[i] == 0 && m.canUseV[i] == true) {
					q.push(i);
					m.visited[i] = -1;
				}
			}
		}
		else if (m.type == 0) {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (m.visited[dinh] == 0 && m.canUseV[dinh] == true) {
					q.push(dinh);
					m.visited[dinh] = -1;
				}
			}
		}

	}
	return res;

}
void checkLT2(graph&m) {
	int start;
	for (int i = 0; i < m.n; i++) {
		if (m.canUseV[i] == true) {
			start = i;
			break;
		}
	}
	int res = isLienThong2(m, start);
	if (res == m.n) {
		cout << "Do thi lien thong \n";
	}
	else {
		cout << "Do thi khong lien thong \n";
	}
}


void bfs(graph&m,int start , int goal) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
		m.parent[i] =0;
	}
	queue<int>q;
	q.push(start);
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		if (m.canUseV[r] == false)continue;
		m.visited[r] = 1;
		if (r != goal ) {
			cout << r + 1 << "->";
		}
		if (r == goal) {
			cout << goal + 1 << endl;
			return;
		}
		else {
			if (m.type == 1) {
				for (int i = 0; i < m.n; i++) {
					if (m.visited[i] == 0 && m.matrix[r][i] > 0 && m.canUseV[i] == true) {
						q.push(i);
						m.visited[i] = -1;
						m.parent[i] = r;
					}
				}
			}
			else if (m.type == 0) {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canUseV[dinh] == true) {
						q.push(dinh);
						m.visited[dinh] = -1;
						m.parent[dinh] = r;
					}
				}
			}
		}

	}

}
void dfs(graph& m, int start, int goal) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	stack<int>s;
	s.push(start);
	while (!s.empty()) {
		int r = s.top();
		if (m.canUseV[r] == false) {
			s.pop();
			continue;
		}
		if (r != goal && m.visited[r] == 0) {
			cout << r + 1 << "->";
		}
		m.visited[r] = 1;
		if (r == goal) {
			cout << goal + 1 << endl;
			return;
		}
		else {
			bool flag = false;
			if (m.type == 1) {
				for (int i = 0; i < m.n; i++) {
					if (m.visited[i] == 0 && m.matrix[r][i] > 0 && m.canUseV[i] == true) {
						s.push(i);
						m.parent[i] = r;
						flag = true;
						break;
					}
				}
			}
			else if (m.type == 0) {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canUseV[dinh] == true) {
						s.push(dinh);
						m.parent[dinh] = r;
						flag = true;
						break;
					}
				}
			}
			if (flag == false) {
				s.pop();
			}
		}

	}
}
void display(graph m, int start , int goal) {
	stack<int>s;
	int idx = m.parent[goal];
	while (idx != start) {
		s.push(idx);
		idx = m.parent[idx];
	}
	s.push(start);
	while (!s.empty()) {
		cout << s.top() + 1 << "->";
		s.pop();
	}
	cout << goal + 1 << endl;
}

void del(graph& m) {
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
	delete[]m.matrix;
	delete[]m.list;
	delete[]m.check;
	delete[]m.canUseV;
	delete[]m.label;
	delete[]m.visited;
	delete[]m.parent;
	delete[]m.sz;
	m.matrix = nullptr; m.list = nullptr; m.check = nullptr; m.canUseV = nullptr; m.visited = nullptr; m.parent = nullptr; m.sz = nullptr; m.label = nullptr;
	bool res = m.matrix == nullptr && m.list == nullptr && m.check == nullptr && m.canUseV == nullptr && m.visited == nullptr && m.parent == nullptr && m.sz == nullptr && m.label==nullptr ? true : false;
	if (res == true) {
		cout << "Giai phong thanh cong !\n";
	}
}




int main() {
	graph m;
	int chon;
	int c;
	bool canUse = true;
	
	do
	{
		init(m);
		cout << "=========MENU========\n";
		cout << "1.Tao do thi bang file\n";
		cout << "2.Tao do thi do user nhap\n";
		cout << "3.Tao do thi tu dong\n";
		cout << "=====================\n";
		cout << "Chon cach tao do thi(1-3): ";
		cin >> m.chose;
		cout << "Dung ma tran ke (bam 1)/ dung danh sach ke (bam 0): ";
		cin >> m.type;
		if (m.chose != 1 && m.type != 0) {
			cout << "Do thi co trong so (bam 1)/ khong trong so (bam 0): ";
			cin >> m.ts;
		}
		
		createGraph(m);

		if (m.type == 1) {
			output1(m);
		}
		else if (m.type == 0) {
			output2(m);
		}

		int choice4;
		cout << "Ban muon them/xoa canh hoac dinh khong ? (Yes: bam(1)/ No: bam(0)): ";
		cin >> choice4;
		if (choice4 == 1) {
			int cont;
			do
			{
				cout << "Them dinh/canh (bam 1)/ xoa dinh/canh(bam 0): ";
				int chon1;
				cin >> chon1;

				switch (chon1)
				{
					int chose;
				case 1: {
					cout << "Them dinh (bam 1)/ Them canh (bam 0): ";
					cin >> chose;
					if (chose == 1) {
						addVertex(m);
					}
					else if (chose == 0) {
						addEdge(m);

					}
					break;
				}
				case 0: {
					cout << "Xoa dinh (bam 1)/ Xoa canh (bam 0): ";
					cin >> chose;
					if (chose == 1) {
						delVertex(m);
					}
					else if (chose == 0) {
						delEdge(m);
					}
					break;
				}
				default:
					cout << "Chuc nang khong ton tai !\n ";
					break;
				}

				if (m.type == 1) {
					output1(m);
				}
				else if (m.type == 0) {
					output2(m);
				}
				int flag = isGraph(m);
				if (flag != -1) {
					cout << "Do thi hop le !\n";
					cout << "So canh cua do thi hien tai: " << flag << " canh \n";
					canUse = true;
				}
				else {
					cout << "Do thi khong hop le !, ban can tao lai do thi\n";
					canUse = false;
				}

				cout << "Tiep tuc thao tac(bam 1)/ ket thuc(bam 0): ";
				cin >> cont;
			} while (cont == 1);
		}
		

		if (canUse == true) {
			checkLT2(m);
			cout << "Ban muon duyet do thi khong ? (Yes: bam 1 / No: bam 0): ";
			int choice;
			cin >> choice;
			if (choice == 1) {
				int d = 0;
				do
				{
					cout << "BFS (bam 1)/ DFS (bam 0): ";
					int choice2;
					cin >> choice2;

					int s, g;
					bool flag3 = false;
					for (int i = 0; i < m.n; i++) {
						if (m.canUseV[i] == false) {
							flag3 = true;
							break;
						}
					}
					if (flag3== true) {
						cout << "! luu y khong duoc nhap cac dinh sau day vi da xoa truoc do: ";
						for (int i = 0; i < m.n; i++) {
							if (m.canUseV[i] == false) {
								cout << i + 1 << " ";
							}
						}
					}
					cout << endl;
					
					cout << "Nhap dinh bat dau (pham vi tu 1 -> " << m.n << "): ";
					cin >> s;
					cout << "Nhap dinh ket thuc (pham vi tu 1 -> " << m.n << "): ";
					cin >> g;
					s--;
					g--;
					bool flag = true;
					if (m.canUseV[s] == false || m.canUseV[g] == false) {
						cout << "Khong the duyet \n";
						flag = false;
					}
					if (flag == true) {
						if (choice2 == 1) {
							bfs(m, s, g);
						}
						else if (choice2 == 0) {
							dfs(m, s, g);
						}
					}

					cout << "Duong di tu " << s + 1 << "->" << g + 1 << ": ";
					display(m, s, g);
					cout << "Tiep tuc duyet (bam 1)/ ket thuc (bam 0): ";
					cin >> d;
				} while (d==1);
				
			}

		}


		cout << "Tiep tuc tao do thi (bam 1)/ ket thuc (bam 0): ";
		cin >> c;
	} while (c == 1);


	del(m);
	return 0;
}