#include <iostream>

using namespace std;

void HanoiTower(int n, char a, char b, char c){
	if (n == 1){
		printf("%c -> %c�� 1�� ���븦 �̵��Ѵ�\n", a, c);
		return;
	}

	HanoiTower(n - 1, a, c, b);
	printf("%c -> %c�� %d �� ���븦 �̵�\n", a, c, n);
	HanoiTower(n - 1, b, a, c);
}
int main(void){
	HanoiTower(3, 'a', 'b', 'c');
	getchar();
	return 0;
}