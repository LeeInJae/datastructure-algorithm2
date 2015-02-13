#include<bitset>
#include<iostream>

using namespace std;
struct A{
	int a, b;
};

class AA{
public:
	int a, b, c;
	virtual void Print(){};
};

int main(void){
	struct A aa, bb;
	bb.a = 3;
	bb.b = 5;

	AA aaa, bbb;
	bbb.a = 10;
	bbb.b = 5;
	aaa = bbb;
	aa = bb;
	cout << sizeof(aaa) << endl;
	
	int i = 0x12345678;
	int a = 11;
	int &b = a;
	
	cout << (32 >> 1) << endl;
	cout << (-32 >> 1) << endl;
	int temp = a;
	int res = 0;
	cout << bitset<32>(a) << endl;
	cout << bitset<32>(res) << endl << endl << endl;

	for (int i = 0; i < 31; ++i){
		int temp = a & 1;
		res = res + temp;
		res <<= 1;
		a >>= 1;
		cout << bitset<32>(a) << endl;
		cout << bitset<32>(res) << endl << endl << endl;
	}
	cout << bitset<32>(temp) << endl;
	cout << bitset<32>(res) << endl;

	int c = 10;
	int d = 20;

	c ^= d;
	d ^= c;
	c ^= d;
	//c = (c ^ d) ^ c;
	//d = (c ^ d);

	cout << c << endl;
	cout << d << endl;
	getchar();
	return 0;
}
