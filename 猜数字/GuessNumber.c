#include "GuessNumber.h"


void Gotoxy(int x, int y) {
	//  COORD用到了 Windows.h 头文件 
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}


int InitNumber() {
	srand((unsigned)time(NULL) * 10);
	int number = rand() % 100;
	return number;
}
