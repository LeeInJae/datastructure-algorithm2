#include <iostream>
#include <string.h>
#include <string>

using namespace std;

void Permutation(char * str, int curLen, int strLength, char * res, bool * isUsed){
	if (curLen == strLength){
		res[curLen] = '\0';
		cout << res << endl;
		return;
	}

	for (int i = 0; i < strLength; ++i){
		if (isUsed[str[i] - 'a'] == true) continue;
		res[curLen] = str[i];
		isUsed[str[i] - 'a'] = true;
		Permutation(str, curLen + 1, strLength, res, isUsed);
		res[curLen] = '\0';
		isUsed[str[i] - 'a'] = false;
	}
}

void Swap(char * a, char * b){
	char  t = *a;
	*a = *b;
	*b = t;
}

void Permutation2(char *str, int curLen, int strLength){
	if (curLen == strLength){
		cout << str << endl;
		return;
	}
	for (int i = curLen; i < strLength; ++i){
		Swap(&(str[i]), &(str[curLen]));
		Permutation2(str, curLen + 1, strLength);
		Swap(&(str[i]), &(str[curLen]));
	}
}

int main(void){
	int len = strlen("abc");
	char * str = new char[len+1];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';
	
	
	char * res = new char[len + 1];
	bool * isUsed = new bool[27];
	for (int i = 0; i < 27; ++i)
		isUsed[i] = false;
	
//	Permutation(str, 0, len, res, isUsed);
	Permutation2(str, 0, len);
	
	getchar();
	delete[] res;
	delete[] str;
	delete[] isUsed;
	return 0;
}