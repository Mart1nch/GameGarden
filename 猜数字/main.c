#include "GuessNumber.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char *argv[]) {
	// ���ÿ���̨��С 
	system("mode con cols=120 lines=30"); 
	// ���ÿ���̨���� 
	SetConsoleTitle("������С��Ϸ");
	// ���ع�� 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursor_info);
    
    while(1) {
    	int number = InitNumber();
    	int guessNumber;
    	
    	// ���� 
    	system("cls");
    	printf("���������ɣ����������µ����֣�");
    	while (1) {
    		scanf("%d", &guessNumber);
	    	if (number > guessNumber) {
	    		printf("\n���²�������������ƫС�������²£�");
			} else if (number < guessNumber) {
				printf("\n���²�������������ƫ�������²£�");
			} else {
				printf("\n���¶�������ȷ������ǣ�%d\n", number);
				break;
			}
		}
    	printf("�Ƿ������[y]��  [n]��");
    	while (1) {
    		char flag;
    		flag = getch();
	    	if (flag == 'y') {
	    		break;
			} else if (flag == 'n') {
				exit(0);
			} else {
				printf("\n���벻���Ϲ淶���Ƿ������[y]��  [n]��");
			}
		}
    	
    	
	}
    return 0;
	
}
 
 
// ��ȡ�ļ�
void Demo() {
//	FILE *fp = NULL;
//	fp = fopen("C:/Users/matian/Desktop/text.txt", "r");
//	if (fp == NULL) {
//		int errnum;
//		errnum = errno;
//		perror("�ļ��򿪴���");
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
