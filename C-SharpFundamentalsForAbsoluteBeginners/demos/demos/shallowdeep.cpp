#include <iostream>
#include <string>
class FirstClass {
	 public:
		 virtual void MethodA(int);
		 void MethodA(int, int);
		
};
 void FirstClass::MethodA(int i) {
	 std::cout << "ONE!!\n";
	
}
void FirstClass::MethodA(int i, int j) {
	std::cout << "TWO!!\n";
};

class SecondClass : public FirstClass {
	 public:
		 void MethodA(int);
		
};
 void SecondClass::MethodA(int i) {
	 std::cout << "THREE!!\n";
	
}
 void main() {
	 SecondClass a;
	 a.MethodA(1);
	 a.MethodA(1, 1);
}