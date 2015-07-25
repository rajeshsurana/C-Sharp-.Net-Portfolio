#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() { 
	fstream fs;
	fs.open("test.txt", fstream::in | fstream::out | fstream::app);
	string L[10];
	int k = 10;
	int lines = 0;
	while (!fs.eof()){
		getline(fs, L[lines % k]);
		lines++;
	}
	int start, count;
	if (lines < k){
		start = 0;
		count = lines;
	}
	else{
		start = lines%k;
		count = k;
	}
	for (int i = 0; i < count; i++){
		cout << L[(start + i) % k] << "\n";
	}

	fs.close();
	system("pause");
	return 0;
}