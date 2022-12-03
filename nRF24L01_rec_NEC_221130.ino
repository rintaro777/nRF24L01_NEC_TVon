// LED点灯(受信側)
#define IR_SEND_PIN 3
 
#include <SPI.h>                  // ライブラリのインクルード
#include <nRF24L01.h>
#include <RF24.h>
#include <IRremote.hpp>
 
RF24 radio(7, 8);                // CE,CSNピンの指定
const byte address[6] = "00001";  // データを受信するアドレス
//int LED_PIN = 3;
boolean SW_state = 0;
 
void setup() {  
  pinMode(3, OUTPUT);  
  radio.begin();                      // 無線オブジェクトの初期化 
  radio.openReadingPipe(0, address);  // データ受信アドレスを指定
  radio.setPALevel(RF24_PA_HIGH);      // 出力を最小に
  radio.startListening();             // 受信側として設定
  IrSender.begin();
  
}

// Protocol=SONY Address=0x1 Command=0x15 Raw-Data=0x95 電源ONコマンド
uint16_t addressSONY = 0x1;
uint16_t commandSONY = 0x15; 
 
void loop(){
  
  if (radio.available()){
    radio.read(&SW_state, sizeof(SW_state));  // スイッチの状態を受信する
    
    if(SW_state == HIGH){
//      digitalWrite(3, HIGH);
//      /*
      IrSender.sendSony(addressSONY, commandSONY, 0);
      delay(40);
      IrSender.sendSony(addressSONY, commandSONY, 0);
      delay(40);
      IrSender.sendSony(addressSONY, commandSONY, 0);
//      */
    } else {
//      digitalWrite(3, LOW);
    }
  }

delay(100);
 
}