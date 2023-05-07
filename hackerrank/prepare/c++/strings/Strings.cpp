#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string str1, str2;
    cin >> str1 >> str2;

    cout << str1.size() << " " << str2.size() << endl;
    cout << (str1 + str2) << endl;

    swap(str1[0], str2[0]);
    cout << str1 << " " << str2 << endl;

    return 0;
}
