#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


constexpr int QUERY_SZ = -1;


vector<int> read_nums(int sz) {
    if (sz == QUERY_SZ)
        cin >> sz;
    
    vector<int> nums;
    for (int i = 0; i < sz; ++i) {
        int n;
        cin >> n;
        nums.push_back(n);
    }
    return nums;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    vector<int> num_line = read_nums(2);
    int arr_cnt = num_line[0];
    int q_cnt = num_line[1];
    
    vector<vector<int>> arrs(arr_cnt, vector<int>());
    
    for (int i = 0; i < arr_cnt; ++i)
        arrs[i] = read_nums(QUERY_SZ);

    for (int i = 0; i < q_cnt; ++i)
    {
        num_line = read_nums(2);
        cout << arrs[num_line[0]][num_line[1]] << endl;
    }
    
    return 0;
}
