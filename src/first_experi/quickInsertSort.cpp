#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<random>

using namespace std;


int partition(vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i + 1;
}

void insertSort(vector<int> &A, int p, int r) {
    for(int i = p + 1; i <= r; ++i) {
        int elem = A[i];
        for(int j = i - 1; j >= p; --j) {
            if(elem >= A[j]) {
                for(int k = i - 1; k > j; --k) {
                    A[k+1] = A[k];
                }
                A[j+1] = elem;
                break;
            }
            else if(j == p) {
                for(int k = i - 1; k >= p; --k) {
                    A[k+1] = A[k];
                }
                A[j] = elem;
                break;
            }
        }
    }
}

void quickSort(vector<int> &A, int p, int r, int k) { 
    if(r - p + 1 <= k) { // 当数组长度小于等于k时，不做操作直接返回等待对整体执行插入排序
        // insertSort(A, p, r);
        return;
    }
    int pivot = partition(A, p, r);
    quickSort(A, p, pivot - 1, k);
    quickSort(A, pivot + 1, r, k);
}

void quickInsertSort(vector<int> &A, int p, int r, int k) {
    quickSort(A, p, r, k); // 先使得数组“几乎有序”
    insertSort(A, p, r); // 对整体执行一次插入排序
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
        ofstream res;
        res.open("./res.txt");
        if(!fout.is_open()) {
            cout << "Fail to create output file!" << endl;
        }
        else {
            vector<int> a1(array);
            for(int k = 2; k < 1000; ++k) {
                a1 = array;
                auto begin = chrono::system_clock::now();
                quickInsertSort(a1, 0, a1.size() - 1, k);
                auto end = chrono::system_clock::now();
                auto cost = chrono::duration_cast<chrono::milliseconds>(end - begin);
                cout << " quickInsertSort with k=" << k << " costs " << cost.count() << " ms." << endl;
                res << cost.count() << endl;
                
                
            }
            for(auto e : a1) {
                fout << e << " ";
            }
            fout.close();
        }
        fin.close();
    }
    return 0;
}