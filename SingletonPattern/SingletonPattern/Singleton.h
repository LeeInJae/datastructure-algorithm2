#pragma once
#include <iostream>

using namespace std;

class Singleton{
public:
	static Singleton * GetInstance();
	void ReleaseInstance();
	void Print(){ cout << "���� �̱����̴�" << endl; }
private:
	Singleton();
	~Singleton();
	static Singleton * mPinstance;
};

