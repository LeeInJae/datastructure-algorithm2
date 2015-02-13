#include <iostream>
#include <string>
#include <string.h>
#include <hash_map>

using namespace std;

class InputData{
public:
	InputData(){}
	~InputData(){}

public:
	string GetPlayerId(){ return playerId; }
	int duneonId() { return dungeonId; }
	static int GetHashMapValueByKey(string key){ return playerIdToInt[key]; }
private:
	string playerId;
	int dungeonId;
	static hash_map<string, int> playerIdToInt;
};

int main(void){
	hash_map<string, int> ppp;
	ppp["leeinjae"] = 3;
	string k = "leeinjae";
	printf("%d", ppp[k]);
	string a = "aaaa";
	printf("%s", a.c_str());
	getchar();
	return 0;
}