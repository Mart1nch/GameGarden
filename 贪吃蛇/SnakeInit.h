#define MAX_Y 40 // 最大 y 坐标 
#define MAX_X 60 // 最大 x 坐标 
#define LENGTH 3 // 蛇初始长度
#define SPEED 100 // 蛇的速度，sleep时间 


int direction; // 蛇运动方向 x轴为1， y轴为2 
int isOperation; // 是否正常运行 1运行 0暂停 
int score; // 本局分数
int max_score; // 最高纪录
int x_increment; // x轴方向增量
int y_increment; // y轴方向增量 
int length; // 蛇的长度
int isDigestion; // 是否已消化食物 
int border[MAX_X][MAX_Y]; // 边界

// 蛇的结构体
typedef struct SNAKE {
	int x;
	int y;
	int seq;
	char text[1];
	struct Snake *preNode;
	struct Snake *nextNode;
} Snake;
// 食物结构体 
typedef struct FOOD {
	int x; // x坐标 
	int y; // y坐标 
	char text[1]; // 食物符号 
} Food;
// 边框结构体 暂时不用 
//typedef struct FRAME {
//	int x_start; //左上角起点 x 坐标 
//	int y_start; //左上角起点 y 坐标 
//	int x_length; // x轴方向的长度 
//	int y_length; // y轴方向的长度 
//	char x_c; // x轴方向边框线的符号 
//	char y_c // y轴方向边框线的符号 
//};

Snake *snake; //蛇 
Snake *lastNode; // 蛇的最后一个节点 
Food food; //  食物

void InitParams(); // 初始化参数 
void InitMainView(); // 初始化界面
void InitSnake(); 
void AddNode(); // 吃完食物增加一个蛇的节点 
int IsDead(); // 判断蛇是否撞墙或咬到自己 
void InitIntruduction(); // 初始化规则、介绍 
void InitScore(); // 初始化分数牌 
void AddScore(); // 增加分数 
void Gotoxy(int x, int y); //定位光标到 (x, y) 
void InitGameOver(); // 游戏结束框初始化 
void CleanSnake(); // 清除蛇 
