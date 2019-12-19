#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "SnakeInit.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	// cols为宽度 lines为高度 
	system("mode con cols=120 lines=50"); 
	// 控制台窗口命名 
	SetConsoleTitle("贪吃蛇");
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // 隐藏光标
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursor_info);
	// 初始化参数 
	loop: InitParams();
	// 初始化边框 
	InitMainView();
	// 初始化介绍说明 
	InitIntruduction();
	// 初始化分数牌 
	InitScore();
	// 初始化蛇
	InitSnake();
	ShowSnake();
	// 初始化并投放食物
	InitFood();
	AddFood(); 
	
	
	while(1) {
		// 等待按键 
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
			
			ShowSnake(); // 显示蛇 
			// 控制速度 
			if (x_increment == 1 || x_increment == -1) {
				Sleep(SPEED);
			} else if (y_increment == 1 || y_increment == -1) {
				Sleep(SPEED * 1.75);
			}
			
		}
		
	} 

}
