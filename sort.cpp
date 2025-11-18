#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

struct HoTen {
	string *a;
	int n;
};
void init(HoTen& s) {
	s.a = nullptr;
	s.n = 0;
}

void push(string*&a, int &n, string x) {
	if (a == nullptr) {
		n = 1;
		a = new string[n + 1];
		a[0] = x;
		return;
	}
	string *newarr = new string[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	} 
	newarr[n] = x;
	delete[] a;
	a = newarr;
	n++;

}


void readData(HoTen &s) {
	ifstream fin;
	fin.open("danhsach.txt");
	while (!fin.eof()) {
		string x;
		getline(fin, x);
		push(s.a, s.n, x);
	}

	fin.close();
}

void output(HoTen s) {
	for (int i = 0; i < s.n; i++) {
		cout << s.a[i] << endl;
	}
	
}

int getTen(string s) {
	int res = 0;

	for (int i = s.size()-1; i < s.size(); i--) {
		if (s[i-1] == ' ') {
			res = s[i] - '0';
			break;
		}
	}
	return res;
}

void countingSort(HoTen s,int exp) {
	int max = 9;
	int*count = new int[max + 1];
	for (int i = 0; i <= max; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < s.n; i++) {
		
	}


}

int getMaxTen(HoTen s) {
	int max = INT_MIN;
	for (int i = 0; i < s.n; i++) {
		int val = getTen(s.a[i]);
		if (val > max) {
			max = val;
		}
	}
	return max;
}

void radixSort(HoTen s) {
	int max = getMaxTen(s);
	for (int exp = 1; max / exp != 0; exp *= 10) {
		countingSort();
	}
}


int main() {
	HoTen s;
	init(s);
	readData(s);
	output(s);



	return 0;
}