#include <iostream>
#include <string>
#include <string.h>
#include <hash_map>
#include <set>
#include <algorithm>

#define INPUT_FILE_NAME "INPUT.TXT"
#define OUTPUT_FILE_NAME "OUTPUT.TXT"

#define INPUT_MAX 500
#define PLAYER_ID_MAX 100

using namespace std;

void ErrCheck(errno_t err, char * message){
	if (err == 0){
		printf("%s 성공\n", message);
	}
	else{
		printf("%s 에러 발생\n", message);
		exit(0);
	}
}

class InputData{
public:
	InputData(){}
	InputData(string inputName, int length, int inputAge){
		playerId = inputName;
		dungeonId = inputAge;
	}
	~InputData(){}

public:
	string GetPlayerId(){ return playerId; }
	int GetDungeonId() { return dungeonId; }

private:
	string playerId;
	int dungeonId;
};

bool cmp(InputData * a, InputData * b){
	if (a->GetDungeonId() < b->GetDungeonId())
		return true;
	else if (a->GetDungeonId() == b->GetDungeonId()){
		if (a->GetPlayerId() < b->GetPlayerId())
			return true;
		return false;
	}
	return false;
}

void InputLogFile (InputData ** inputData, int * dataCount, hash_map<string, int> * playerIdToInt, string * playerIntToId, set<string> * playerIdSet){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");
	ErrCheck(err, "InputFile");

	int & tempDataCount = *dataCount;

	while (true){
		char tempPlayerId[PLAYER_ID_MAX];
		int dungeonId;

		fscanf_s(fin, "%s %d", tempPlayerId, PLAYER_ID_MAX, &dungeonId);

		if (tempPlayerId[0] == '*')break;

		string playerId = tempPlayerId;
		inputData[tempDataCount] = new InputData(playerId, playerId.length(), dungeonId);
		playerIdSet->insert(playerId);
		++tempDataCount;
	}

	int temp = 0;
	for (auto i = playerIdSet->begin(); i != playerIdSet->end(); ++i){
		string s = *i;
		playerIdToInt->insert(hash_map<string, int>::value_type(s, temp));
		playerIntToId[temp] = s;
		++temp;
		
	}
	fclose(fin);
}

void ReleaseInputData(InputData ** inputData, int * dataCount){
	int & tempDataCount = *dataCount;

	for (int i = 0; i < tempDataCount; ++i){
		if (inputData[i]){
			delete inputData[i];
			inputData[i] = nullptr;
		}
	}
}

void CountAdjPlayer(InputData ** inputData, int dataCount, hash_map<string, int> * playerIdToInt, string * playerIntToId, set<string> * playerIdSet, short int adjPlayerCountArr[][INPUT_MAX]){
	int startDungeonId;
	int dungeonStartPos;
	int endDungeonId;
	int dungeonEndPos;
	
	for (int i = 0; i < dataCount; ++i){
		startDungeonId = inputData[i]->GetDungeonId();
		dungeonStartPos = i;
		for (int j = i; j < dataCount; ++j){
			endDungeonId = inputData[j]->GetDungeonId();
			dungeonEndPos = j;

			if (startDungeonId != endDungeonId){
				break;
			}
		}
		i = dungeonEndPos - 1;
	}
}

int main(void){
	int dataCount = 0;

	InputData * inputData[INPUT_MAX];
	hash_map<string, int> playerIdToInt;
	string playerIntToId[INPUT_MAX];
	set<string> playerIdSet;
	short int adjPlayerCountArr[INPUT_MAX][INPUT_MAX];
	
	for (int i = 0; i < INPUT_MAX; ++i)
		for (int j = 0; j < INPUT_MAX; ++j)
			adjPlayerCountArr[i][j] = 0;

	InputLogFile(inputData, &dataCount, &playerIdToInt, playerIntToId, &playerIdSet);
	sort(inputData, inputData + dataCount, cmp);
	CountAdjPlayer(inputData, dataCount, &playerIdToInt, playerIntToId, &playerIdSet, adjPlayerCountArr);
	ReleaseInputData(inputData, &dataCount);
	
	getchar();
	return 0;
}