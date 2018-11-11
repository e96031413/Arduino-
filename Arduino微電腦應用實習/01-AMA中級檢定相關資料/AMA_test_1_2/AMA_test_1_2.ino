#include "config.h"
char mode=0		; // 工作模式, 預設為0
byte Seg_Pin[] = {seg_g, seg_f, seg_e, seg_d, seg_c, seg_b, seg_a};	// 宣告七段顯示器接腳陣列 
int i;									// for 迴圈的計數變數
byte  S_seg[3][7] = { { 1,1,1,0,0,0,1 },  // =F
{ 1,1,0,1,1,0,1 },  // =S
{ 1,1,1,1,1,0,0 }  // =b
						};
void setup() {
pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
pinMode(IN2, OUTPUT);
pinMode(KEY1, INPUT);		 // 初始化按鍵腳位為輸入
pinMode(KEY2, INPUT);
pinMode(KEY3, INPUT);
for (i=0; i<7; i++)
pinMode(Seg_Pin[i], OUTPUT); 		// 七段顯示器接腳設為輸出
}
void loop() {
if (digitalRead(KEY1)==0 && mode!=1) {
 		mode=1;						// 設定模式為1
 		digitalWrite(IN1,HIGH); 			// 風扇正轉( 送風)
 		digitalWrite(IN2,LOW);
CodeWrite (0);						// 七段顯示器顯示 F
	}
else if (digitalRead(KEY2)==0 && mode!=2) {
 		mode=2; // 設定模式為2
 		digitalWrite(IN1,LOW); 			// 風扇停止
 		digitalWrite(IN2,LOW);
CodeWrite (1);						// 七段顯示器顯示 S

 	}
else if (digitalRead(KEY3)==0 && mode!=3) {
mode=3; 						// 設定模式為3
 		digitalWrite(IN1,LOW); 			// 風扇反轉( 吸風)
 		digitalWrite(IN2,HIGH);
CodeWrite (2);						// 七段顯示器顯示 b
 	}
}
void CodeWrite(byte dat) {
for (i=0; i<7; i++)
// 讀出 dat 指定位元，並顯示在對應七段顯示器的 pin 腳上
digitalWrite(Seg_Pin[i], S_seg[dat][i]);
 }

