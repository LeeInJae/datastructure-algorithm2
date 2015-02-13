#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unordered_map>
#include <list>
#include <locale>
#include <codecvt>

#define INPUT_INFO_FILE_NAME "DATA0.ini"
#define INPUT_DATA_FILE_NAME "DATA0.txt"
#define OUTPUT_FILE_NAME "DATA.out"
#define CAR_NAME_MAX_LENGTH 100
#define MAX_WAIT_CAR_COUNT 10

using namespace std;

struct Time{
	int hour, minute, second;
};

class Car{
public:
	Car(){}
	Car(wstring inputCarName, Time inputDestTime, int inputWorkTime, int inputTotDestTimeSec, int inputOrder, int inputMaxDelayTime) :
		carName(inputCarName), destTime(inputDestTime), workTime(inputWorkTime), totDestTimeSec(inputTotDestTimeSec), order(inputOrder), delayTime(inputMaxDelayTime), adjustTime(0),
		isCehckingTime(false),isParkTime(false), curParkTime(0), curWorkTime(0){}
	~Car(){}

public:
	void TrueIsCheckingTime(){ isCehckingTime = true; }
	void TrueIsParkTime(){ isParkTime = true; }
	void SubDealyTime(){ --delayTime; }
	void AddCurParkTime(){ ++curParkTime; }
	void AddCurWorkTime(){ ++curWorkTime; }
	wstring GetCarName(){ return carName; }
	Time GetDestTime(){ return destTime; }
	int GetWorkTime(){ return workTime; }
	int GetDestTimeHour(){ return destTime.hour; }
	int GetDestTimeMin(){ return destTime.minute; }
	int GetDestTimeSec(){ return destTime.second; }
	int GetTotDestTimeSec(){ return totDestTimeSec; }
	int GetOrder(){ return order; }
	int GetDealyTime(){ return delayTime; }
	int GetCurParkTime(){ return curParkTime; }
	int GetCurWorkTime(){ return curWorkTime; }
	bool GetIsCheckingTime(){ return isCehckingTime; }
	bool GetIsParkTime(){ return isParkTime; }

private:
	wstring carName;
	Time destTime;
	int workTime;
	int totDestTimeSec;
	int order;
	int delayTime;
	int adjustTime;
	bool isCehckingTime;
	bool isParkTime;
	int curParkTime;
	int curWorkTime;
};

class CarPark{
public:
	CarPark(){}
	CarPark(int inputSpaaceArea, int inputAdjustmentTime, int inputMaxDelayTime, Time inputOpenTime, Time inputCloseTime, int inputTotOpenTimeSec, int inputTotCloseTimeSec)
		: spaceArea(inputSpaaceArea), adjustmentTime(inputAdjustmentTime), maxDelayTime(inputMaxDelayTime), openTime(inputOpenTime), closeTime(inputCloseTime),
		curCarNumber(0), usingParkCarCount(0), totOpenTimeSec(inputTotOpenTimeSec), totCloseTimeSec(inputTotCloseTimeSec), firstFull(false), firstFullTime(0), curTime(0)
	{}
	~CarPark(){}

public:
	void TrueFirstFull(){ firstFull = true; }
	void CheckCarListDestTime(list<Car*> & carList);
	void CheckWaitCarListDelayTime();
	void CheckWaitCarPossibleParking();
	void AddCarCurNumber(){ ++curCarNumber; }
	void SubCarCurNumber(){ --curCarNumber; }
	void AddUsingParkCarCount(){ ++usingParkCarCount; }
	void SubWaitCarListDelayTime();
	void AddParkingCarList(unordered_map< wstring, int>& carInfoData);
	int GetSpaceArea(){ return spaceArea; }
	int GetAdjustmentTime(){ return adjustmentTime; }
	int GetMaxDealyTime(){ return maxDelayTime; }
	int GetCurCarNumber(){ return curCarNumber; }
	Time GetOpenTime(){ return openTime; }
	Time GetCloseTime(){ return closeTime; }
	int GetTotOpenTimeSec(){ return totOpenTimeSec; }
	int GetTotCloseTimeSec(){ return totCloseTimeSec; }
	int GetUsingParkCarCount(){ return usingParkCarCount; }
	int GetFirstFullTime(){ return firstFullTime; }
	bool GetFirstFull(){ return firstFull; }
	bool IsEmpty(){
		if (curCarNumber == 0)
			return true;
		return false;
	}

