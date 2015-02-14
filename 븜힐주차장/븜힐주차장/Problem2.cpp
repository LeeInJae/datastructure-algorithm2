#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unordered_map>
#include <list>
#include <locale>
#include <codecvt>

#define INPUT_INFO_FILE_NAME L"Data0.ini"
#define INPUT_DATA_FILE_NAME L"Data0.txt"
#define OUTPUT_FILE_NAME L"DATA.out"
#define CAR_NAME_MAX_LENGTH 100

using namespace std;

struct Time{
	int hour, minute, second;
};

class Car{
public:
	Car(){}
	Car(wstring inputCarName, Time inputDestTime, int inputWorkTime, int inputTotDestTimeSec, int inputOrder, int inputMaxDelayTime) :
		carName(inputCarName), destTime(inputDestTime), workTime(inputWorkTime), totDestTimeSec(inputTotDestTimeSec), order(inputOrder), delayTime(inputMaxDelayTime), adjustTime(0),
		isCehckingTime(false),isFinishPark(false), isFinishWork(false), curParkTime(0), curWorkTime(0), curAdjustTime(0){}
	~Car(){}

public:
	void SubDealyTimeToSpecialNumber(int interval){ delayTime -= interval; }
	void TrueIsCheckingTime(){ isCehckingTime = true; }
	void TrueIsFinishPark(){ isFinishPark = true; }
	void TrueIsFinishWork(){ isFinishWork = true; }
	void SubDealyTime(){ --delayTime; }
	void AddCurParkTime(){ ++curParkTime; }
	void AddCurWorkTime(){ ++curWorkTime; }
	void AddCurAdjustTime(){ ++curAdjustTime; }
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
	int GetCurAdjustTime(){ return curAdjustTime; }
	bool GetIsCheckingTime(){ return isCehckingTime; }
	bool IsFinishPark(){ return isFinishPark; }
	bool IsFinishWork(){ return isFinishWork; }
private:
	wstring carName;
	Time destTime, finishTime;
	int workTime;
	int totDestTimeSec;
	int order;
	int delayTime;
	int adjustTime;
	bool isCehckingTime;
	bool isFinishPark;
	bool isFinishWork;
	int curParkTime;
	int curWorkTime;
	int curAdjustTime;
};

