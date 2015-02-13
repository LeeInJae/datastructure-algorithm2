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

//���ð� �ϳ��� ���̱�
void CarPark::SubWaitCarListDelayTime(){
	for (auto& i = waitCarList.begin(); i != waitCarList.end(); ++i){
		auto obj = *i;
		if (obj->GetTotDestTimeSec() <= curTime || obj->GetIsCheckingTime()){
			obj->SubDealyTime();
			obj->TrueIsCheckingTime();
		}
	}
}

//���ð� ���������ֵ� ����
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

//waitList���� parkingList�� ���ɼ� �ִ� �ֵ��� �Ű���.
void CarPark::CheckWaitCarPossibleParking(){
	if (waitCarList.empty())
		return;

	auto iter = waitCarList.begin();
	auto obj = *iter;

	if ((obj->GetTotDestTimeSec() == curTime) || (obj->GetTotDestTimeSec() < curTime && obj->GetDealyTime() >= 0)){ //������ open ������ �ͼ� ��ٸ� ��
		if (!IsFull()){
			AddCarCurNumber();//�̶����� ���� ���� ����.
			
			if (IsFull() && firstFull == false){ //ó�� ������ �ð��� ����
				firstFull = true;
				firstFullTime = curTime;
			}
			
			obj->TrueIsCheckingTime();
			waitCarList.erase(iter);
			parkingCarList.push_back(obj);
		}
	}
}

//������ �Ϸ�ƴ��� Ȯ��(�����ϴµ� �ɸ��� �ð������ϱ�)
void CarPark::AddParkingCarList(unordered_map< wstring, int>& carInfoData){
	bool flag = false;

	for (auto& i = parkingCarList.begin(); i != parkingCarList.end();){
		auto iter = i;
		auto obj = *iter;
		flag = false;

		obj->AddCurParkTime();

		if (!obj->GetIsParkTime()){ //���� ���� �Ϸ���� �ʰ�
			if (obj->GetCurParkTime() == carInfoData[obj->GetCarName()]) //������ �Ϸ�ƴٸ� workTime������ �����־����
				obj->TrueIsParkTime();
		}
		else{//���� �Ϸ� �Ǿ��ٸ� �������� workTime ����
			obj->AddCurWorkTime();
			if (obj->GetCurWorkTime() == obj->GetWorkTime()){ //�ϱ��� �� �Ϸ�ƴٸ� parkingList ���� adjustList�� ��������(�׸��� ���� ���������� +1 �÷���..��?)
				i = parkingCarList.erase(iter);
				adjustCarList.push_back(obj);
				flag = true;
			}
		}

		if (!flag)
			++i;
	}
}


//carList���� waitList�� �߰��� ���� �ִ��� Ȯ��
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
	//���� ���� ��ٸ��� �ִ� ����
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

	//open���� 10�� �� �������� ������ �� ������
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
		
		//��߽ð����� �� ��
		while (curTime != GetTotOpenTimeSec()){
			SubWaitCarListDelayTime();
			++curTime;
		}
	}
	
	curTime = GetTotOpenTimeSec();
	
	while (curTime != GetTotCloseTimeSec()){
		CheckCarListDestTime(carList); //carList���� waitList�� �߰��� ���� ���� �߰�
		CheckWaitCarListDelayTime(); //waitCar�� �ִ� �ֵ� �� �̹� ���� ���� �� ����
		CheckWaitCarPossibleParking(); //wait���� ���� ������ ���� parkingList�� �߰�
		++curTime;
 		if (curTime == 36567) 
 			curTime = 36567;
		AddParkingCarList(carInfoData); //parkingList�� �ִ� parkingī���� �����ϴ� �ð� Ȯ��
		SubWaitCarListDelayTime();//wait�� �ִ� car���� ���� ���ð��� �ϳ��� �ٿ��־�� ��
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
	res.bustParkTime = carInfoData[L"����Ʈ"];
	res.firstDestCarname = (carList.front())->GetCarName();
	carPark->DoParkingCar(carList, carInfoData);
	res.totTimeSec = carPark->GetFirstFullTime();
	SecToTime(res);
	Output(res);
	getchar();
	return 0;
}