	bool IsFull(){
		if (curCarNumber == spaceArea)
			return true;
		return false;
	}
	list<Car*>& GetWaitCarList(){ return waitCarList; }
	list<Car*>& GetParkingCarList(){ return parkingCarList; }
	list<Car*>& GetAdjustCarList(){ return adjustCarList; }
	
	void DoParkingCar(list<Car*> & carList, unordered_map< wstring, int>& carInfoData);
private:
	int spaceArea;
	int adjustmentTime;
	int maxDelayTime;
	Time openTime, closeTime;
	int totOpenTimeSec;
	int totCloseTimeSec;
	int curCarNumber;
	int usingParkCarCount;
	list<Car *> waitCarList;
	list<Car *> parkingCarList;
	list<Car *> adjustCarList;
	bool firstFull;
	int firstFullTime;
	int curTime;
};

struct Result{
	int bustParkTime;
	wstring firstDestCarname;
	int totTimeSec;
	Time fullParkingTime;
	int usingParkCarCount;
};

struct StlListSort{
	bool operator() (Car * t1, Car * t2){
		if (t1->GetTotDestTimeSec() < t2->GetTotDestTimeSec()){
			return true;
		}
		else if (t1->GetTotDestTimeSec() == t2->GetTotDestTimeSec()){
			if (t1->GetOrder() < t2->GetOrder())
				return true;
		}
		else
			return false;
	
		return false;
	}
};

Time StrTokTime(wchar_t * str){
	Time time;
	wchar_t * token;
	wchar_t * nextToken;
	int calculateTime;
	for (int i = 0; i < 3; ++i)
	{
		calculateTime = 0;
		token = wcstok_s(str, L":", &nextToken); 
		str = nextToken;
		if (wcslen(token) == 2){
			calculateTime += (token[0] - '0') * 10;
			calculateTime += (token[1] - '0');
		}
		else
			calculateTime += (token[0] - '0');
		
		switch (i)
		{
		case 0:
			time.hour = calculateTime;
			break;

		case 1:
			time.minute = calculateTime;
			break;

		case 2:
			time.second = calculateTime;
			break;

		default:
			break;
		}
	}
	return time;
}

