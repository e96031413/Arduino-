/*
  序列阜(沒有行結尾)改成(NL&CR)
  AT：測試，回應「OK」
  AT+VERSION：回應?體的版本。
  AT+NAME:xyz：將裝置名稱改為「xyz」。n
  AT+PIN:1234：將連線密碼換為「1234」。
  AT+BAUD4：將 baud rate 換為 9600。
  AT+BAUD5：將 baud rate 換為 19200
  AT+BAUD6：將 baud rate 換為 38400
  AT+BAUD7：將 baud rate 換為 57600
*/
int XX;
int YY;
int ZZ;
#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // TX, RX(in BLUETOOTH)
char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(9600);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }

  if(val=='R')
    {
      digitalWrite(3,HIGH);
    }

  else if(val=='r')
    {
    digitalWrite(3,LOW);
    }

  else if(val=='A')
  {
    XX=BT.parseInt();
    Serial.print("XX=");
    Serial.println(XX);
    analogWrite(3,map(XX,0,100,0,255));
  }
  else if(val=='B')
  {
    YY=BT.parseInt();
    Serial.print("YY=");
    Serial.println(YY);
    analogWrite(5,map(YY,0,100,0,255));
  }
  else if(val=='C')
  {
    ZZ=BT.parseInt();
    Serial.print("ZZ=");
    Serial.println(ZZ);
    analogWrite(6,map(ZZ,0,100,0,255));
  }

  
}