class CarPark{
public:
	CarPark(){}
	CarPark(int inputSpaaceArea, int inputAdjustmentTime, int inputMaxDelayTime, Time inputOpenTime, Time inputCloseTime, int inputTotOpenTimeSec, int inputTotCloseTimeSec)
		: spaceArea(inputSpaaceArea), adjustmentTime(inputAdjustmentTime), maxDelayTime(inputMaxDelayTime), openTime(inputOpenTime), closeTime(inputCloseTime),
		curCarNumber(0), usingParkCarCount(0), totOpenTimeSec(inputTotOpenTimeSec), totCloseTimeSec(inputTotCloseTimeSec), firstFull(false), firstFullTime(0), curTime(0),
		curAdjustmentCar(nullptr), isFinishcurAdjustmentCar(false)
	{}
	~CarPark(){}

public:
	void TrueFirstFull(){ firstFull = true; }
	void CheckCarListDestTime(list<Car*> & carList);
	void CheckWaitCarListDelayTime();
	void CheckWaitCarPossibleParking(unordered_map< wstring, int>& carInfoData);
	void CheckAdjustCar();
	void AddCarCurNumber(){ ++curCarNumber; }
	void SubCarCurNumber(){ --curCarNumber; }
	void AddUsingParkCarCount(){ ++usingParkCarCount; }
	void SubWaitCarListDelayTime();
	void AddParkingCarList(unordered_map< wstring, int>& carInfoData);
	void CheckAdjutWaitCarList();
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
	list<Car *> adjustWaitCarList;
	bool firstFull;
	bool isFinishcurAdjustmentCar;
	int firstFullTime;
	int curTime;
	Car * curAdjustmentCar;
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
	wifs.open(INPUT_INFO_FILE_NAME);
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
	wifs.open(INPUT_DATA_FILE_NAME);
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
		obj->SubDealyTime();
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
//���׼����� �� ����

void CarPark::CheckWaitCarPossibleParking(unordered_map< wstring, int>& carInfoData){
	if (waitCarList.empty())
		return;

	auto iter = waitCarList.begin();
	auto obj = *iter;

	if (obj->GetDealyTime() >= 0){
		if (!IsFull()){
			++curCarNumber;//�̶����� ���� ���� ����.
			
			++usingParkCarCount;//�̿��ϴ� �� ī��Ʈ

			if (IsFull() && firstFull == false){ //ó�� ������ �ð��� ����
				firstFull = true;
				firstFullTime = curTime;
			}
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

		if (!obj->IsFinishPark()){ //���� ���� �Ϸ���� ����
			obj->AddCurParkTime();
			if (obj->GetCurParkTime() == carInfoData[obj->GetCarName()]) //������ �Ϸ�ƴٸ� workTime������ �����־����
				obj->TrueIsFinishPark();
		}
		else{//���� �Ϸ� �Ǿ��ٸ� �������� workTime ����
			if (!obj->IsFinishWork()){//work ���� �ȳ�������
				obj->AddCurWorkTime();
				if (obj->GetCurWorkTime() == obj->GetWorkTime()){ //�ϱ��� �� �Ϸ�ƴٸ� parkingList ���� adjustList�� ��������(�׸��� ���� ���������� + 1 �÷���..��?)
					obj->TrueIsFinishWork();
				}
			}
			else{//���� ��������
				i = parkingCarList.erase(iter);
				adjustWaitCarList.push_back(obj); //���� ����ٿ� �־���.
				flag = true;
				//--curCarNumber;
			}
		}

		if (flag == false)
			++i;
	}
}

void CarPark::CheckAdjutWaitCarList(){
	if (adjustWaitCarList.empty())
		return;

	auto iter = adjustWaitCarList.begin();
	auto obj = *iter;
	
	if (curAdjustmentCar == nullptr){ //���� �������� ���� ���ٸ�
		adjustWaitCarList.erase(iter);
		curAdjustmentCar = obj;
		--curCarNumber;
	}
}

void CarPark::CheckAdjustCar(){
	if (curAdjustmentCar == nullptr) return;

	if (isFinishcurAdjustmentCar == true){
		isFinishcurAdjustmentCar = false;
		delete curAdjustmentCar;
		curAdjustmentCar = nullptr;
	}
	else{
		curAdjustmentCar->AddCurAdjustTime();//�������� ���� �ִٸ� ���� ��� ����
		if (curAdjustmentCar->GetCurAdjustTime() == adjustmentTime){
			isFinishcurAdjustmentCar = true;
		}
	}
}

//carList���� waitList�� �߰��� ���� �ִ��� Ȯ��
//���ÿ� �����ѳ� ���ð� ���� �ٿ��࿩�ϴ°� �����ϱ�
void CarPark::CheckCarListDestTime(list<Car*> & carList){
	if (carList.empty())
		return;

	for (auto& i = carList.begin(); i != carList.end();){
		auto iter = i;
		auto obj = *iter;

		if (obj->GetTotDestTimeSec() == curTime){ //���� Ÿ�ӿ� ���� �� �ִ� ������ ��� waitCarList�� �߰�
			i = carList.erase(iter);
			waitCarList.push_back(obj);
		}
		else
			++i;
	}
}

void CarPark::DoParkingCar(list<Car*> & carList, unordered_map< wstring, int>& carInfoData){
	//���� ���� ��ٸ��� �ִ� ����
	for (auto& i = carList.begin(); i != carList.end(); ++i){
		auto obj = *i;
		int interval = totOpenTimeSec - obj->GetTotDestTimeSec(); //���� ����� Car�� open�ð��� ����
		
		if (obj->GetTotDestTimeSec() >= totOpenTimeSec)
			break;
		else
			obj->SubDealyTimeToSpecialNumber(interval);
	}

	for (auto& i = carList.begin(); i != carList.end();){
		auto iter = i;
		auto obj = *iter;
		bool flag = false;

		if (obj->GetTotDestTimeSec() >= totOpenTimeSec)
			break;
		else {
			flag = true;
			i = carList.erase(iter);
			if (obj->GetDealyTime() >= 0){
				waitCarList.push_back(obj);
			}
		}
		if (flag == false)
			++i;
	}

	///////////////////////////////////////////////////////////////////////////
	curTime = totOpenTimeSec;
	 
	while (curTime != totCloseTimeSec + 1){
		CheckCarListDestTime(carList); //carList���� waitList�� �߰��� ���� ���� �߰�
		AddParkingCarList(carInfoData); //parkingList�� �ִ� parkingī���� �����ϴ� �ð� Ȯ�� (�̹� �ִ� ��Ű�� �����ð� + 1)
		CheckAdjutWaitCarList();//������ ����Ʈ�� �ִ� �͵� �� ������ �� �ִ� ���� ������ �ٷ� ���������
		CheckAdjustCar();//���� �����ϰ� �ִ� ���� update
		CheckWaitCarPossibleParking(carInfoData); //waitList���� ���� ������ ���� parkingList�� �߰�
		
		++curTime;
		if (curTime > totCloseTimeSec) break;
		SubWaitCarListDelayTime();//wait�� �ִ� car���� ���� ���ð��� �ϳ��� �ٿ��־�� ��
		CheckWaitCarListDelayTime(); //waitCar�� �ִ� �ֵ� �� �̹� ���� ���� �� ����
	}
}

//�ʸ� �ð����� ��ȯ
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

//��� ��� ����
void PrintFormSet(wstring & str){
	if (str.length() == 1){
		str = L"0" + str;
	}
}

//���
void Output(Result res){
	wofstream wofs;
	wofs.open(OUTPUT_FILE_NAME);
	wofs.imbue(locale(wofs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	wstring hour = to_wstring(res.fullParkingTime.hour);
	wstring minute = to_wstring(res.fullParkingTime.minute);
	wstring second = to_wstring(res.fullParkingTime.second);
	
	PrintFormSet(hour);
	PrintFormSet(minute);
	PrintFormSet(second);

	wofs << res.bustParkTime << endl << res.firstDestCarname << endl << hour << ":" << minute << ":" << second << endl << res.usingParkCarCount << endl;
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
	res.usingParkCarCount = carPark->GetUsingParkCarCount();
	SecToTime(res);
	Output(res);
	getchar();
	return 0;
}