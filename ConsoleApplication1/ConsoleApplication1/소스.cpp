#include <iostream>
#include <hash_map>
#include <set>

using namespace std;

int main(void){
	hash_map<string, set<int>> inputData;
	vector<set<int>*> setVectorPointer;
	
	set<int> * setArr = new set < int > ;
	setVectorPointer.push_back(setArr);
	inputData.insert(hash_map < string, set<int> >::value_type("nana", *setArr));

	set<int>& set1 = inputData["nana"];
	set1.insert(1);
	set1.insert(-10);

	for (auto i = set1.begin(); i != set1.end(); ++i){
		auto pI = *i;
		//printf("%d ", pI);
	}

	set<int>& set2 = inputData["nana"];
	for (auto i = set2.begin(); i != set2.end(); ++i){
		auto pI = *i;
		printf("%d ", pI);
	}
	delete setVectorPointer[0];
	getchar();
	return 0;
}