void InputData(unordered_map< wstring, int>& carInfoData, CarPark *& carPark){
	wifstream wifs;
	wstring txtline;
	wifs.open("data0.ini");
	wifs.imbue(locale(wifs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	
	int spaceArea;
	int adjustmentTime;
	int maxDelayTime;
	Time openTime, closeTime;
	wchar_t tempName[CAR_NAME_MAX_LENGTH];
	int tempInt, tempOpenTime, tempCloseTime;

	wifs >> txtline;

	for (int i = 0; i < 3; ++i){
		wifs >> txtline;
		wifs >> txtline;
		wifs >> tempInt;
		switch (i)
		{
		case 0:
			spaceArea = tempInt;
			break;
		case 1:
			adjustmentTime = tempInt;
			break;
		case 2:
			maxDelayTime = tempInt;
			break;
		default:
			break;
		}
	}

	wifs >> txtline;
	wifs >> tempName;
	wifs >> tempName;
 	openTime = StrTokTime(tempName);
 	tempOpenTime = 0;
 	tempOpenTime += openTime.second + openTime.minute * 60 + openTime.hour * 3600;
 	
	wifs >> txtline;
	wifs >> tempName;
	wifs >> tempName;
 	closeTime = StrTokTime(tempName);
 	tempCloseTime = 0;
 	tempCloseTime += closeTime.second + closeTime.minute * 60 + closeTime.hour * 3600;
 
 	carPark = new CarPark(spaceArea, adjustmentTime, maxDelayTime, openTime, closeTime, tempOpenTime, tempCloseTime);

 	while (true){
 		wchar_t tempStr[CAR_NAME_MAX_LENGTH];
		wifs >> tempName;
		if (tempName[0] == '\0') break;
		wifs >> tempStr;
		wifs >> tempStr;
		wifs >> tempStr;
		wifs >> tempInt;
		tempName[wcslen(tempName)-1] = '\0';
		for (unsigned int i = 0; i < wcslen(tempName); ++i){
			tempName[i] = tempName[i + 1];
		}
		wstring carName = tempName;
		tempName[0] = '\0';
		carInfoData[carName] = tempInt;
	}
	wifs.close();
}

void InputCarData(list<Car*> &carList, int maxDelayTime){
	wifstream wifs;
	wstring txtline;
	wifs.open("data0.txt");
	wifs.imbue(locale(wifs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	
	int tempInt, tempTime;
	int order = 0;
	wchar_t tempStr[CAR_NAME_MAX_LENGTH];
	
	wifs >> txtline;
	wifs >> txtline;
	wifs >> txtline;

	while (true){
		wifs >> tempStr;
		if (tempStr[0] == '\0')
			break;
		
		wstring carName = tempStr;
		wifs >> tempStr;
		
		Time time = StrTokTime(tempStr);

		wifs >> tempInt;
		
		tempTime = 0;
		tempTime += time.second + time.minute * 60 + time.hour * 3600;
		
		carList.insert(carList.begin(), new Car(carName, time, tempInt, tempTime, order, maxDelayTime));
		tempStr[0] = '\0';
		++order;
	}
	wifs.close();
}

//대기시간 하나씩 줄이기
void CarPark::SubWaitCarListDelayTime(){
	for (auto& i = waitCarList.begin(); i != waitCarList.end(); ++i){
		auto obj = *i;
		if (obj->GetTotDestTimeSec() <= curTime || obj->GetIsCheckingTime()){
			obj->SubDealyTime();
			obj->TrueIsCheckingTime();
		}
	}
}

//대기시간 지나버린애들 제거
void CarPark::CheckWaitCarListDelayTime(){
	for (auto& i = waitCarList.begin(); i != waitCarList.end();){
		auto obj = *i;

		if (obj->GetDealyTime() < 0){
			i = waitCarList.erase(i);
		}
		else
			++i;
	}
}

//waitList에서 parkingList로 가능성 있는 애들을 옮겨줌.
void CarPark::CheckWaitCarPossibleParking(){
	if (waitCarList.empty())
		return;

	auto iter = waitCarList.begin();
	auto obj = *iter;

	if ((obj->GetTotDestTimeSec() == curTime) || (obj->GetTotDestTimeSec() < curTime && obj->GetDealyTime() >= 0)){ //주차장 open 이전에 와서 기다린 차
		if (!IsFull()){
			AddCarCurNumber();//이때부터 주차 공간 차지.
			
			if (IsFull() && firstFull == false){ //처음 만차된 시간을 구함
				firstFull = true;
				firstFullTime = curTime;
			}
			
			obj->TrueIsCheckingTime();
			waitCarList.erase(iter);
			parkingCarList.push_back(obj);
		}
	}
}

//주차가 완료됐는지 확인(주차하는데 걸리는 시간있으니까)
void CarPark::AddParkingCarList(unordered_map< wstring, int>& carInfoData){
	bool flag = false;

	for (auto& i = parkingCarList.begin(); i != parkingCarList.end();){
		auto iter = i;
		auto obj = *iter;
		flag = false;

		obj->AddCurParkTime();

		if (!obj->GetIsParkTime()){ //아직 주차 완료되지 않고
			if (obj->GetCurParkTime() == carInfoData[obj->GetCarName()]) //주차가 완료됐다면 workTime증가를 시켜주어야함
				obj->TrueIsParkTime();
		}
		else{//주차 완료 되었다면 이제부터 workTime 정의
			obj->AddCurWorkTime();
			if (obj->GetCurWorkTime() == obj->GetWorkTime()){ //일까지 다 완료됐다면 parkingList 에서 adjustList로 보내야함(그리고 이제 주차공간을 +1 늘려야..ㅇ?)
				i = parkingCarList.erase(iter);
				adjustCarList.push_back(obj);
				flag = true;
			}
		}

		if (!flag)
			++i;
	}
}


//carList에서 waitList로 추가될 놈이 있느지 확인
void CarPark::CheckCarListDestTime(list<Car*> & carList){
	if (carList.empty())
		return;

	auto iter = carList.begin();
	auto obj = *iter;

	if (obj->GetTotDestTimeSec() == curTime){
		carList.erase(iter);
		waitCarList.push_back(obj);
	}
}

void CarPark::DoParkingCar(list<Car*> & carList, unordered_map< wstring, int>& carInfoData){
	//오픈 전에 기다리고 있는 차들
	for (auto& i = carList.begin(); i != carList.end();){
		auto obj = *i;

		if (obj->GetTotDestTimeSec() < totOpenTimeSec){
			waitCarList.push_back(obj);
			i = carList.erase(i);
		}
		else
			++i;

		if (waitCarList.size() >= MAX_WAIT_CAR_COUNT)
			break;
	}

	//open전에 10개 다 차있으면 이전꺼 다 지워줌
	if (waitCarList.size() >= 10){
		for (auto& i = carList.begin(); i != carList.end();){
			auto obj = *i;

			if (obj->GetTotDestTimeSec() < totOpenTimeSec){
				i = carList.erase(i);
			}
			else
				++i;
		}
	}

	if (!waitCarList.empty()){
		auto iter = waitCarList.begin();
		auto obj = *iter;
		curTime = obj->GetTotDestTimeSec();
		
		//출발시간까지 다 깜
		while (curTime != GetTotOpenTimeSec()){
			SubWaitCarListDelayTime();
			++curTime;
		}
	}
	
	curTime = GetTotOpenTimeSec();
	
	while (curTime != GetTotCloseTimeSec()){
		CheckCarListDestTime(carList); //carList에서 waitList로 추가될 만한 놈을 추가
		CheckWaitCarListDelayTime(); //waitCar에 있는 애들 중 이미 가망 없는 애 제거
		CheckWaitCarPossibleParking(); //wait에서 주차 가능한 차를 parkingList에 추가
		++curTime;
 		if (curTime == 36567) 
 			curTime = 36567;
		AddParkingCarList(carInfoData); //parkingList에 있는 parking카들의 주차하는 시간 확인
		SubWaitCarListDelayTime();//wait에 있는 car들은 이제 대기시간을 하나씩 줄여주어야 함
	}
}

void SecToTime(Result & res){
	int sec, min, hr;
	sec = res.totTimeSec;
	min = sec / 60;
	sec = sec % 60;

	hr = min / 60;
	min = min % 60;
	
	res.fullParkingTime.hour = hr;
	res.fullParkingTime.minute = min;
	res.fullParkingTime.second = sec;
}

void Output(Result res){
	res.usingParkCarCount = 0;
	wofstream wofs;
	wofs.open("data0.out");
	wofs.imbue(locale(wofs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	wofs << res.bustParkTime << endl << res.firstDestCarname << endl << res.fullParkingTime.hour << ":" << res.fullParkingTime.minute << ":" << res.fullParkingTime.second << endl << res.usingParkCarCount << endl;
	wofs.close();

}

int main(void){
	CarPark * carPark = nullptr;
	unordered_map< wstring, int> carInfoData;
	list<Car*> carList;

	InputData(carInfoData, carPark);
	InputCarData(carList, carPark->GetMaxDealyTime());
	carList.sort(StlListSort());

	Result res;
	res.bustParkTime = carInfoData[L"버스트"];
	res.firstDestCarname = (carList.front())->GetCarName();
	carPark->DoParkingCar(carList, carInfoData);
	res.totTimeSec = carPark->GetFirstFullTime();
	SecToTime(res);
	Output(res);
	getchar();
	return 0;
}