#include <iostream>
#include <string.h>
#include <string>

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define NAME_MAX 100

using namespace std;

class Person{
public:
	Person(){}

	Person(string inputName, int inputAge){
		name = inputName;
		age = inputAge;
	}
	
	~Person(){
	}

public:
	
	string GetName(){ return name; }
	int GetAge(){ return age; }

private:
	string name;
	int age;
};

void ErrCheck(errno_t err, char * message){
	if (err == 0){
		printf("%s 성공\n", message);
	}
	else{
		printf("%s 에러 발생\n", message);
	}
}

int main(void){
	FILE * inputFp, * outFp;
	errno_t err;
	err = fopen_s(&inputFp, INPUT_FILE_NAME, "r");
	ErrCheck(err, "InputFile");

	int n;
	fscanf_s(inputFp, "%d", &n);
	Person ** personArr = new Person *[n];

	for (int i = 0; i < n; ++i){
		string inputName;
		int inputAge;		
		fscanf_s(inputFp, "%s %d", inputName.c_str(), NAME_MAX, &inputAge);
		personArr[i] = new Person(inputName, inputAge);
	}

	err = fopen_s(&outFp, OUTPUT_FILE_NAME, "w");
	ErrCheck(err, "OutputFile");

	for (int i = 0; i < n; ++i){
		fprintf_s(outFp, "%s %d\n", personArr[i]->GetName(), personArr[i]->GetAge());
	}
	
	for (int i = 0; i < n; ++i){
		delete personArr[i];
	}
	delete personArr;
	getchar();
	return 0;
}