#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "SnakeInit.h"


// 移动光标 
void Gotoxy(int x, int y)
{
	//  COORD用到了 Windows.h 头文件 
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/*
	画边框，以下都是边框的属性 
	x_start 起点的 x 坐标 
	y_start 起点的 y 坐标
	x_length x轴方向的长度 
	y_length y轴方向的长度 
	x_c x轴方向的符号 
	y_c y轴方向的符号 
*/
void InitBorder(int x_start, int y_start, int x_length, int y_length, char x_c, char y_c) {
	int i;
	// 平行于 Y 轴的
	for (i = 0; i < y_length + 1; i++) {
		Gotoxy(x_start, y_start + i);
		printf("%c", y_c);
		Gotoxy(x_start + x_length, y_start + i);
		printf("%c", y_c);
	}
	// 平行于 X 轴的 
	for (i = 0; i < x_length + 1; i++) {
		// 为了美观，隔一个画一个 "." 
		if (i % 2 == 0) {
			Gotoxy(x_start + i, y_start);
			printf("%c", x_c);
			Gotoxy(x_start + i, y_start + y_length	);
			printf("%c", x_c);
		} 
		
	}
	
} 



// 初始化蛇
void InitSnake() {
	length = LENGTH;
	 
	snake = (Snake *) malloc(sizeof(Snake));
	snake->preNode = NULL;
	snake->nextNode = NULL;
	// 初始化在中间 
	snake->x = MAX_Y / 2 ;
	snake->y = MAX_X / 2 ;
	snake->seq = 1;
	strcpy(snake->text, "O");
	
	int i;
	Snake *pre = snake;
	for (i = 0; i < length - 1; i++) {
		Snake *next = (Snake *) malloc(sizeof(Snake));
		next->preNode = pre;
		next->nextNode = NULL;
		next->x = pre->x + 1;
		next->y = pre->y;
		next->seq = pre->seq + 1;
		pre->nextNode = next;  
		strcpy(next->text, "O");
		pre = next;
	}
	lastNode = pre;
	pre = NULL; 
} 

// 清除蛇的最后一个节点的移动轨迹
void ClearSnake() {
	Gotoxy(lastNode->x, lastNode->y);
	printf(" ");
} 

// 界面显示蛇
void ShowSnake() {
	Snake *snakeNode = snake;
	while (snakeNode->nextNode != NULL) {
		Gotoxy(snakeNode->x, snakeNode->y);
		printf("%s", snakeNode->text);
		snakeNode = snakeNode->nextNode;
	}
	Gotoxy(snakeNode->x, snakeNode->y);
	printf("%s", snakeNode->text);
	snakeNode = NULL;
} 

// 界面移动蛇
//void MoveSnake() {
//	// 吃食物 
//	if (lastNode->x == food.x && lastNode->y == food.y) {
//		isDigestion = 1;
//	}
//	Snake *node = lastNode;
//	Snake *temp = NULL;
//	while (node->preNode != NULL) {
//		temp = node->preNode;
//		node->x = temp->x;
//		node->y = temp->y;
//		node = node->preNode;
//	}
//	node->x += x_increment;
//	node->y += y_increment;
//} 

void MoveSnake() {
	// 吃食物，头碰到了食物就算吃了，但是要尾巴碰到食物才算吃完并增加一节
	// 这样是为了快速投放食物而不必等消化了再投放 
	if (snake->x == food.x && snake->y == food.y) {
		isDigestion = 1;
	}
	Snake *node = lastNode;
	Snake *temp = NULL;
	while (node->preNode != NULL) {
		temp = node->preNode;
		node->x = temp->x;
		node->y = temp->y;
		node = node->preNode;
	}
	node->x += x_increment;
	node->y += y_increment;
	node = NULL;
	temp = NULL;
} 


// 操纵蛇 
void OperateSnake() {
	if (kbhit() == 0) {
		// 没有按下键 
		return;
	}
	char key = getch();
	switch (key) {
		case 'w':// 上
		case 'W':
			if (y_increment == 1) {
				return;
			}
			x_increment = 0;
			y_increment = -1;
			direction = 2; 
			isOperation = 1;
			break;
		case 'a':// 左 
		case 'A':
			if (x_increment == 1) {
				return;
			}
			x_increment = -1;
			y_increment = 0;
			direction = 1;
			isOperation = 1;
			break;
		case 's': // 下 
		case 'S':
			if (y_increment == -1) {
				return;
			}
			x_increment = 0;
			y_increment = 1;
			direction = 2;
			isOperation = 1;
			break;
		case 'd': // 右 
		case 'D':
			if (x_increment == -1) {
				return;
			}
			x_increment = 1;
			y_increment = 0;
			direction = 1;
			isOperation = 1;
			break;
		case 'p':
		case 'P':
			if (isOperation == 0) {
				isOperation = 1;
			}
			if (isOperation == 1) {
				isOperation = 0;
			}
			break;
		default :
			break; 
	}
}

// 判断蛇是否撞到了墙或吃到了自己 
int IsDead() {
	int result = 0;
	// 撞墙 
	if (snake->x == 0 || snake->x == MAX_X + 2 || snake->y == 0 || snake->y == MAX_Y + 2) {
		result = 1;
		return result;
	}
	int x = snake->x + x_increment;
	int y = snake->y + y_increment;
	Snake *nextNode = snake;
	while (nextNode->nextNode != NULL) {
		nextNode = nextNode->nextNode; 
		// 吃到自己 
		if (x == nextNode->x && y == nextNode->y) {
			result = 1;
			break;
		}
		
	}
	nextNode = NULL;
	return result;
}

// 初始化食物
void InitFood() {
	strcpy(food.text, "#");
} 

// 投放食物
void AddFood() {
	int x, y;
	do {
		x = rand() % (MAX_X);
		y = rand() % (MAX_Y);
	} while (CheakFoodPosition(x, y));

	food.x = x;
	food.y = y;
	Gotoxy(x, y);
	printf("%s", food.text);
}

// 检查投放点是否在蛇节点上
int CheakFoodPosition(int x, int y) {
	int result = 0;
	Snake *node = snake;
	while (node->nextNode != NULL) {
		if (x == node->x && y == node->y) {
			result = 1;
			break;
		}
		node = node->nextNode;
	}
	
	node = NULL;
	return result;
}



// 吃食物增加节点 
void AddNode() {
	Snake *node = (Snake *)malloc(sizeof(Snake));
	node->x = food.x;
	node->y = food.y;
	strcpy(node->text, "O");
	node->seq = lastNode->seq + 1;
	node->preNode = lastNode;
	lastNode->nextNode = node;
	node->nextNode = NULL;
	lastNode = node;
} 




// 初始化界面
void InitMainView() {
	// 右上框，记录排名 
	InitBorder(MAX_X + 10, 0, 45, 5, '.', '.');
//	// 右下框 
	InitBorder(MAX_X + 10, 10, 45, 32, '.', '.');
	// 主框 
	InitBorder(0, 0, MAX_X + 2, MAX_Y + 2, '.', '.');
	
} 

// 规则说明
void InitIntruduction() {
	int i;
	Gotoxy(MAX_X + 10 + 1, 10 + 1);
	printf("规则说明：\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 2);
	printf("此游戏为贪吃蛇小游戏\n"); 
	Gotoxy(MAX_X + 10 + 1, 10 + 3);
	printf("并且跟其他的贪吃蛇小游戏玩法并无区别\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 4);
	printf("要注意的是：\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 5);
	printf("W/A/S/D 为控制蛇的方向\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 6);
	printf("P 暂停\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 7);
	printf("按下暂停后按 W/A/S/D 中任意一键继续游戏\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 8);
	printf("当然你也可以动一动你性感的手指点一下鼠标左键\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 8);
	printf("也是可以暂停的\n");
	 
} 

// 分数记录牌初始化 
void InitScore() {
	Gotoxy(MAX_X + 10 + 1, 1);
	printf("您当前的分数为：%d\n", score);
} 

// 记录分数
void AddScore() {
	score++;
	Gotoxy(MAX_X + 10 + 1, 1);
	printf("您当前的分数为：%d\n", score);
} 

// 初始化游戏


// 初始化参数
void InitParams() {
	x_increment = -1; 
	score = 0;
	isOperation = 0; 
	isDigestion = 0;
}

// 游戏结束提示 
void InitGameOver() {
	InitBorder(20, 15, 20, 10, '.', '.');
	Gotoxy(21, 16);
	printf("您的游戏已结束\n");
	Gotoxy(21, 17);
	printf("当前分数：%d\n", score);
	Gotoxy(21, 19);
	printf("是否重新开始：\n");
	
	Gotoxy(21, 20);
	printf("[y]是 [n]否\n");
	
}
// 回收蛇
void CleanSnake() {
	Snake *n1 = snake;
	Snake *n2 = snake;
	while (n1->nextNode != NULL) {
		n1 = n1->nextNode;
		n2 = NULL;
		n2 = n1;
	}
	n1 = NULL;
	n2 = NULL;
} 
 
