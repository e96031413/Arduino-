#include "config.h"
char mode=0;		; // 工作模式, 預設為0
void setup() {
pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
pinMode(IN2, OUTPUT);
pinMode(KEY1, INPUT);		 // 初始化按鍵腳位為輸入
pinMode(KEY2, INPUT);
pinMode(KEY3, INPUT);
}
void loop() {
if (digitalRead(KEY1)==0 && mode!=1) {
 		mode=1;						// 設定模式為1
 		digitalWrite(IN1,HIGH); 			// 風扇正轉( 送風)
 		digitalWrite(IN2,LOW);
 	}
else if (digitalRead(KEY2)==0 && mode!=2) {
 		mode=2; // 設定模式為2
 		digitalWrite(IN1,LOW); 			// 風扇停止
 		digitalWrite(IN2,LOW);
 	}
else if (digitalRead(KEY3)==0 && mode!=3) {
                mode=3; 						// 設定模式為3
 		digitalWrite(IN1,LOW); 			// 風扇反轉( 吸風)
 		digitalWrite(IN2,HIGH);
 	}
 }

