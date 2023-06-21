#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

using schedule = struct schedule { //调度方案数据结构
    int cost; //耗时代价
    vector<int> record; //任务分配情况
    schedule(int c, vector<int> r) : cost(c), record(r) {}
};

vector<int> machines; //记录每个机器的完成时间
vector<int> schedules;

vector<schedule> records;

int best = INT_MAX; //用来记录最优调度下的耗时

void backtrack(const vector<int>& tasks, int idx, int k) { //核心算法函数
    if(idx == tasks.size()) { //完成任务分配
        if(best > *max_element(machines.begin(), machines.end())) { 
            best = *max_element(machines.begin(), machines.end()); 
            schedule sche(best, schedules);
            records.emplace_back(sche);
        }
        return;
    }
    for(int i = 0; i < k; ++i) {
        if(i > 0 && machines[i] == machines[i-1]) continue; //剪枝操作1：如果第i个机器当前耗时与i-1个机器耗时相同，则可以直接跳过
        machines[i] += tasks[idx]; //分配该任务
        schedules[idx] = i;
        if(machines[i] < best) { //剪枝操作2：如果当前分配方案耗时高于记录的最小耗时，则跳过该情况
            backtrack(tasks, idx + 1, k); //分配下一个任务
        }
        machines[i] -= tasks[idx]; //复原
        schedules[idx] = -1;
    }
}

int main() {
    string test1, test2, test3;
    test1 = "./test1.txt", test2 = "./test2.txt", test3 = "./test3.txt";
    ifstream fin;
    fin.open(test1);
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