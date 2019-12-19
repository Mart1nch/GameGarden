#define MAX_Y 40 // ��� y ���� 
#define MAX_X 60 // ��� x ���� 
#define LENGTH 3 // �߳�ʼ����
#define SPEED 100 // �ߵ��ٶȣ�sleepʱ�� 


int direction; // ���˶����� x��Ϊ1�� y��Ϊ2 
int isOperation; // �Ƿ��������� 1���� 0��ͣ 
int score; // ���ַ���
int max_score; // ��߼�¼
int x_increment; // x�᷽������
int y_increment; // y�᷽������ 
int length; // �ߵĳ���
int isDigestion; // �Ƿ�������ʳ�� 
int border[MAX_X][MAX_Y]; // �߽�

// �ߵĽṹ��
typedef struct SNAKE {
	int x;
	int y;
	int seq;
	char text[1];
	struct Snake *preNode;
	struct Snake *nextNode;
} Snake;
// ʳ��ṹ�� 
typedef struct FOOD {
	int x; // x���� 
	int y; // y���� 
	char text[1]; // ʳ����� 
} Food;
// �߿�ṹ�� ��ʱ���� 
//typedef struct FRAME {
//	int x_start; //���Ͻ���� x ���� 
//	int y_start; //���Ͻ���� y ���� 
//	int x_length; // x�᷽��ĳ��� 
//	int y_length; // y�᷽��ĳ��� 
//	char x_c; // x�᷽��߿��ߵķ��� 
//	char y_c // y�᷽��߿��ߵķ��� 
//};

Snake *snake; //�� 
Snake *lastNode; // �ߵ����һ���ڵ� 
Food food; //  ʳ��

void InitParams(); // ��ʼ������ 
void InitMainView(); // ��ʼ������
void InitSnake(); 
void AddNode(); // ����ʳ������һ���ߵĽڵ� 
int IsDead(); // �ж����Ƿ�ײǽ��ҧ���Լ� 
void InitIntruduction(); // ��ʼ�����򡢽��� 
void InitScore(); // ��ʼ�������� 
void AddScore(); // ���ӷ��� 
void Gotoxy(int x, int y); //��λ��굽 (x, y) 
void InitGameOver(); // ��Ϸ�������ʼ�� 
void CleanSnake(); // ����� 
