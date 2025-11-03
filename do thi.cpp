#include <iostream>
#include <queue>
#include <stack>
using namespace std;


void nhap(int **& a, int &n,int *&visited,int *&parent) {
    cin >> n;
    a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
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


}

void bfs(int ** a, int n, int *& visited, int*&parent) {
    queue<int>q;
    q.push(2);
    while (!q.empty()) {
        int r = q.front();
        q.pop();
        visited[r] = 1;
        if (r == 5) {
            break;
        }
        else {
            for (int i = 0; i < n; i++) {
                if (a[r][i] > 0 && visited[i] == 0) {
                    q.push(i);
                    visited[i] = -1;
                    parent[i] = r;
                }
            }
        }
        
    }

    stack<int>s;
    int idx = parent[5];
    while (idx != 2) {
        s.push(idx + 1);
        idx = parent[idx];
    }
    s.push(2 + 1);
    while (!s.empty()) {
        cout << s.top() << "->";
        s.pop();
    }
    cout << 5+1 << endl;

}




void delMatrix(int ** &a,int n,int *&visited,int*&parent) {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[]a;
    delete[]visited;
    delete[]parent;
    a = nullptr; visited = nullptr; parent = nullptr;
    
    if (a == nullptr && visited == nullptr && parent == nullptr) {
        cout << "Giai phong thanh cong\n";
    }
}




int main()
{ 
    int n;
    int** a, *visited,*parent;
    nhap(a, n,visited,parent);

    bfs(a,n,visited,parent);

    delMatrix(a, n,visited,parent);
    return 0;
}
