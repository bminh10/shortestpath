#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#define ll long long
using namespace std;

const int M = 65;

struct name {
	string s;
	int len;
};

struct SinhVien {
	ll mssv;
	name hoten;
	double dtb, hp;
};

struct List {
	SinhVien* list;
	int n;
};

void push(SinhVien*& a, int& n, SinhVien x) {
	if (a == nullptr) {
		n = 1;
		a = new SinhVien[n];
		a[0] = x;
		return;
	}
	SinhVien* newarr = new SinhVien[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	}
	newarr[n] = x;
	delete[]a;
	a = newarr;
	n++;
}

ll getVal(SinhVien x, int chon1) {
	switch (chon1)
	{
	case 1: {
		return x.mssv;
		break;
	}
	case 2: {
		return x.hoten.len;
		break;
	}
	case 3: {
		return x.dtb * 10;
		break;
	}
	case 4: {
		return x.hp * 100;
		break;
	}

	default:
		break;
	}

}

ll getIdx(SinhVien x) {
	ll res = 0;
	for (int i = x.hoten.s.length() - 1; i >= 0; i--) {
		if (x.hoten.s[i - 1] == ' ') {
			res = x.hoten.s[i] - '0';
			break;
		}
	}
	return res;
}
void output(SinhVien** a , int*sz) {
	cout << "DANH SACH HIEN TAI \n";
	for (int i = 0; i < M; i++) {
		if (a[i] == nullptr)continue;
		for (int j = 0; j < sz[i]; j++) {
			cout << a[i][j].mssv << " " << a[i][j].hoten.s << " " << a[i][j].dtb << " " << a[i][j].hp <<endl;
		}
		
	}
}

int calLen(SinhVien x) {
	int n = x.hoten.s.length();
	int res = 0;
	for (int i = n - 1; i >= 0; i--) {

		if (x.hoten.s[i - 1] == ' ') {
			res++;
			break;
		}
		res++;

	}
	return res;
}
void readData(SinhVien**&a ,int *&sz) {
	ifstream fin;
	fin.open("SinhVien.txt");
	while (!fin.eof())
	{
		SinhVien x;
		fin >> x.mssv;
		fin.ignore();
		getline(fin, x.hoten.s, '#');
		x.hoten.len = 0;
		fin >> x.dtb;
		fin.ignore();
		fin >> x.hp;
		ll idx = getIdx(x)%M;
		push(a[idx], sz[idx], x);
	}
	fin.close();

	

}



ll cmpMSSV(SinhVien a, SinhVien b) {
	return a.mssv - b.mssv;
}

ll cmpTen(SinhVien a, SinhVien b) {
	return a.hoten.len - b.hoten.len;
}
ll cmpDTB(SinhVien a, SinhVien b) {
	return a.dtb - b.dtb > 0 ? 1 : a.dtb - b.dtb < 0 ? -1 : 0;
}
ll cmpHP(SinhVien a, SinhVien b) {
	return a.hp - b.hp > 0 ? 1 : a.hp - b.hp < 0 ? -1 : 0;
}

void shellSort(SinhVien*& a, int n, ll func(SinhVien a, SinhVien b),int chon2) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			SinhVien tmp = a[i];
			int j;
			switch (chon2)
			{
			case 1: {
				for (j = i; j >= gap && func(a[j-gap],tmp) > 0; j -= gap) {
					a[j] = a[j - gap];
				}
				break;

			}
			case 2: {
				for (j = i; j >= gap && func(a[j - gap], tmp) < 0; j -= gap) {
					a[j] = a[j - gap];
				}
				break;
			}
			default:
				break;
			}
			a[j] = tmp;
		}
		
	}

}

ll findMax(SinhVien* a, int n , int chon1) {
	ll max = INT_MIN;
	for (int i = 0; i < n; i++) {
		int val = getVal(a[i], chon1);
		if (max < val) {
			max = val;
		}
	}
	return max;
}

