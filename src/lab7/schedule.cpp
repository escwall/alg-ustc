#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

using schedule = struct schedule {
    int cost;
    vector<int> record;
    schedule(int c, vector<int> r) : cost(c), record(r) {}
};

vector<int> machines;
vector<int> schedules;

vector<schedule> records;

int best = INT_MAX;

void backtrack(const vector<int>& tasks, int idx, int k) {
    if(idx == tasks.size()) {
        if(best > *max_element(machines.begin(), machines.end())) {
            best = *max_element(machines.begin(), machines.end()); 
            schedule sche(best, schedules);
            records.emplace_back(sche);
        }
        return;
    }
    for(int i = 0; i < k; ++i) {
        if(i > 0 && machines[i] == machines[i-1]) continue;
        machines[i] += tasks[idx];
        schedules[idx] = i;
        if(machines[i] < best) {
            backtrack(tasks, idx + 1, k);
        }
        machines[i] -= tasks[idx];
        schedules[idx] = -1;
    }
}

int main() {
    string test1, test2, test3;
    test1 = "./test1.txt", test2 = "./test2.txt", test3 = "./test3.txt";
    ifstream fin;
    fin.open(test3);
    int n, k;
    fin >> n >> k;
    vector<int> tasks;
    for(int i = 0; i < n; ++i) {
        int val;
        fin >> val;
        tasks.emplace_back(val);
    }
    schedules.resize(n);
    machines.resize(k, 0);
    sort(tasks.begin(), tasks.end());
    backtrack(tasks, 0, k);
    cout << "time consumed " << best << endl;
    for(int j = 0; j < k; ++j) {
        cout << "machine" << j+1 << ": ";
        for(int i = 0; i < records[records.size()-1].record.size(); ++i) {
            if(j == records[records.size()-1].record[i]) {
                cout << "task" << i+1 << " ";
            }
        }
        cout << endl;
    }
    return 0;
}