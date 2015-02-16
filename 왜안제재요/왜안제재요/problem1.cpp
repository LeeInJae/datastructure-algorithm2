#include <iostream>
#include <string>
#include <string.h>
#include <hash_map>
#include <set>
#include <algorithm>
#include <vector>
#include <time.h>

#define INPUT_FILE_NAME "INPUT.TXT"
#define OUTPUT_FILE_NAME "OUTPUT.TXT"

#define INPUT_FILE_MAX (2<<23)
#define INPUT_PLAYER_MAX 501

#define PLAYER_ID_MAX 100

using namespace std;

void ErrCheck(errno_t err, char * message){
	if (err == 0){
		//printf("%s 성공\n", message);
	}
	else{
		//printf("%s 에러 발생\n", message);
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
	static bool Cmp(const InputData * t1, const InputData * t2) {
		if (t1->playerId < t2->playerId){
			return true;
		}
		else if (t1->playerId == t2->playerId){
			if (t1->dungeonId < t2->dungeonId)
				return true;
		}
		return false;
	}
private:
	string playerId;
	int dungeonId;
};

struct DataPart{
	int startPos, endPos;
};

struct OutPutData{
	string id;
	unsigned int count;
};

bool cmp2(OutPutData a, OutPutData b){
	if (a.count > b.count)
		return true;
	else if (a.count == b.count){
		if (a.id < b.id)
			return true;
		return false;
	}
	return false;
}

void InputLogFile(vector< InputData*> & inputData, hash_map< string, int> * playerIdToInt, string * playerIntToId, set< string> * playerIdSet){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");
	ErrCheck(err, "InputFile Open");

	while (true){
		char tempPlayerId[PLAYER_ID_MAX];
		int dungeonId;

		fscanf_s(fin, "%s %d", tempPlayerId, PLAYER_ID_MAX, &dungeonId);

		if (tempPlayerId[0] == '*') break;

		string playerId = tempPlayerId;
		inputData.push_back(new InputData(playerId, playerId.length(), dungeonId));
		playerIdSet->insert(playerId);
	}

	int temp = 0;
	for (auto i = playerIdSet->begin(); i != playerIdSet->end(); ++i){
		string s = *i;
		playerIdToInt->insert(hash_map< string, int>::value_type(s, temp));
		playerIntToId[temp] = s;
		++temp;

	}
	fclose(fin);
}

void DataPartition(vector< InputData*> & inputData, hash_map< string, int> * playerIdToInt, string * playerIntToId, set< string> * playerIdSet, hash_map< string, DataPart> * dataCover){
	string startPlayerId;
	string endPlayerId;
	int dungeonStartPos;
	int dungeonEndPos;
	DataPart data;
	unsigned int dataCount = inputData.size();
	unsigned int i, j;
	for (i = 0; i < dataCount; ++i){
		startPlayerId = inputData[i]->GetPlayerId();
		dungeonStartPos = i;
		data.startPos = i;
		data.endPos = i;
		for (j = i; j < dataCount; ++j){
			endPlayerId = inputData[j]->GetPlayerId();
			dungeonEndPos = j;

			if (startPlayerId != endPlayerId){
				break;
			}
		}

		if (j == dataCount){
			data.endPos = dungeonEndPos;
			dataCover->insert(hash_map< string, DataPart>::value_type(inputData[i]->GetPlayerId(), data));
			break;
		}
		i = dungeonEndPos - 1;
		data.endPos = i;
		dataCover->insert(hash_map< string, DataPart>::value_type(inputData[i]->GetPlayerId(), data));
	}
}

void CountAdjPlayer(vector< InputData*> & inputData, hash_map< string, set< int>> & settingInputData, hash_map< string, int> & playerIdToInt, string * playerIntToId, set< string> & playerIdSet, hash_map< string, DataPart> & dataCover){
	OutPutData count[INPUT_PLAYER_MAX];
	unsigned int playerCount = playerIdSet.size();
	unsigned int dataCount = inputData.size();
	FILE * fout;
	errno_t err;
	err = fopen_s(&fout, OUTPUT_FILE_NAME, "w");
	ErrCheck(err, "OutputFile Open");


	for (auto& i = playerIdSet.begin(); i != playerIdSet.end(); ++i){
		string playerId = *i;
		for (unsigned int j = 0; j < playerCount; ++j){
			count[j].id = playerIntToId[j];
			count[j].count = 0;
		}

		auto playerIdData = dataCover[playerId];

		for (int j = playerIdData.startPos; j <= playerIdData.endPos; ++j){
			int key = inputData[j]->GetDungeonId();
			for (auto& k = playerIdSet.begin(); k != playerIdSet.end(); ++k){
				string foundPlyaerId = *k;
				if (playerId == foundPlyaerId) continue;

				set< int>& foundSet = settingInputData[foundPlyaerId];
				auto curKey = foundSet.find(key);
				if (curKey != foundSet.end()){
					int foundPlyaerIdtoInt = playerIdToInt[foundPlyaerId];
					++(count[foundPlyaerIdtoInt].count);
				}
			}
		}

		sort(count, count + playerCount, cmp2);

		fprintf(fout, "%s:", playerId.c_str());
		int outCount = 0;
		for (unsigned int j = 0; j < playerCount; ++j){
			if (count[j].count == 0) break;
			fprintf(fout, "%s(%d)", count[j].id.c_str(), count[j].count);
			if (j != 2 && j + 1 < 3 && count[j + 1].count != 0)
				fprintf(fout, ",");
			else{
				outCount = j;
				break;
			}
		}
		for (unsigned int j = outCount + 1; j < playerCount; ++j){
			if (count[j].count != 0 && count[j].count == count[outCount].count){
				fprintf(fout, ",");
				fprintf(fout, "%s(%d)", count[j].id.c_str(), count[j].count);
			}
			if (j + 1 >= playerCount || count[j + 1].count != count[outCount].count)
				break;
		}
		fprintf(fout, "\n");
	}
	fclose(fout);
}

void ReleaseInputData(vector< InputData*> & inputData, vector< set< int>*> & saveSetPointer){
	for (unsigned int i = 0; i < inputData.size(); ++i){
		if (inputData[i]){
			delete inputData[i];
			inputData[i] = nullptr;
		}
	}
	for (unsigned int i = 0; i < saveSetPointer.size(); ++i){
		if (saveSetPointer[i]){
			delete saveSetPointer[i];
			saveSetPointer[i] = nullptr;
		}
	}
}

void SettingData(vector< InputData*> & inputData, hash_map< string, set< int>> & settingInputData, vector< set< int>*> & saveSetPointer, set< string> & playerIdset){
	unsigned int playerCount = playerIdset.size();
	for (auto& i = playerIdset.begin(); i != playerIdset.end(); ++i){
		string curPlayer = *i;
		set< int> * setArr = new set < int > ;
		saveSetPointer.push_back(setArr);
		settingInputData.insert(hash_map < string, set< int> >::value_type(curPlayer, *setArr));
	}

	unsigned int dataCount = inputData.size();
	for (unsigned int i = 0; i < dataCount; ++i){
		set< int> & curSet = settingInputData[inputData[i]->GetPlayerId()];
		curSet.insert(inputData[i]->GetDungeonId());
	}
}

int main(void){
	clock_t start_time, end_time;

	vector< InputData*> inputData;
	hash_map<string, set<int>> settingInputData;
	vector<set<int>*> saveSetPointer;
	inputData.reserve(INPUT_FILE_MAX);
	saveSetPointer.reserve(512);
	hash_map< string, int> playerIdToInt;
	hash_map< string, DataPart> dataCover;
	string playerIntToId[INPUT_PLAYER_MAX];
	set<string> playerIdSet;

	InputLogFile(inputData, &playerIdToInt, playerIntToId, &playerIdSet);
	sort(inputData.begin(), inputData.end(), InputData::Cmp);
	SettingData(inputData, settingInputData, saveSetPointer, playerIdSet);
	DataPartition(inputData, &playerIdToInt, playerIntToId, &playerIdSet, &dataCover);
	start_time = clock();
	CountAdjPlayer(inputData, settingInputData, playerIdToInt, playerIntToId, playerIdSet, dataCover);
	ReleaseInputData(inputData, saveSetPointer);
	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}
