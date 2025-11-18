#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stack>
#include <queue>
using namespace std;



struct Graph {
	int** matrix;
	int** list;
	int n;
	int* sz;
	int** check;
	int* label;
	int tplt;
	int* visited;
	int* parent;
	bool* canuse;
};

//xuat ma tran ke
void output(Graph m) {
	if (m.n == 0) {
		cout << "Khong co du lieu \n";
		return;
	}
	cout << "MA TRAN KE HIEN TAI \n";

	for (int i = 0; i < m.n; i++) {
		if (m.canuse[i] == false)continue;
		cout << "Dinh " << i + 1 << ": ";
		for (int j = 0; j < m.n; j++) {
			if (m.canuse[j] == true) {
				cout << m.matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}
//xuat danh sach ke
void output1(Graph m) {
	if (m.n == 0) {
		cout << "Khong co du lieu \n";
		return;
	}
	cout << "DANH SACH KE HIEN TAI\n";
	for (int i = 0; i < m.n; i++) {
		if (m.canuse[i] == false)continue;
		cout << "Dinh " << i + 1 << ": ";
		for (int j = 0; j < m.sz[i]; j++) {
			int dinh = m.list[i][j];
			if (m.canuse[dinh] == true) {
				cout << dinh + 1 << " ";
			}
		}
		cout << endl;
	}
}

void push(int*& a, int*&sz, int x,int val) {
	if (a == nullptr) {
		sz[val] = 1;
		a = new int[sz[val]];
		a[0] = x;
		return;
	}
	int* newarr = new int[sz[val] + 1];
	for (int i = 0; i < sz[val]; i++) {
		newarr[i] = a[i];
	}
	newarr[sz[val]] = x;
	delete[]a;
	a = newarr;
	sz[val]++;
}


void init(Graph& m, int chon, int k, string s = "") {
	if (chon == 1) {
		ifstream fin;
		fin.open(s);
		fin >> m.n;
		m.matrix = new int* [m.n];
		for (int i = 0; i < m.n; i++) {
			m.matrix[i] = new int[m.n];
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++)
			{
				fin >> m.matrix[i][j];
			}
		}
		fin.close();
	}
	else if (chon == 2 && k == 1) {

		m.matrix = new int* [m.n];
		for (int i = 0; i < m.n; i++) {
			m.matrix[i] = new int[m.n];
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++)
			{
				m.matrix[i][j] = 0;
			}
		}

	}
	else if (chon == 3 && k == 1) {
		m.matrix = new int* [m.n];
		for (int i = 0; i < m.n; i++) {
			m.matrix[i] = new int[m.n];
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				m.matrix[i][j] = rand() % 2;
			}
		}
	}
	m.canuse = new bool[m.n];
	for (int i = 0; i < m.n; i++) {
		m.canuse[i] = true;
	}

	m.check = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.check[i] = new int[m.n];
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++)
		{
			m.check[i][j] = 0;
		}
	}
	m.label = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.label[i] = 0;
	}
	m.tplt = 0;
	m.visited = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	m.parent = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.parent[i] = 0;
	}

	m.sz = nullptr;
	if (chon == 2 && k == 0) {
		m.sz = new int[m.n];
		for (int i = 0; i < m.n; i++) {
			m.sz[i] = 0;
		}
		m.list = new int* [m.n];
		for (int i = 0; i < m.n; i++) {
			m.list[i] = nullptr;
		}
	}

}

long calGiaiThua(int n) {
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
	long res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}

long isGraph(Graph& m, int k)
{
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}


	long res = 0;
	if (k == 0) {
		//dem tren danh sach ke
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == false) continue;
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.canuse[dinh]==true && m.check[dinh][i] == 0 && dinh < m.n) {
					res++;
					m.check[i][dinh] = 1;
				}
			}
		}
	}
	else if (k == 1) {
		//dem tren ma tran ke
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == false) {
				continue;
			}
			for (int j = 0; j < m.n; j++) {
				if (m.canuse[j] == false) {
					continue;
				}
				if (m.matrix[i][j] == 1 && m.check[j][i] == 0) {
					res++;
					m.check[i][j] = 1;
				}
			}
		}
	}
	if (res <= calGiaiThua(m.n)) {
		return res;
	}
	else {
		return -1;
	}
}
void checkLT(Graph& m, int start, int k) {
	stack<int>s;
	s.push(start);
	while (!s.empty()) {
		int r = s.top();
		if (m.canuse[r] == false) {
			continue;
		}
		s.pop();
		m.label[r] = 1;
		if (k == 1) {
			for (int i = 0; i < m.n; i++) {
				if (m.matrix[r][i] > 0 && m.label[i] == 0 && m.canuse[i] == true) {
					s.push(i);

				}
			}
		}
		else if (k == 0) {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (m.canuse[dinh]==true && m.label[dinh] == 0) {
					s.push(dinh);
				}
			}
		}

	}
}

