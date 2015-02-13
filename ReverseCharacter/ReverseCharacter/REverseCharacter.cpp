#include <iostream>
#include <string.h>

using namespace std;
void ReverseString(char * str, int left, int right){
	int count = 0;
	char * temp = new char[right - left + 1];
	
	for (int i = right; i >= left; i--){
		temp[count] = str[i];
		++count;
	}

	count = 0;
	for (int i = left; i <= right; i++){
		str[i] = temp[count];
		++count;
	}

	free(temp);
}

void ReverseWord(char * str, int strLength){
	ReverseString(str, 0, strLength-1);
	
	int left = 0, right = 0;
	
	for (int i = 0; i < strLength; ++i){
		if (str[i] == '.'){
			ReverseString(str, left, i - 1);
			left = i + 1;
		}
	}
	ReverseString(str, left, strLength - 1);
}

int main(void){
	char str[] = ".wab.naver.com";
	int strLength = strlen(str);
	ReverseWord(str, strLength);
	cout << str << endl;
	getchar();
	return 0;
}