void countingSort(SinhVien*& a, int n,int chon1,int chon2, int exp = 0) {
	ll max = 0;
	if (exp != 0) {
		max = 9;
	}
	else {
		max = findMax(a, n, chon1);
	}
	int* cnt = new int[max + 1];
	for (int i = 0; i <= max; i++) {
		cnt[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int val = exp!= 0 ? (getVal(a[i], chon1)/exp) % 10 : getVal(a[i], chon1);
		cnt[val]++;
	}

	for (int i = 1; i <= max; i++) {
		cnt[i] += cnt[i - 1];
	}
	SinhVien* output = new SinhVien[n];
	for (int i = n-1; i >=0 ; i--) {
		int val = exp != 0 ? (getVal(a[i], chon1) / exp) % 10 : getVal(a[i], chon1);
		output[cnt[val] - 1] = a[i];
		cnt[val]--;
	}
	
	if (chon2 == 1 || exp !=0) {
		for (int i = 0; i < n; i++) {
			a[i] = output[i];
		}
	}
	else if (exp==0) {
		int idx = 0;
		for (int i = n - 1; i >= 0; i--) {
			a[idx] = output[i];
			idx++;
		}
	}
	delete[]output;
	delete[]cnt;
}

void radixSort(SinhVien*& a, int n, int chon1, int chon2) {
	ll max = findMax(a, n, chon1);
	for (int exp = 1; max / exp != 0; exp *= 10) {
		countingSort(a, n, chon1, chon2,exp);
	}
	if (chon2 == 2) {
		for(int i = 0 ; i < n/2 ; i++){
			swap(a[i], a[(n - 1) - i]);
		}
	}
	
}

void bucketSort(SinhVien*& a, int n, int chon1, int chon2) {
	SinhVien**bucket = new SinhVien*[n];
	int* sz = new int[n];
	for (int i = 0; i < n; i++) {
		bucket[i] = nullptr;
		sz[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		int idx = 0;
		push(bucket[idx], sz[idx], a[i]);
	}

	for (int i = 0; i < n; i++) {
		if (bucket[i] == nullptr)continue;
		radixSort(bucket[i], sz[i], chon1, chon2);
	}

	
	int idx = 0;
	/*if (chon2 == 1) {*/
		for (int i = 0; i < n; i++) {
			if (bucket[i] == nullptr)continue;
			for (int j = 0; j < sz[i]; j++) {
				a[idx] = bucket[i][j];
				idx++;
			}
		}
	/*}
	else  {
		for (int i = n - 1; i >= 0; i--) {
			if (bucket[i] == nullptr)continue;
			for (int j = sz[i]-1; j >= 0 ; j--) {
				a[idx] = bucket[i][j];
				idx++;
			}
		}
	}*/

}


void output2(SinhVien * list, int n) {
	cout << "DANH SACH HIEN TAI\n";
	for (int i = 0; i < n; i++) {
		cout << list[i].mssv << " " << list[i].hoten.s << " " << list[i].dtb << " " << list[i].hp << endl;
	}
}

void process(SinhVien ** &a , int *&sz, int chon , int chon1, int chon2, List& l) {
	for (int i = 0; i < M; i++) {
		if (a[i] == nullptr)continue;
		for (int j = 0; j < sz[i]; j++) {
			
			a[i][j].hoten.len = calLen(a[i][j]);
		}
	}

	if (chon1 != 2) {

		for (int i = 0; i < M; i++) {
			if (a[i] == nullptr)continue;
			for (int j = 0; j < sz[i]; j++) {
				push(l.list, l.n, a[i][j]);
			}
		}

		switch (chon)
		{
		case 1: {
			switch (chon1)
			{
			case 1: {
				shellSort(l.list, l.n, cmpMSSV, chon2);
				break;
			}
			case 3: {
				shellSort(l.list, l.n, cmpDTB, chon2);
				break;
			case 4: {
				shellSort(l.list, l.n, cmpHP, chon2);
				break;
			}
			}
			default:
				break;
			}
			break;
		}
		case 2: {
			countingSort(l.list, l.n, chon1, chon2);
			break;
		}
		case 3: {
			radixSort(l.list, l.n, chon1, chon2);
			break;
		}
		case 4: {
			bucketSort(l.list, l.n, chon1, chon2);
			break;
		}
		default:
			break;
		}

	}
	else {
		for (int i = 0; i < M; i++) {
			if (a[i] == nullptr)continue;
			switch (chon)
			{
			case 1: {
				shellSort(a[i], sz[i], cmpTen, chon2);
				
				break;
			}
			case 2: {
				countingSort(a[i], sz[i], chon1, chon2);
				break;
			}
			case 3: {
				radixSort(a[i], sz[i], chon1, chon2);
				break;
			}
			case 4: {
				bucketSort(a[i], sz[i], chon1, chon2);
				break;
			}
			default:
				break;
			}
		}
	}


	
	if (chon1 != 2) {
		output2(l.list, l.n);
	}
	else {
		output(a, sz);

	}

}




int main() {
	SinhVien** a;
	List l;
	int* sz;
	
	
	int c;
	do
	{
		a = nullptr;
		l.list = nullptr;
		l.n = 0;
		a = new SinhVien*[M];
		sz = new int[M];
		for (int i = 0; i < M; i++) {
			a[i] = nullptr;
			sz[i] = 0;
		}
		readData(a, sz);
		output(a, sz);
		cout << "MENU\n";
		cout << "1. Shell sort \n";
		cout << "2. counting sort \n";
		cout << "3. radix sort \n";
		cout << "4. bucket sort \n";
		int chon;
		cout << "Chon chuc nang: ";
		cin >> chon;
		cout << "MENU\n";
		cout << "1. MSSV \n";
		cout << "2. Ten \n";
		cout << "3. DTB \n";
		cout << "4. HP\n";
		int chon1;
		cout << "Ban muon sort theo: ";
		cin >> chon1;
		cout << "MENU\n";
		cout << "1. Tang dan \n";
		cout << "2. Giam dan\n";
		int chon2;
		cout << "Chon thu tu sap xep: ";
		cin >> chon2;
		process(a, sz, chon, chon1, chon2,l);

		cout << "Tiep tuc ( bam 1 ) / ket thuc( bam 0 ): ";
		cin >> c;
	} while (c==1);

	

	for (int i = 0; i < M; i++) {
		delete[]a[i];
	}
	delete[]l.list;
	delete[]a;
	delete[]sz;
	return 0;
}