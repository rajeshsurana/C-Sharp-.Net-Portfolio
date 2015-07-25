#include <iostream>
#include <string>
using namespace std;

class car{
public:
	string color;
	car(){ color = "violet"; }
	virtual void colorofcar(){
		cout << "car color is " << color << endl;
	}

};

class ford: public car{
public:
	ford(){
		color = "blue";
	}
	void colorofcar(){
		cout << "ford color is " << color << endl;
	}
};

void main(){
	car * c1 = new car();
	car * c2 = new ford();
	c1->colorofcar();
	c2->colorofcar();
	system("pause");
}