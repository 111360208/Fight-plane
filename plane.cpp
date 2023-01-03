#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <windows.h>
#include <time.h>

#define high 25
#define width 30
#define border 0 
#define blank 1
#define plane 2
#define bullet 3
#define enemy 4
#define destroy 5

int canvas[high+2][width+2];
int pos_h,pos_w;
int enemynum;
int interval;
int itv_move;
int itv_new;
int score; 
int IsOver;
