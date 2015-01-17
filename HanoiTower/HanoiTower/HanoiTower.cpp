#include <iostream>

using namespace std;

void HanoiTower(int n, char a, char b, char c){
	if (n == 1){
		printf("%c -> %c로 1번 막대를 이동한다\n", a, c);
		return;
	}

	HanoiTower(n - 1, a, c, b);
	printf("%c -> %c로 %d 번 막대를 이동\n", a, c, n);
	HanoiTower(n - 1, b, a, c);
}
int main(void){
	HanoiTower(3, 'a', 'b', 'c');
	getchar();
	return 0;
}