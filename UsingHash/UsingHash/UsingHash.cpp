#include <iostream>
#include <string.h>
#include <string>
#include <map>

using namespace std;

struct Student{
	string name;
	unsigned int point;
	unsigned int age;
};

void StudentInformationInit(Student *studentArr, map<string, Student *> & StudentInfo, int studentNum){
	studentArr[0].name = "abc";
	studentArr[0].point = 100;
	studentArr[0].age = 26;

	studentArr[1].name = "�̽¿�";
	studentArr[1].point = 100;
	studentArr[1].age = 25;

	studentArr[1].name = "�̿���";
	studentArr[1].point = 100;
	studentArr[1].age = 18;
	StudentInfo.insert(map<string, Student*>::value_type("������", &studentArr[0]));
	StudentInfo.insert(map<string, Student*>::value_type("�̽¿�", &studentArr[1]));
	StudentInfo.insert(map<string, Student*>::value_type("�̿���", &studentArr[2]));
}

void PrintStudentInfo(map<string, Student*> & StudentInfo, string studentName){
	//map<string, Student *>::iterator student;
	auto student = StudentInfo.find(studentName);
	if ( student == StudentInfo.end()){
		cout << "�ش��ϴ� �л��� �̸��� �����ϴ�" << endl;
	}
	else
	{
		cout << student->second->name << endl;
		cout << (student->second)->age << endl;
		cout << (student->second)->point << endl;
	}
}

void ReleaseStudnetInfo(map<string, Student *> & StudentInfo){
	StudentInfo.clear();
}

int main(void){
	int studentNum = 3;
	map<string, Student *> StudentInfo;
	Student * studentArr = new Student[studentNum];
	StudentInformationInit(studentArr, StudentInfo, studentNum);
	PrintStudentInfo(StudentInfo, "������");
	delete[] studentArr;
	studentArr = nullptr;
	ReleaseStudnetInfo(StudentInfo);
	PrintStudentInfo(StudentInfo, "������");
	getchar();
	return 0;
}
