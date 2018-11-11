/**********七段顯示器測試程式********/
#include "config.h"
byte Seg_Pin[] = {seg_g, seg_f, seg_e, seg_d, seg_c, seg_b, seg_a};	// 宣告七段顯示器接腳陣列 
int i;									// for 迴圈的計數變數
byte  S_seg[3][7] = { { 1,1,1,0,0,0,1 },  // =F
{ 1,1,0,1,1,0,1 },  // =S
{ 1,1,1,1,1,0,0 }  // =b
						};
void setup() {
for (i=0; i<7; i++)
pinMode(Seg_Pin[i], OUTPUT); 		// 七段顯示器接腳設為輸出
}
void loop() {
CodeWrite (0);						// 七段顯示器顯示 F
delay(1000); 						// 延遲1 秒
CodeWrite (1);						// 七段顯示器顯示 S
delay(1000); 						// 延遲1 秒
CodeWrite (2); 						// 七段顯示器顯示 b
delay(1000); 						// 延遲1 秒
}
void CodeWrite(byte dat) {
for (i=0; i<7; i++)
// 讀出 dat 指定位元，並顯示在對應七段顯示器的 pin 腳上
digitalWrite(Seg_Pin[i], S_seg[dat][i]);
}

