#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "SnakeInit.h"


// �ƶ���� 
void Gotoxy(int x, int y)
{
	//  COORD�õ��� Windows.h ͷ�ļ� 
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/*
	���߿����¶��Ǳ߿������ 
	x_start ���� x ���� 
	y_start ���� y ����
	x_length x�᷽��ĳ��� 
	y_length y�᷽��ĳ��� 
	x_c x�᷽��ķ��� 
	y_c y�᷽��ķ��� 
*/
void InitBorder(int x_start, int y_start, int x_length, int y_length, char x_c, char y_c) {
	int i;
	// ƽ���� Y ���
	for (i = 0; i < y_length + 1; i++) {
		Gotoxy(x_start, y_start + i);
		printf("%c", y_c);
		Gotoxy(x_start + x_length, y_start + i);
		printf("%c", y_c);
	}
	// ƽ���� X ��� 
	for (i = 0; i < x_length + 1; i++) {
		// Ϊ�����ۣ���һ����һ�� "." 
		if (i % 2 == 0) {
			Gotoxy(x_start + i, y_start);
			printf("%c", x_c);
			Gotoxy(x_start + i, y_start + y_length	);
			printf("%c", x_c);
		} 
		
	}
	
} 



// ��ʼ����
void InitSnake() {
	length = LENGTH;
	 
	snake = (Snake *) malloc(sizeof(Snake));
	snake->preNode = NULL;
	snake->nextNode = NULL;
	// ��ʼ�����м� 
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

// ����ߵ����һ���ڵ���ƶ��켣
void ClearSnake() {
	Gotoxy(lastNode->x, lastNode->y);
	printf(" ");
} 

// ������ʾ��
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

// �����ƶ���
//void MoveSnake() {
//	// ��ʳ�� 
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
	// ��ʳ�ͷ������ʳ�������ˣ�����Ҫβ������ʳ�������겢����һ��
	// ������Ϊ�˿���Ͷ��ʳ������ص���������Ͷ�� 
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


// ������ 
void OperateSnake() {
	if (kbhit() == 0) {
		// û�а��¼� 
		return;
	}
	char key = getch();
	switch (key) {
		case 'w':// ��
		case 'W':
			if (y_increment == 1) {
				return;
			}
			x_increment = 0;
			y_increment = -1;
			direction = 2; 
			isOperation = 1;
			break;
		case 'a':// �� 
		case 'A':
			if (x_increment == 1) {
				return;
			}
			x_increment = -1;
			y_increment = 0;
			direction = 1;
			isOperation = 1;
			break;
		case 's': // �� 
		case 'S':
			if (y_increment == -1) {
				return;
			}
			x_increment = 0;
			y_increment = 1;
			direction = 2;
			isOperation = 1;
			break;
		case 'd': // �� 
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

// �ж����Ƿ�ײ����ǽ��Ե����Լ� 
int IsDead() {
	int result = 0;
	// ײǽ 
	if (snake->x == 0 || snake->x == MAX_X + 2 || snake->y == 0 || snake->y == MAX_Y + 2) {
		result = 1;
		return result;
	}
	int x = snake->x + x_increment;
	int y = snake->y + y_increment;
	Snake *nextNode = snake;
	while (nextNode->nextNode != NULL) {
		nextNode = nextNode->nextNode; 
		// �Ե��Լ� 
		if (x == nextNode->x && y == nextNode->y) {
			result = 1;
			break;
		}
		
	}
	nextNode = NULL;
	return result;
}

// ��ʼ��ʳ��
void InitFood() {
	strcpy(food.text, "#");
} 

// Ͷ��ʳ��
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

// ���Ͷ�ŵ��Ƿ����߽ڵ���
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



// ��ʳ�����ӽڵ� 
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




// ��ʼ������
void InitMainView() {
	// ���Ͽ򣬼�¼���� 
	InitBorder(MAX_X + 10, 0, 45, 5, '.', '.');
//	// ���¿� 
	InitBorder(MAX_X + 10, 10, 45, 32, '.', '.');
	// ���� 
	InitBorder(0, 0, MAX_X + 2, MAX_Y + 2, '.', '.');
	
} 

// ����˵��
void InitIntruduction() {
	int i;
	Gotoxy(MAX_X + 10 + 1, 10 + 1);
	printf("����˵����\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 2);
	printf("����ϷΪ̰����С��Ϸ\n"); 
	Gotoxy(MAX_X + 10 + 1, 10 + 3);
	printf("���Ҹ�������̰����С��Ϸ�淨��������\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 4);
	printf("Ҫע����ǣ�\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 5);
	printf("W/A/S/D Ϊ�����ߵķ���\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 6);
	printf("P ��ͣ\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 7);
	printf("������ͣ�� W/A/S/D ������һ��������Ϸ\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 8);
	printf("��Ȼ��Ҳ���Զ�һ�����Ըе���ָ��һ��������\n");
	Gotoxy(MAX_X + 10 + 1, 10 + 8);
	printf("Ҳ�ǿ�����ͣ��\n");
	 
} 

// ������¼�Ƴ�ʼ�� 
void InitScore() {
	Gotoxy(MAX_X + 10 + 1, 1);
	printf("����ǰ�ķ���Ϊ��%d\n", score);
} 

// ��¼����
void AddScore() {
	score++;
	Gotoxy(MAX_X + 10 + 1, 1);
	printf("����ǰ�ķ���Ϊ��%d\n", score);
} 

// ��ʼ����Ϸ


// ��ʼ������
void InitParams() {
	x_increment = -1; 
	score = 0;
	isOperation = 0; 
	isDigestion = 0;
}

// ��Ϸ������ʾ 
void InitGameOver() {
	InitBorder(20, 15, 20, 10, '.', '.');
	Gotoxy(21, 16);
	printf("������Ϸ�ѽ���\n");
	Gotoxy(21, 17);
	printf("��ǰ������%d\n", score);
	Gotoxy(21, 19);
	printf("�Ƿ����¿�ʼ��\n");
	
	Gotoxy(21, 20);
	printf("[y]�� [n]��\n");
	
}
// ������
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
 
