#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> schedule; // 任务分配列表
vector<int> machines; // 机器完成时间列表
int min_time;         // 当前的最小完成时间

void backtrack(const vector<int>& tasks, int task_index, int num_machines) {
    if (task_index == tasks.size()) {
        // 所有任务都已经分配完成
        min_time = min(min_time, *max_element(machines.begin(), machines.end()));
        return;
    }

    for (int i = 0; i < num_machines; i++) {
        machines[i] += tasks[task_index]; // 尝试将任务分配给第i个机器
        if (machines[i] < min_time) {
            backtrack(tasks, task_index + 1, num_machines); // 递归调用
        }
        machines[i] -= tasks[task_index]; // 恢复第i个机器的完成时间
    }
}

int main() {
    int n; // 任务数量
    int k; // 机器数量

    cout << "Enter the number of tasks: ";
    cin >> n;
    cout << "Enter the number of machines: ";
    cin >> k;

    vector<int> tasks(n);

    cout << "Enter the time required for each task:\n";
    for (int i = 0; i < n; i++) {
        cin >> tasks[i];
    }

    schedule.resize(n);
    machines.resize(k, 0);
    min_time = INT_MAX;

    sort(tasks.begin(), tasks.end()); // 对任务按所需时间排序

    backtrack(tasks, 0, k); // 调用回溯算法

    cout << "Minimum completion time: " << min_time << endl;

    return 0;
}
