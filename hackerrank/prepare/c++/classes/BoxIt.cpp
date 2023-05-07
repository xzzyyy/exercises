#include<bits/stdc++.h>

using namespace std;

//Implement the class Box
//l,b,h are integers representing the dimensions of the box
struct Box {

    // The class should have the following functions :
    // Constructors:

    // Box();
    Box() = default;

    // Box(int,int,int);
    Box(int l, int b, int h)
        : l(l), b(b), h(h)
    {}

    // Box(Box);
    Box(const Box& other) = default;

    // int getLength(); // Return box's length
    int getLength() const { return l; }

    // int getBreadth (); // Return box's breadth
    int getBreadth() const { return b; }

    // int getHeight ();  //Return box's height
    int getHeight() const { return h; }

    // long long CalculateVolume(); // Return the volume of the box
    long long CalculateVolume() const {
        return static_cast<long long>(l) * b * h;
    }

    //Overload operator < as specified
    //bool operator<(Box& b)
    bool operator<(const Box& r) {
        if (l < r.l)
            return true;
        else if (l == r.l && b < r.b)
            return true;
        else if (l == r.l && b == r.b && h < r.h)
            return true;
        else
            return false;
    }

    friend ostream& operator<<(ostream& os, const Box& B);

private:
    int l = 0;
    int b = 0;
    int h = 0;
};

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)
ostream& operator<<(ostream& os, const Box& B) {
    os << B.l << " " << B.b << " " << B.h;
    return os;
}


void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}