long isLienThong(Graph& m, int k) {
	for (int i = 0; i < m.n; i++) {
		if (m.label[i] == 0 && m.canuse[i] == true) {
			checkLT(m, i, k);
			m.tplt++;
		}
	}
	if (m.tplt == 1) {
		return 1;
	}
	return -1;

}
long bfs(Graph& m, int start, int goal, int k) {
	queue<int>q;
	q.push(start);
	while (!q.empty()) {
		int r = q.front();
		if (m.canuse[r] == false) {
			continue;
		}
		q.pop();
		m.visited[r] = 1;
		if (r != goal) {
			cout << r + 1 << "->";
		}
		if (r == goal) {
			cout << goal + 1 << endl;
			return 1;
		}
		else {
			if (k == 1) {
				for (int i = 0; i < m.n; i++) {
					if (m.visited[i] == 0 && m.matrix[r][i] > 0 && m.canuse[i] == true) {
						q.push(i);
						m.visited[i] = -1;
						m.parent[i] = r;
					}
				}
			}
			else {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canuse[dinh]==true) {
						q.push(dinh);
						m.visited[dinh] = -1;
						m.parent[dinh] = r;
					}
				}
			}

		}
	}
	return -1;
}
long dfs(Graph& m, int start, int goal, int k) {
	stack<int>s;
	s.push(start);
	while (!s.empty()) {
		int r = s.top();
		if (m.canuse[r] == false) {
			s.pop();
			continue;
		}
		if (r != goal && m.visited[r] == 0) {
			cout << r + 1 << "->";
		}
		m.visited[r] = 1;
		if (r == goal) {
			cout << goal + 1 << endl;
			return 1;
		}
		else {
			bool flag = false;
			if (k == 1) {

				for (int i = 0; i < m.n; i++) {
					if (m.visited[i] == 0 && m.matrix[r][i] > 0 && m.canuse[i] == true) {
						s.push(i);
						m.parent[i] = r;
						flag = true;
						break;
					}
				}
				if (flag == false) {
					s.pop();
				}

			}
			else {
				for (int i = 0; i < m.sz[r]; i++) {
					int dinh = m.list[r][i];
					if (m.visited[dinh] == 0 && m.canuse[dinh]==true) {
						s.push(dinh);
						m.parent[dinh] = r;
						flag = true;
						break;
					}
				}
				if (flag == false) {
					s.pop();
				}
			}

		}
	}
	return -1;
}

void display(Graph m, int start, int goal) {
	cout << "DUONG DI TU " << start + 1 << "->" << goal + 1 << ": " << endl;
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
void initArr(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		m.parent[i] = 0;
		m.visited[i] = 0;
	}

}



void del(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		if (m.matrix != nullptr) {
			if (m.matrix[i] != nullptr) {
				delete[]m.matrix[i];
			}
		}
		if (m.list != nullptr) {
			if (m.list[i] != nullptr) {
				delete[]m.list[i];
			}
		}
		if (m.check[i] != nullptr) {
			delete[]m.check[i];
		}

	}
	delete[]m.matrix;
	delete[]m.list;
	delete[]m.sz;
	delete[]m.check;
	delete[]m.label;
	delete[]m.visited;
	delete[]m.parent;
	delete[]m.canuse;
	m.canuse = nullptr;
	m.parent = nullptr;
	m.matrix = nullptr;
	m.list = nullptr;
	m.sz = nullptr;
	m.check = nullptr;
	m.tplt = 0;
	m.label = nullptr;
	m.visited = nullptr;
	bool res = m.matrix == nullptr && m.list == nullptr && m.sz == nullptr && m.check == nullptr && m.label == nullptr && m.visited == nullptr && m.parent == nullptr && m.canuse == nullptr ? true : false;
	if (res) {
		cout << "Giai phong thanh cong\n";
	}
	else {
		cout << "Giai phong that bai\n";
	}
}



