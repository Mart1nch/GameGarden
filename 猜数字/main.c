#include "GuessNumber.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char *argv[]) {
	// 设置控制台大小 
	system("mode con cols=120 lines=30"); 
	// 设置控制台名称 
	SetConsoleTitle("猜数字小游戏");
	// 隐藏光标 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursor_info);
    
    while(1) {
    	int number = InitNumber();
    	int guessNumber;
    	
    	// 清屏 
    	system("cls");
    	printf("数字已生成，请输入您猜的数字：");
    	while (1) {
    		scanf("%d", &guessNumber);
	    	if (number > guessNumber) {
	    		printf("\n您猜测的数字与结果相比偏小，请重新猜：");
			} else if (number < guessNumber) {
				printf("\n您猜测的数字与结果相比偏大，请重新猜：");
			} else {
				printf("\n您猜对啦！正确结果就是：%d\n", number);
				break;
			}
		}
    	printf("是否继续？[y]是  [n]否：");
    	while (1) {
    		char flag;
    		flag = getch();
	    	if (flag == 'y') {
	    		break;
			} else if (flag == 'n') {
				exit(0);
			} else {
				printf("\n输入不符合规范。是否继续？[y]是  [n]否：");
			}
		}
    	
    	
	}
    return 0;
	
}
 
 
// 读取文件
void Demo() {
//	FILE *fp = NULL;
//	fp = fopen("C:/Users/matian/Desktop/text.txt", "r");
//	if (fp == NULL) {
//		int errnum;
//		errnum = errno;
//		perror("文件打开错误");
//		exit(-1);
//	}
//	
//	char s[1024], ch;
//	int i = 0;
//	while (!feof(fp)) {
//		fgets(s, 1024, fp);
//		printf("%s\n", s); 
//		Sleep(200);
//	} 
//	fclose(fp);
}
