#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//�ϥ�kbhit()�P�����U�˽L 
#include <windows.h>//��Ш禡 
#include <time.h>

#define high 25 //�e����
#define width 30 //�e���e
#define border 0 //���
#define blank 1 //�ť�
#define plane 2 //����
#define bullet 3 //�l�u
#define enemy 4 //�ľ�
#define destroy 5 //�R���аO

int canvas[high+2][width+2]; //�C�����������M�e�A�Y��+2 
int pos_h,pos_w; //������m
int enemynum; //�ľ��ƶq
int interval; //�P�ӭp���Ӽ����ɶ����j
int itv_move; //�ľ����ʪ��ɶ����j
int itv_new; //�ľ����s��z���ɶ����j
int score; //����
int IsOver; //�P�_�C���O�_����

void Startup(); //�C���ƭȪ�l��
void Show(); //�C��������X

int main(){
 	Startup(); //��l��
	while(IsOver){ //�C���j��
 		UpdateInput();
 		UpdateNormal();
		Show();
 	}
 	printf("\t\tGAME OVER!\n");
 	//Sleep(2500); //�Ȱ��C�����������]�@��^
 	system("pause");
 	return 0;
}
void Startup(){ //�C���ƭȪ�l��
 	IsOver=1;
 	score=0; //��l�Ƥ���
	for(int i=0;i<high+2;i++){ //��l�Ƶe��
	 	for(int j=0;j<width+2;j++){
	 		if(i==0 || i==high+1 ||j==0 || j==width+1)//�e�X������ 
	 			canvas[i][j]=border;
	 	else canvas[i][j]=blank;//�e�X�ťհϰ� 
	 	}
	}
	pos_h=high/2; //��l�ƭ����ݪ��y��
 	pos_w=width/2; //��l�ƭ��������y��
	canvas[pos_h][pos_w]=plane; //��l�ƭ�����m(�������b������)
	enemynum=10; //�ľ���s���ƶq
	srand(time(NULL));
	interval=4; //��}�l�C�������y 
	itv_move=5; //��l�Ƽľ����ʮɶ����j
	itv_new =40; //��l�Ƽľ��X�{���j 
}
void Show(){ //�C���e����X
	HideCursor(); //���ô��
 	gotoxy(0,0); //����Ц^����I�b��X�e���A���M�|�@��@��g�U�h 
 	for(int i=0;i<high+2;i++){
 		for(int j=0;j<width+2;j++){
 			if( canvas[i][j] == plane ) //��e��m��������m
				printf("*");
 			else if( canvas[i][j] == bullet ) //��e��m���l�u��m
 				printf(".");
 		
 			else if( canvas[i][j] == enemy ) //��e��m���ľ���m
 				printf("@");
 
 			else if( canvas[i][j] == border ) //��e��m�����
 				printf("+");
 				
 			else if( canvas[i][j] == blank ) //��e��m�L���A�B�b��ɤ�
 				printf(" ");
 				
 			else if( canvas[i][j] == destroy ) //��e��m�L���A�B�b��ɤ�
 				printf("x");
 		}
 		printf("\n");
 	}
 	printf("W(�W),S(�U),A(��),D(�k)\n");
 	printf("\n�o���G%d",score);
}
