#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "SnakeInit.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	// colsΪ��� linesΪ�߶� 
	system("mode con cols=120 lines=50"); 
	// ����̨�������� 
	SetConsoleTitle("̰����");
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // ���ع��
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursor_info);
	// ��ʼ������ 
	loop: InitParams();
	// ��ʼ���߿� 
	InitMainView();
	// ��ʼ������˵�� 
	InitIntruduction();
	// ��ʼ�������� 
	InitScore();
	// ��ʼ����
	InitSnake();
	ShowSnake();
	// ��ʼ����Ͷ��ʳ��
	InitFood();
	AddFood(); 
	
	
	while(1) {
		// �ȴ����� 
		OperateSnake(); 
		if(IsDead()) {
			CleanSnake();
			InitGameOver();
			int c;
			while(c = getch()) {
				if(c == 'y') {
					CleanSnake();
					system("cls");
					goto loop;
					break;
				}
				if(c == 'n') {
					CleanSnake();
					exit(0);
				}
			}
			
		}
		if (isOperation == 1) {
			ClearSnake();
			MoveSnake(); 
			if (isDigestion == 1) {
				AddScore();
				AddNode();
				AddFood();
				isDigestion = 0; 
			}
			
			ShowSnake(); // ��ʾ�� 
			// �����ٶ� 
			if (x_increment == 1 || x_increment == -1) {
				Sleep(SPEED);
			} else if (y_increment == 1 || y_increment == -1) {
				Sleep(SPEED * 1.75);
			}
			
		}
		
	} 

}