void delV(Graph& m, int v,int k) {
	if (k == 1) {
		for (int i = 0; i < m.n; i++) {
			if (i == v) {
				for (int k = 0; k < m.n; k++) {
					m.matrix[i][k] = 0;
				}
				continue;
			}
			for (int j = 0; j < m.n; j++) {
				if (j == v) {
					m.matrix[i][j] = 0;
				}
			}
		}
		
	}
	//danh sach ke khong can lam gi het
	m.canuse[v] = false;
}
void initNew(Graph& m, int v) {
	int** newmatrix = new int* [m.n + v];
	for (int i = 0; i < m.n + v; i++) {
		newmatrix[i] = new int[m.n + v];
		for (int j = 0; j < m.n + v; j++) {
			newmatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			newmatrix[i][j] = m.matrix[i][j];
		}
	}

	del(m);
	m.n += v;
	m.matrix = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.matrix[i] = new int[m.n];
	}
	m.matrix = newmatrix;

	m.check = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.check[i] = new int[m.n];
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++)
		{
			m.check[i][j] = 0;
		}
	}
	m.label = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.label[i] = 0;
	}
	m.tplt = 0;
	m.visited = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	m.parent = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.parent[i] = 0;
	}
}

void pop(int*& a, int*&sz,int v,int val) {
	if (sz[val] == 1) {
		sz[val]--;
		a = nullptr;
		return;
	}
	int* newarr = new int[sz[val] - 1];
	int size = 0;
	for (int i = 0; i < sz[val]; i++) {
		int dinh = a[i];
		if (dinh == v) {
			continue;
		}
		newarr[size] = a[i];
		size++;
	}
	delete[]a;
	a = newarr;
	sz[val]--;
}

void delEdge(Graph& m,int a , int b , int k ) {
	if (k == 1) {
		m.matrix[a][b] = 0;
		m.matrix[b][a] = 0;
	}
	else if (k == 0) {
		pop(m.list[a], m.sz, b, a);
		pop(m.list[b], m.sz, a, b);
	}
}


