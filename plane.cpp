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
void Show(); //畫面輸出
void UpdateInput(); //控制上下左右是否造成墜毀和發射子彈 
void UpdateNormal(); //畫面更新(正面撞到飛機or射到飛機) 
void HideCursor();
void gotoxy(int x,int y);

int main(){
 	Startup(); //初始化
	while(IsOver){ //遊戲迴圈， IsOver=0時game over 
 		UpdateInput();//控制上下左右是否造成墜毀和發射子彈 
 		UpdateNormal();//畫面更新(正面撞到飛機or射到飛機) 
		Show();//畫面輸出
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


void UpdateInput(){ //控制上下左右是否造成墜毀和發射子彈 
	char key_W=GetKeyState('W'),//監測 W 鍵是否按下
	key_S=GetKeyState('S'),//監測 S 鍵是否按下
	key_A=GetKeyState('A'),//監測 A 鍵是否按下
	key_D=GetKeyState('D'),//監測 D 鍵是否按下
	key_attack=GetKeyState(' '); //監測 空格 鍵是否按下
 	if(kbhit()){ //當有鍵按下時
 		if(key_W<0){ //當按下 W 鍵，上移 
 			if(pos_h>1){//如果不在最頂端 ，才可以上移 
 				canvas[pos_h][pos_w]=blank;
 				if(canvas[pos_h-1][pos_w] == enemy){ //下個位置是敵機，撞毀
 					canvas[pos_h-1][pos_w]= destroy;
 					IsOver=0;
 				}
 				else canvas[--pos_h][pos_w]=plane;//往上數值減少，所以--pos_h 
 			}
 		}
 		if(key_S<0){ //當按下 S 鍵，下移
 			if(pos_h<high){
 				canvas[pos_h][pos_w]=blank;
	 			if(canvas[pos_h+1][pos_w] == enemy){ //下個位置是敵機，撞毀
 					canvas[pos_h+1][pos_w]= destroy;
 					IsOver=0;
 				}
 				else canvas[++pos_h][pos_w]=plane;
 			}
 		}
 		if(key_A<0){ //當按下 A 鍵，左移
	 		if(pos_w>1){
	 			canvas[pos_h][pos_w]=blank;
	 			if(canvas[pos_h][pos_w-1] == enemy){ //下個位置是敵機，撞毀
	 				canvas[pos_h][pos_w-1]= destroy;
	 				IsOver=0;
	 			}
	 			else canvas[pos_h][--pos_w]=plane;
	 		}
 		}
 		if(key_D<0){ //當按下 D 鍵，右移
 			if(pos_w<width){
 				canvas[pos_h][pos_w]=blank;
 				if(canvas[pos_h][pos_w+1] == enemy){ //下個位置是敵機，撞毀
				 	canvas[pos_h][pos_w+1]= destroy;
				 	IsOver=0;
 				}
 				else canvas[pos_h][++pos_w]=plane;
 			}
 		}
 		if(key_attack<0&&pos_h!=1) //當按下空格鍵，發射子彈
 			canvas[pos_h-1][pos_w]=bullet;	
 	}
}


void UpdateNormal(){ //畫面更新(正面撞到飛機or射到飛機) 
 	int temp[high+2][width+2];//設兩張畫面交換，修改畫面 
 	for(int i=1;i<=high;i++){
 		for(int j=1;j<=width;j++){
 			temp[i][j]=canvas[i][j];
 		}
 	}
 	for(int i=1;i<=high;i++){ 
 		for(int j=1;j<=width;j++){
 			if(temp[i][j]==enemy && interval%itv_move==0){ //當前敵機位置
 				canvas[i][j]=blank;
 				if(temp[i+1][j]==bullet){ //下面為子彈，敵機被擊中
 					canvas[i+1][j]=blank;//下一張畫面顯示空白 
 					score++;
 				}
 				else if(i<high)
 					canvas[i+1][j]=enemy;
 
 				if(i+1==pos_h&&j==pos_w){ //下面為飛機，玩家飛機被撞毀
 					canvas[i+1][j]=destroy;//下一張畫面顯示叉叉 
 					IsOver=0;
 				}
 			}
 			if(temp[i][j]==bullet){ //當前子彈位置
 				canvas[i][j]=blank;
 				if(temp[i-1][j]==enemy){ //下個位置是敵機，敵機被擊毀
 					canvas[i-1][j]=blank;//下一張畫面顯示空白 
 					score++;
 				}
 				else if(i>1)
 					canvas[i-1][j]=bullet;
 			}
 		}
 	}
 	if(interval%itv_new==0) //剛好到時間間隔
 		for(int i=0;i<enemynum;i++) //新增敵機群
 			canvas[rand()%2+1][rand()%width+1]=enemy;
 
 	if(interval<=100) //時間間隔計次
 		interval++;
 
 	else //時間間隔計次清零
 		interval=0;
 
}


void gotoxy(int x,int y){ //移動游標的函式 
 COORD pos;
 pos.X=x;
 pos.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
 
void HideCursor(){ //隱藏游標的函式，不使用此函式的話會造成游標一直再跑，導致看起來有個 "|"在閃爍 
 /*CONSOLE_CURSOR_INFO cursor;
 cursor.bVisible = FALSE;
 cursor.dwSize = sizeof(cursor);
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorInfo(handle,&cursor);
 */
  CONSOLE_CURSOR_INFO cursor={1,0};//第二個0表示隱藏游標 
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
}
