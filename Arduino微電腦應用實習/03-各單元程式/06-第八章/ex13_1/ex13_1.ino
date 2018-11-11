#include<LiquidCrystal.h>	     //LiquidCrystal.h程式庫
LiquidCrystal lcd(12,11,5,4,3,2);  //LiquidCrystal.h程式庫對應接腳宣告
//自訂符號表
byte logo_a[8]={
0b00100,0b01110,0b11111,0b00100,0b00100,0b00100,0b00100,0b0000};
byte logo_b[8]={ 
0b00100,0b00100,0b00100,0b01110,0b11111,0b01110,0b00100,0b0000};
byte logo_c[8] = {
0b01110,0b10101,0b11111,0b01110,0b00100,0b00100,0b00100,0b0000};
byte logo_d[8] = {
0b00100,0b00100,0b00100,0b10101,0b11111,0b10101,0b01110,0b0000};
void setup()
{
    lcd.createChar(0,logo_a);       //設定自訂符號logo_a編號為0
    lcd.createChar(1,logo_b);       //設定自訂符號logo_b編號為1
    lcd.createChar(2,logo_c);       //設定自訂符號logo_c編號為2
    lcd.createChar(3,logo_d);       //設定自訂符號logo_d編號為3
    lcd.begin(16,2);		//LCD為2行，每行16(列)個字
    lcd.clear();		//清除螢幕
}
void loop()
{
    lcd.setCursor(5,0);    	//文字顯示位置
    lcd.write(byte(0));		//LCD顯示文字
    lcd.setCursor(10,0);    //文字顯示位置
    lcd.write(byte(1));		//LCD顯示文字
    lcd.setCursor(5,1);    	//文字顯示位置
    lcd.write(byte(2));		//LCD顯示文字
    lcd.setCursor(10,1);    //文字顯示位置
    lcd.write(byte(3));		//LCD顯示文字
    delay(2000);			//文字顯示停留時間
    lcd.clear();				//清除螢幕
    delay(2000);			//文字顯示停留時間
}

