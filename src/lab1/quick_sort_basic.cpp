#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<random>

using namespace std;

enum TYPE {STL, BASIC, RANDOM, MEDIAN};
TYPE test_type = RANDOM;

int partition(vector<int> &A, int p, int r) { // 对A数组进行划分，返回基准元素pivot的下标
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(A[j] <= x) { // 小于基准元素的都交换到左边
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]); // 将基准元素放置到对应位置
    return i + 1;
}

void quickSort(vector<int> &A, int p, int r) { //固定基准
    if(p >= r) return;
    int pivot = partition(A, p, r);
    quickSort(A, p, pivot - 1); //对子数组递归执行快速排序
    quickSort(A, pivot + 1, r);
}

int random(int p, int r) { // 生成下标区间内的一个随机数
    uniform_int_distribution<unsigned> u(p, r);
    default_random_engine e;
    return u(e);
}

int random_partition(vector<int> &A, int p, int r) { // 以生成的随机数下标元素为基准元素进行划分
    int i = random(p, r);
    // cout << "random number: " << i << endl;
    swap(A[i], A[r]);
    return partition(A, p, r);
}

void random_quickSort(vector<int> &A, int p, int r) { //随机基准
    if(p >= r) return;
    int pivot = random_partition(A, p, r);
    random_quickSort(A, p, pivot - 1);
    random_quickSort(A, pivot + 1, r);
}

int mid_partition(vector<int> &A, int p, int r) {
    int mid = (p + r) / 2;
    int i = A[p] > A[r] ? p : r; // fisrt pick the bigger one index as i
    int j = i == p ? r : p; // record the other index as j
    if(A[i] > A[mid]) i = A[j] > A[mid] ? j : mid; // if A[i] is the largest among them, the median must be the larger one of the remaining two elements
    swap(A[i], A[r]);
    return partition(A, p, r);
}

void mid_quickSort(vector<int> &A, int p, int r) { //三数取中
    if(p >= r) return;
    int pivot = mid_partition(A, p, r);
    mid_quickSort(A, p, pivot - 1);
    mid_quickSort(A, pivot + 1, r);
}

void merge(vector<int> &A, int p, int mid, int r) {
    int i = p, j = mid + 1;
    int k = 0;
    int temp[r - p + 1];
    while(i <= mid && j <= r) {
        if(A[i] <= A[j]) {
            temp[k++] = A[i++];
        }
        else {
            temp[k++] = A[j++];
        }
    }
    while(i <= mid) {
        temp[k++] = A[i++];
    }
    while (j <= r)
    {
        temp[k++] = A[j++];
    }
    for(i = 0; i < k; ++i) {
        A[p++] = temp[i];
    }
    
}

void mergeSort(vector<int> &A, int p, int r) {
    if(p >= r) return;
    int mid = (p + r) / 2;
    mergeSort(A, p, mid);
    mergeSort(A, mid + 1, r);
    merge(A, p, mid, r);
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
        vector<int> v2(array);
        auto begin = chrono::system_clock::now();
        mergeSort(v2, 0, v2.size() - 1);
        auto end = chrono::system_clock::now();
        auto cost = chrono::duration_cast<chrono::milliseconds>(end - begin);
        cout << "mergeSort costs " << cost.count() << " ms." << endl;
        ofstream fout;
        fout.open("./sorted.txt");
        if(!fout.is_open()) {
            cout << "Fail to create output file!" << endl;
        }
        else {
            string type_info;
            auto begin = chrono::system_clock::now();
            switch (test_type)
            {
            case STL:
                sort(array.begin(), array.end());
                type_info = "STL";
                break;
            case BASIC:
                quickSort(array, 0, array.size() - 1);
                type_info = "BASIC";
                break;
            case RANDOM:
                random_quickSort(array, 0, array.size() - 1);
                type_info = "RANDOMIZED";
                break;
            case MEDIAN:
                mid_quickSort(array, 0, array.size() - 1);
                type_info = "MEDIAN";
                break;
            
            default:
                break;
            } 
            auto end = chrono::system_clock::now();
            auto cost = chrono::duration_cast<chrono::milliseconds>(end - begin);
            cout << type_info << " quickSort costs " << cost.count() << " ms." << endl;
            for(auto e : array) {
                fout << e << " ";
            }
            fout.close();
        }
        fin.close();
    }
    return 0;
}