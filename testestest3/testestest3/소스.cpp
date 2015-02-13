#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <codecvt>

using namespace std;
int main(void){
	wifstream wifs;
	wstring txtline;
	
	int c = 0;

	wifs.open("data0.ini");
	if (!wifs.is_open())
	{
		wcerr << L"Unable to open file" << endl;
	}

	wifs.imbue(locale(wifs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
	while (true)
		wifs >> txtline;
		//wcout << ++c << L'\t' << txtline << L'\n';
	wcout << endl;
	
	getchar();
	return 0;
}