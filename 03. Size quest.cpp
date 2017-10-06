/*
Определение размеров различных типов данных.
(Размер различных типов может варьироваться для 32- и 64-битных компиляторов.)
*/

#include <iostream>
using namespace std;

int main() {
	bool b = true;
	char ch = 'a';
	int i = 12345;
	float f = 3.14;
	double db = 3.14159;

	cout << "Boolean: " << sizeof(b) << endl;    // 1 byte
	cout << "Char: " << sizeof(ch) << endl;      // 1 byte
	cout << "Integer: " << sizeof(i) << endl;    // 4 byetes
	cout << "Float: " << sizeof(f) << endl;      // 4 bytes
	cout << "Double: " << sizeof(db) << endl;    // 8 bytes

	return 0;
}

// Size of the variables will be different for 32 bit and 64 bit compiler.
