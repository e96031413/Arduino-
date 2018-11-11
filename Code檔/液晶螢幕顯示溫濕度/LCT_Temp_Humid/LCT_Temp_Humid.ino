#include <LiquidCrystal_I2C_AvrI2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2);
#include <dht.h>
#define dht_dpin 2 //定義訊號要從Pin A0 進來  

dht DHT;
byte easy [8] = {

  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

void setup() {
  lcd.begin();
  lcd.backlight();
  delay(250);
  lcd.noBacklight(); // 關閉背光
  delay(250);
  lcd.backlight();
  delay(250);
  lcd.noBacklight(); // 關閉背光
  delay(250);
  lcd.backlight();
  lcd.print("Hello");
  lcd.setCursor(0, 1);  //游標移到左上角
  lcd.print("Wecome");
  lcd.createChar(1, easy);

  Serial.begin(9600);
  delay(300);             //Let system settle
  Serial.println("Humidity and temperature\n\n");
  delay(300);             //Wait rest of 1000ms recommended delay before
  //accessing sensor

}
void loop() {
  DHT.read11(dht_dpin);   //去library裡面找DHT.read11
  lcd.clear();  //清除螢幕
  lcd.setCursor(0, 0);  //游標移到左上角
  lcd.print("Humidity=");
  float H = DHT.humidity;
  float T = DHT.temperature;
  lcd.print(H);
  lcd.print("%");
  lcd.write(byte(1));
  lcd.setCursor(0, 1);  //游標移到左上角
  lcd.print("Temperature=");
  lcd.print(T);
  lcd.println("C");
  delay(10000);            //每1000ms更新一次

}
