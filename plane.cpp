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
void Show(); //�e����X
void UpdateInput(); //����W�U���k�O�_�y���Y���M�o�g�l�u 
void UpdateNormal(); //�e����s(�������쭸��or�g�쭸��) 
void HideCursor();
void gotoxy(int x,int y);

int main(){
 	Startup(); //��l��
	while(IsOver){ //�C���j��A IsOver=0��game over 
 		UpdateInput();//����W�U���k�O�_�y���Y���M�o�g�l�u 
 		UpdateNormal();//�e����s(�������쭸��or�g�쭸��) 
		Show();//�e����X
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


void UpdateInput(){ //����W�U���k�O�_�y���Y���M�o�g�l�u 
	char key_W=GetKeyState('W'),//�ʴ� W ��O�_���U
	key_S=GetKeyState('S'),//�ʴ� S ��O�_���U
	key_A=GetKeyState('A'),//�ʴ� A ��O�_���U
	key_D=GetKeyState('D'),//�ʴ� D ��O�_���U
	key_attack=GetKeyState(' '); //�ʴ� �Ů� ��O�_���U
 	if(kbhit()){ //������U��
 		if(key_W<0){ //����U W ��A�W�� 
 			if(pos_h>1){//�p�G���b�̳��� �A�~�i�H�W�� 
 				canvas[pos_h][pos_w]=blank;
 				if(canvas[pos_h-1][pos_w] == enemy){ //�U�Ӧ�m�O�ľ��A����
 					canvas[pos_h-1][pos_w]= destroy;
 					IsOver=0;
 				}
 				else canvas[--pos_h][pos_w]=plane;//���W�ƭȴ�֡A�ҥH--pos_h 
 			}
 		}
 		if(key_S<0){ //����U S ��A�U��
 			if(pos_h<high){
 				canvas[pos_h][pos_w]=blank;
	 			if(canvas[pos_h+1][pos_w] == enemy){ //�U�Ӧ�m�O�ľ��A����
 					canvas[pos_h+1][pos_w]= destroy;
 					IsOver=0;
 				}
 				else canvas[++pos_h][pos_w]=plane;
 			}
 		}
 		if(key_A<0){ //����U A ��A����
	 		if(pos_w>1){
	 			canvas[pos_h][pos_w]=blank;
	 			if(canvas[pos_h][pos_w-1] == enemy){ //�U�Ӧ�m�O�ľ��A����
	 				canvas[pos_h][pos_w-1]= destroy;
	 				IsOver=0;
	 			}
	 			else canvas[pos_h][--pos_w]=plane;
	 		}
 		}
 		if(key_D<0){ //����U D ��A�k��
 			if(pos_w<width){
 				canvas[pos_h][pos_w]=blank;
 				if(canvas[pos_h][pos_w+1] == enemy){ //�U�Ӧ�m�O�ľ��A����
				 	canvas[pos_h][pos_w+1]= destroy;
				 	IsOver=0;
 				}
 				else canvas[pos_h][++pos_w]=plane;
 			}
 		}
 		if(key_attack<0&&pos_h!=1) //����U�Ů���A�o�g�l�u
 			canvas[pos_h-1][pos_w]=bullet;	
 	}
}


void UpdateNormal(){ //�e����s(�������쭸��or�g�쭸��) 
 	int temp[high+2][width+2];//�]��i�e���洫�A�ק�e�� 
 	for(int i=1;i<=high;i++){
 		for(int j=1;j<=width;j++){
 			temp[i][j]=canvas[i][j];
 		}
 	}
 	for(int i=1;i<=high;i++){ 
 		for(int j=1;j<=width;j++){
 			if(temp[i][j]==enemy && interval%itv_move==0){ //��e�ľ���m
 				canvas[i][j]=blank;
 				if(temp[i+1][j]==bullet){ //�U�����l�u�A�ľ��Q����
 					canvas[i+1][j]=blank;//�U�@�i�e����ܪť� 
 					score++;
 				}
 				else if(i<high)
 					canvas[i+1][j]=enemy;
 
 				if(i+1==pos_h&&j==pos_w){ //�U���������A���a�����Q����
 					canvas[i+1][j]=destroy;//�U�@�i�e����ܤe�e 
 					IsOver=0;
 				}
 			}
 			if(temp[i][j]==bullet){ //��e�l�u��m
 				canvas[i][j]=blank;
 				if(temp[i-1][j]==enemy){ //�U�Ӧ�m�O�ľ��A�ľ��Q����
 					canvas[i-1][j]=blank;//�U�@�i�e����ܪť� 
 					score++;
 				}
 				else if(i>1)
 					canvas[i-1][j]=bullet;
 			}
 		}
 	}
 	if(interval%itv_new==0) //��n��ɶ����j
 		for(int i=0;i<enemynum;i++) //�s�W�ľ��s
 			canvas[rand()%2+1][rand()%width+1]=enemy;
 
 	if(interval<=100) //�ɶ����j�p��
 		interval++;
 
 	else //�ɶ����j�p���M�s
 		interval=0;
 
}


void gotoxy(int x,int y){ //���ʴ�Ъ��禡 
 COORD pos;
 pos.X=x;
 pos.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
 
void HideCursor(){ //���ô�Ъ��禡�A���ϥΦ��禡���ܷ|�y����Ф@���A�]�A�ɭP�ݰ_�Ӧ��� "|"�b�{�{ 
 /*CONSOLE_CURSOR_INFO cursor;
 cursor.bVisible = FALSE;
 cursor.dwSize = sizeof(cursor);
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorInfo(handle,&cursor);
 */
  CONSOLE_CURSOR_INFO cursor={1,0};//�ĤG��0������ô�� 
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
}
