#include <iostream>
#include <string.h>
#include <string>

using namespace std;

void Swap(char * a, char * b){
	char  t = *a;
	*a = *b;
	*b = t;
}

void Combination(char * str, char * res, int curLen, int length, int resPos){
	if (curLen == length){
		return;
	}

	for (int i = curLen; i < length; ++i){
		res[resPos] = str[i];
		cout << res << endl;
		Combination(str, res, i + 1, length, resPos + 1);
		res[resPos] = '\0';
	}
}
int main(void){
	int len = strlen("abc");
	char * str = new char[len + 1];
	char * res = new char[len + 1];
	
	memset(res, '\0', len + 1);
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';

	res[len] = '\0';

	Combination(str, res, 0, len, 0);

	getchar();
	delete[] str;
	delete[] res;
	return 0;
}