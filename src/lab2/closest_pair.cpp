#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<random>
#include<cmath>
#include<cstdio>
#include<cfloat>

using namespace std;

using Point = struct Point
{
    int idx;
    double x;
    double y;

    Point(int _i, double _x, double _y) : idx(_i), x(_x), y(_y) {}
}; // 记录点的编号以及x,y坐标信息

using Result = struct Result
{
    Point p1, p2;
    double dist;

    Result(Point _p1, Point _p2, double _d) : p1(_p1), p2(_p2), dist(_d) {}
}; // 记录最近点对的信息


double dist(Point& p1, Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
} // 两点间距离辅助函数

Result closest_pair(vector<Point>& arr, int low, int high) { // 核心算法函数
    /*
        arr->目标点集
        low->待考察左区间索引
        high->待考察右区间索引  
    */
    if(high - low == 1) // 如果当前待考察区间内仅有两个点，直接返回这两点间结果信息
        return Result(arr[low], arr[high], dist(arr[low], arr[high]));
    double d1, d2, d3, min_d;
    if(high - low == 2) { // 如果当前待考察区间内有三个点，比较出距离最小的两个点并返回结果
        d1 = dist(arr[low], arr[low+1]);
        d2 = dist(arr[low], arr[high]);
        d3 = dist(arr[low+1], arr[high]);
        min_d = d1 < d2 ? d1 : d2;
        Point p1 = arr[low], p2 = d1 < d2 ? arr[low+1] : arr[high];
        min_d = min_d < d3 ? min_d : d3;
        if(min_d > d3) {
            p1 = arr[low+1];
            p2 = arr[high];
        }
        return Result(p1, p2, dist(p1, p2));
    }
    int mid = (high + low) / 2; // 二分待考察区间
    Result r1 = closest_pair(arr, low, mid); // 求左半部最近点对
    Result r2 = closest_pair(arr, mid + 1, high); // 求右半部最近点对
    Result r = r1.dist < r2.dist ? r1 : r2; // 比较左右半部最近点对，取较小的
    vector<Point> candi;

    for(int i = low; (i <= high) && fabs(arr[i].x - arr[mid].x) < r.dist; ++i) { // 将在前面求得最小点对距离范围内的点对记录下来
        candi.emplace_back(arr[i]);
    }
    sort(candi.begin(), candi.end(), [&](Point p1, Point p2) {
            return p1.y < p2.y;
        });

    for(int i = 0; i < candi.size(); ++i) // 考察中点附近在前面求得最小点对距离范围内的点对距离
        for(int j = i+1; j < candi.size(); ++j) {
            if(arr[i].y - arr[j].y >= r.dist) break; 
            if(dist(arr[i], arr[j]) < r.dist) {
                r = Result(arr[i], arr[j], dist(arr[i], arr[j]));
            }
        }

    return r;

}

int main() {
    ifstream fin;
    fin.open("./data.txt");
    if(!fin.is_open()) {
        cout << "Can't open input file!" << endl;
    }
    else {
        vector<Point> arr; // arr数组存放读入的点数据
        while(!fin.eof()) {
            int idx;
            double x, y;
            fin >> idx >> x >> y;
            Point p(idx, x ,y);
            arr.emplace_back(p);
        }
        sort(arr.begin(), arr.end(), [&](Point p1, Point p2) {
            return p1.x < p2.x;
        }); // 对读入数据按照x轴坐标排序，便于之后划分
        vector<Point> v1(arr);
        auto begin = chrono::system_clock::now();
        Result res = closest_pair(arr, 0, arr.size() - 1);
        auto end = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin);
        printf("分治法求解：\n距离最近点对的编号为：%d和%d，距离为：%lf\n分治求解共耗时%ldms\n", res.p1.idx, res.p2.idx, res.dist, duration.count());
        double d = DBL_MAX;
        Result trivail(v1[0], v1[1], d);
        begin = chrono::system_clock::now();
        for(int i = 0; i < v1.size(); ++i)
            for(int j = i + 1; j < v1.size(); ++j) {
                double dd = dist(v1[i], v1[j]);
                if(dd < d) {
                    d = dd;
                    trivail.p1 = v1[i];
                    trivail.p2 = v1[j];
                    trivail.dist = d;
                }
            }
        end = chrono::system_clock::now();
        auto cost = chrono::duration_cast<chrono::milliseconds>(end - begin);
        printf("\n朴素蛮力法求解：\n距离最近点对的编号为：%d和%d，距离为：%lf\n朴素蛮力法求解共耗时%ldms\n", trivail.p1.idx, trivail.p2.idx, trivail.dist, cost.count());
        fin.close();
    }
    
    return 0;
}