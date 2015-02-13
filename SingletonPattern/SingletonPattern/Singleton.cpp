#include "Singleton.h"

Singleton * Singleton::mPinstance = nullptr;

Singleton::Singleton()
{
}


Singleton::~Singleton()
{
}

void Singleton::ReleaseInstance()
{
	if (mPinstance != nullptr){
		delete mPinstance;
		mPinstance = nullptr;
	}
}

Singleton * Singleton::GetInstance()
{
	if (!mPinstance){
		mPinstance = new Singleton;
	}
	return mPinstance;
}
