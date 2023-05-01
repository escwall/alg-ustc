#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<random>

using namespace std;

using S = struct S { // 用来记录聚集元素区间的结构体
    int q;
    int t;
    S(int qq, int tt) : q(qq), t(tt) {}
};


S partition(vector<int> &A, int p, int r) {
    int x = A[r];
    int q, t; // q用来记录聚集元素的左区间，t用来记录聚集元素的右区间
    q = t = p - 1;
    for(int j = p; j < r; ++j) {
        if(A[j] < x) {
            q++;
            t++;
            swap(A[q], A[j]); // 将小于基准元素的放到左边
            if(q != t) { // q != t说明有与基准元素相等的元素，需要交换使得区间右移一位
                swap(A[t], A[j]);
            }
        }
        else if(A[j] == x) { // 聚集相同元素
            t++;
            swap(A[t], A[j]);
        }
    }
    swap(A[t+1], A[r]); // 将基准元素放置到对应位置
    t++;
    q++;
    return S(q, t);
}

void quickSort(vector<int> &A, int p, int r) { //fix pivot
    if(p >= r) return;
    S pivot = partition(A, p, r);
    quickSort(A, p, pivot.q - 1);
    quickSort(A, pivot.t + 1, r);
}

int main() {
    ifstream fin;
    fin.open("./data.txt");
    if(!fin.is_open()) {
        cout << "Can't open input file!" << endl;
    }
    else {
        int size;
        fin >> size;
        vector<int> array(size);
        int idx = 0;
        while(idx < size) {
            fin >> array[idx++];
        }
        ofstream fout;
        fout.open("./sorted.txt");
        if(!fout.is_open()) {
            cout << "Fail to create output file!" << endl;
        }
        else {
            auto begin = chrono::system_clock::now();
            quickSort(array, 0, array.size() - 1);
            auto end = chrono::system_clock::now();
            auto cost = chrono::duration_cast<chrono::milliseconds>(end - begin);
            cout << " jointQuickSort costs " << cost.count() << " ms." << endl;
            
            for(auto e : array) {
                fout << e << " ";
            }
            fout.close();
        }
        fin.close();
    }
    return 0;
}