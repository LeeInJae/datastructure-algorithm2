#pragma once
#include <iostream>

using namespace std;

class Singleton{
public:
	static Singleton * GetInstance();
	void ReleaseInstance();
	void Print(){ cout << "³»°¡ ½Ì±ÛÅæÀÌ´Ù" << endl; }
private:
	Singleton();
	~Singleton();
	static Singleton * mPinstance;
};

