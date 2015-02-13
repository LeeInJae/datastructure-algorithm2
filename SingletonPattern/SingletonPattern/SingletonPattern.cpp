#include <iostream>
#include "Singleton.h"

int main(void){
 	Singleton::GetInstance()->Print();
	Singleton::GetInstance()->Print();
	Singleton::GetInstance()->Print();
	getchar();
	return 0;
}