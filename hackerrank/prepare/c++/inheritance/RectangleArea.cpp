#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


struct Rectangle {
    Rectangle(istream& is) {
        is >> wd >> hd;
    }

    virtual string display() const {
        return to_string(wd) + " " + to_string(hd);
    }

protected:
    int wd = 0;
    int hd = 0;
};


struct RectangleArea : Rectangle {
    RectangleArea(istream& is)
        : Rectangle(is)
    {
    }

    virtual string display() const {
        return to_string(wd * hd);
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    RectangleArea rec_area(cin);
    cout << rec_area.Rectangle::display() << endl;
    cout << rec_area.display() << endl;
    return 0;
}
