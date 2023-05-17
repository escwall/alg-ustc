#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<random>
#include<cmath>
#include<cstdio>

using namespace std;

using Point = struct Point
{
    int idx;
    double x;
    double y;

    Point(int _i, double _x, double _y) : idx(_i), x(_x), y(_y) {}
};

using Result = struct Result
{
    Point p1, p2;
    double dist;

    Result(Point _p1, Point _p2, double _d) : p1(_p1), p2(_p2), dist(_d) {}
};


double dist(Point& p1, Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

Result closest_pair(vector<Point>& arr, int low, int high) {
    if(high - low == 1) 
        return Result(arr[low], arr[high], dist(arr[low], arr[high]));
    double d1, d2, d3, min_d;
    if(high - low == 2) {
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
    int mid = (high + low) / 2;
    Result r1 = closest_pair(arr, low, mid);
    Result r2 = closest_pair(arr, mid + 1, high);
    Result r = r1.dist < r2.dist ? r1 : r2;
    vector<Point> candi;

    for(int i = low; (i <= high) && fabs(arr[i].x - arr[mid].x) < r.dist; ++i) {
        candi.emplace_back(arr[i]);
    }
    sort(candi.begin(), candi.end(), [&](Point p1, Point p2) {
            return p1.y < p2.y;
        });

    for(int i = 0; i < candi.size(); ++i)
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
        Result res = closest_pair(arr, 0, arr.size() - 1);
        printf("距离最近点对的编号为：%d和%d，距离为：%lf", res.p1.idx, res.p2.idx, res.dist);
        fin.close();
    }
    
    return 0;
}