int main() {

	int c = 1;
	Graph m;
	m.matrix = nullptr;
	m.list = nullptr;
	m.n = 0;
	m.sz = nullptr;
	bool canUse = false;
	do
	{

		int chon;
		m.matrix = nullptr;
		m.list = nullptr;
		m.n = 0;
		m.sz = nullptr;
		cout << "MENU\n";
		cout << "1.Cho nguoi dung nhap file do thi\n";
		cout << "2.Nhap tu ban phim\n";
		cout << "3.Tu dong tao do thi\n";
		cout << "========================\n";

		cout << "Moi ban chon cach khoi tao du lieu: ";
		cin >> chon;

		cout << "Ban muon tao ma tran ke(1) / danh sach ke(0)?: ";
		int k;
		cin >> k;
		switch (chon)
		{
		case 1: {

			string s;
			cout << "Nhap ten file: ";
			cin >> s;
			init(m, chon, k, s);
			if (k == 1) {
				output(m);
			}
			else if (k == 0) {
				output1(m);
			}
			else {
				output(m);
				output1(m);
			}
			long res = isGraph(m, k);
			if (res != -1) {
				cout << "Do thi hop le ! \n";
				canUse = true;
			}
			else {
				cout << "Do thi khong hop le ! \n";
				canUse = false;
			}
			break;

		}
		case 2: {
			int t;
			cout << "Nhap dinh cho do thi: ";
			cin >> m.n;
			init(m, chon, k);
			cout << "Tao do thi co trong so(1)/ khong trong so(0): ";
			cin >> t;
			int a, b;
			int stop;
			do
			{
				cout << "Nhap canh noi tu i -> j (vd: 1 2) (chi so dinh tu 1 -> " << m.n << "): ";
				cin >> a >> b;
				a--;
				b--;
				if (k == 1) {
					if (t == 1) {

					}
					else {
						if (a < m.n && b < m.n) {
							if (m.matrix[a][b] == 0) {
								m.matrix[a][b] = 1;
								m.matrix[b][a] = 1;
							}
							else {
								cout << "Canh da ton tai trong do thi\n";
							}
						}
						else {
							cout << "Dinh vuot pham vi \n";
						}

						long res = isGraph(m, k);
						if (res != -1) {
							cout << "So canh cua do thi hien tai: " << res << endl;
							cout << "Do thi hop le !\n";
							output(m);
							canUse = true;
						}
						else {
							cout << "Do thi khong hop le!\n";
							output(m);
							canUse = false;
							break;
						}
					}
				}
				else if (k == 0) {
					if (t == 1) {

					}
					else {
						if (a < m.n && b < m.n) {
							if (m.check[a][b] == 0 && m.check[b][a] == 0) {
								push(m.list[a], m.sz, b, a);
								push(m.list[b], m.sz, a, b);
							}
							else {
								cout << "Canh da ton tai trong do thi! \n";
							}
						}
						else {
							cout << "Dinh vuot ngoai pham vi !\n";
						}

						long res = isGraph(m, k);
						if (res != -1) {
							cout << "So canh cua do thi hien tai: " << res << endl;
							cout << "Do thi hop le !\n";
							output1(m);

							canUse = true;
						}
						else {
							cout << "Do thi khong hop le !\n";
							output(m);
							canUse = false;
							break;
						}
					}
				}
				else {

				}
				cout << "Tiep tuc nhap canh (1)/ket thuc(0): ";
				cin >> stop;
			} while (stop == 1);
			break;
		}
		case 3: {

			break;
		}
		default:
			cout << "Chuc nang khong ton tai \n";
			break;
		}



		//thao tac
		if (canUse == true) {
			//them dinh/ canh && xoa dinh/ canh
			int cont;
			do
			{
				int choice;
				cout << "Ban muon them dinh va canh, bam(1)/xoa dinh va canh bam (0): ";
				cin >> choice;
				if (choice == 1) {
					cout << "THEM DINH BAM (1)/ THEM CANH BAM (0): ";
					int chon1;
					cin >> chon1;
					if (chon1 == 1) {
						int v;
						cout << "Chon so dinh can them: ";
						cin >> v;
						initNew(m, v);
						if (k == 1) {
							output(m);
						}
						else if (k == 0) {
							output1(m);
						}

						long res = isGraph(m, k);
						if (res != -1) {
							cout << "So canh cua do thi hien tai: " << res << endl;
							cout << "Do thi hop le !\n";
							canUse = true;
							
							
						}
						else {
							cout << "Do thi khong hop le\n";
							canUse = false;
						}

					}
					else if (chon1 == 0) {
						int a, b;
						cout << "Pham vi dinh tu (1->" << m.n << ") !\n";
						cout << "them canh noi tu i den j(vd: 1 2): ";
						cin >> a >> b;
						a--;
						b--;
						if (k == 1) {
							if (a < m.n && b < m.n) {
								if (m.matrix[a][b] == 0) {
									m.matrix[a][b] = 1;
									m.matrix[b][a] = 1;
								}
								else {
									cout << "Canh da ton tai trong do thi\n";
								}
							}
							else {
								cout << "Dinh vuot pham vi \n";
							}

							long res = isGraph(m, k);
							if (res != -1) {
								cout << "So canh cua do thi hien tai: " << res << endl;
								cout << "Do thi hop le !\n";
								output(m);
								canUse = true;
							}
							else {
								cout << "Do thi khong hop le!\n";
								output(m);
								canUse = false;
								break;
							}
						}
						else if (k == 0) {
							if (a < m.n && b < m.n) {
								if (m.check[a][b] == 0 && m.check[b][a] == 0) {
										push(m.list[a], m.sz, b, a);
										push(m.list[b], m.sz, a, b);
								}
								else {
									cout << "Canh da ton tai trong do thi! \n";
								}
							}
							else {
								cout << "Dinh vuot ngoai pham vi !\n";
							}
							long res = isGraph(m, k);
							if (res != -1) {
								cout << "So canh cua do thi hien tai: " << res << endl;
								cout << "Do thi hop le !\n";
								output1(m);
								canUse = true;
							}
							else {
								cout << "Do thi khong hop le!\n";
								canUse = false;
								break;
							}
						}
					}
					else {
						cout << "Khong ton tai chuc nang!\n";
					}
				}
				else if (choice == 0) {
					cout << "XOA DINH BAM (1)/ XOA CANH BAM(0): ";
					int chon2;
					cin >> chon2;
					if (chon2 == 1) {
						int v;
						cout << "Ban muon xoa dinh nao? (Pham vi tu 1->" << m.n << "): ";
						cin >> v;
						v--;
						if (k == 1) {
							delV(m, v, k);
							cout << "DO THI SAU KHI XOA !\n";
							output(m);


						}
						else if (k == 0) {
							delV(m, v, k);
							cout << "DO THI SAU KHI XOA !\n";
							output1(m);
						}
						long res = isGraph(m, k);
						if (res != -1) {
							cout << "So canh cua do thi: " << res << endl;
							cout << "Do thi hop le !\n";
						}
						else {
							cout << "Do thi khong hop le!\n";
							canUse = false;
							break;
						}
					}
					else if (chon2 == 0) {
						int a, b;
						int sV, sG;
						//tim dinh bat dau
						for (int i = 0; i < m.n; i++) {
							if (m.canuse[i] == true) {
								sV = i;
								break;
							}
						}
						//tim dinh ket thuc
						for (int j = m.n - 1; j >= 0; j--) {
							if (m.canuse[j] == true) {
								sG = j;
								break;
							}
						}
						cout << "Nhap canh i noi j can xoa (vd 1 2) (pham vi dinh tu " << sV + 1 << "->" << sG + 1 << "): ";
						cin >> a >> b;
						a--; b--;
						delEdge(m, a, b, k);
						if (k == 1) {
							cout << "Da xoa canh!\n";
							output(m);
						}
						else if (k == 0) {
							cout << "Da xoa canh!\n";
							output1(m);
						}
						long res = isGraph(m, k);
						if (res != -1) {
							cout << "So canh hien tai: " << res << endl;
							cout << "Do thi hop le!\n";
						}
						else {
							cout << "Do thi khong hop le !\n";
							canUse = false;
							break;
						}
					}
					else {
						cout << "Khong ton tai chuc nang!\n";
					}
				}
				else {
					cout << "Khong ton tai chuc nang!\n";
				}

				cout << "Tiep tuc thao tac bam(1)/ket thuc bam(0): ";
				cin >> cont;
			} while (cont == 1);

			if (canUse == true) {
				//kiem tra lien thong
				string s = isLienThong(m, k) != -1 ? "Do thi lien thong !\n" : "Do thi khong lien thong !\n";
				cout << s << endl;
				int con = 0;
				cout << "BAN CO MUON DUYET DO THI KHONG, NEU CO BAM(1)/NEU KHONG BAM(0): ";
				int chon3;
				cin >> chon3;
				if (chon3 == 1) {
					do
					{
						//dfs / bfs
						cout << "Ban muon su dung BFS bam (1) / DFS bam (0): ";
						int chose;
						cin >> chose;
						int start, goal;
						int sV = 0, sG = 0;
						//tim dinh bat dau
						for (int i = 0; i < m.n; i++) {
							if (m.canuse[i] == true) {
								sV = i;
								break;
							}
						}
						//tim dinh ket thuc
						for (int i = m.n - 1; i >= 0; i--) {
							if (m.canuse[i] == true) {
								sG = i;
								break;
							}
						}
						cout << "Nhap dinh bat dau (" << sV + 1 << "->" << sG + 1 << "): ";
						cin >> start;
						cout << "Nhap dinh ket thuc (" << sV + 1 << "->" << sG + 1 << "): ";
						cin >> goal;
						start--;
						goal--;
						bool flag2 = true;
						if (start < sV || goal < sV || start > sG && goal > sG) {
							cout << "Dinh vuot ngoai pham vi !\n";
							flag2 = false;
						}
						initArr(m);
						if (flag2 == true) {
							if (chose == 1) {
								cout << "=====THU TU DUYET RONG=======\n";
								long res = bfs(m, start, goal, k);

								if (res != -1) {
									cout << "Dinh " << goal + 1 << " ton tai trong do thi !\n";
									display(m, start, goal);
								}
								else {
									cout << "Dinh " << goal + 1 << " khong ton tai trong do thi !\n";
								}
							}
							else {
								cout << "=========THU TU DUYET SAU==========\n";
								long res = dfs(m, start, goal, k);
								if (res != -1) {
									cout << "Dinh " << goal + 1 << " ton tai trong do thi !\n";
									display(m, start, goal);
								}
								else {
									cout << "Dinh " << goal + 1 << " khong ton tai trong do thi !\n";
								}
							}
						}
						cout << "Tiep tuc su dung bam(1)/ ket thuc bam(0): ";
						cin >> con;
					} while (con == 1);
				}
			}
		}

		if (canUse == false) {
			cout << "Do thi khong hop le nen khong the thao tac tren do thi, moi ban tao lai do thi !\n";
		}

		cout << "Tiep tuc tao do thi moi (1)/ ket thuc(0): ";
		cin >> c;
	} while (c == 1);

	del(m);
	return 0;
}