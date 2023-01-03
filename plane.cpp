#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//使用kbhit()感測按下檢盤 
#include <windows.h>//游標函式 
#include <time.h>

#define high 25 //畫布高
#define width 30 //畫布寬
#define border 0 //邊界
#define blank 1 //空白
#define plane 2 //飛機
#define bullet 3 //子彈
#define enemy 4 //敵機
#define destroy 5 //摧毀標記

int canvas[high+2][width+2]; //遊戲場景的高和寬，頭尾+2 
int pos_h,pos_w; //飛機位置
int enemynum; //敵機數量
int interval; //同個計次來模擬時間間隔
int itv_move; //敵機移動的時間間隔
int itv_new; //敵機重新整理的時間間隔
int score; //分數
int IsOver; //判斷遊戲是否結束

void Startup(); //遊戲數值初始化
void Show(); //遊戲介面輸出

int main(){
 	Startup(); //初始化
	while(IsOver){ //遊戲迴圈
 		UpdateInput();
 		UpdateNormal();
		Show();
 	}
 	printf("\t\tGAME OVER!\n");
 	//Sleep(2500); //暫停遊戲結束介面（毫秒）
 	system("pause");
 	return 0;
}
void Startup(){ //遊戲數值初始化
 	IsOver=1;
 	score=0; //初始化分數
	for(int i=0;i<high+2;i++){ //初始化畫布
	 	for(int j=0;j<width+2;j++){
	 		if(i==0 || i==high+1 ||j==0 || j==width+1)//畫出方形邊界 
	 			canvas[i][j]=border;
	 	else canvas[i][j]=blank;//畫出空白區域 
	 	}
	}
	pos_h=high/2; //初始化飛機豎直座標
 	pos_w=width/2; //初始化飛機水平座標
	canvas[pos_h][pos_w]=plane; //初始化飛機位置(讓飛機在正中間)
	enemynum=10; //敵機更新的數量
	srand(time(NULL));
	interval=4; //剛開始遊戲的停頓 
	itv_move=5; //初始化敵機移動時間間隔
	itv_new =40; //初始化敵機出現間隔 
}
void Show(){ //遊戲畫面輸出
	HideCursor(); //隱藏游標
 	gotoxy(0,0); //讓游標回到原點在輸出畫面，不然會一行一行寫下去 
 	for(int i=0;i<high+2;i++){
 		for(int j=0;j<width+2;j++){
 			if( canvas[i][j] == plane ) //當前位置為飛機位置
				printf("*");
 			else if( canvas[i][j] == bullet ) //當前位置為子彈位置
 				printf(".");
 		
 			else if( canvas[i][j] == enemy ) //當前位置為敵機位置
 				printf("@");
 
 			else if( canvas[i][j] == border ) //當前位置為邊界
 				printf("+");
 				
 			else if( canvas[i][j] == blank ) //當前位置無物，且在邊界內
 				printf(" ");
 				
 			else if( canvas[i][j] == destroy ) //當前位置無物，且在邊界內
 				printf("x");
 		}
 		printf("\n");
 	}
 	printf("W(上),S(下),A(左),D(右)\n");
 	printf("\n得分：%d",score);
}
