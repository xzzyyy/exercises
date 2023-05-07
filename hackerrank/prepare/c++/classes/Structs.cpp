#include <iostream>
#include <sstream>
using namespace std;


struct Student {
    int age;
    string first_name;
    string last_name;
    int standard;

    string display() const {
        ostringstream oss;
        oss << age << " " << first_name << " " << last_name << " " << standard;
        return oss.str();
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Student student;
    cin >> student.age >> student.first_name >> student.last_name >> student.standard;
    cout << student.display() << endl;
    return 0;
}
