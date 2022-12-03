// LED点灯(送信側)
 
#include <SPI.h>                  // ライブラリのインクルード
#include <nRF24L01.h>
#include <RF24.h>
#include <IRremote.h>            // ライブラリのインクルード_赤外線受信部
 
RF24 radio(7, 8);                // CE,CSNピンの指定       
const byte address[6] = "00001";  // データを送信するアドレス
 
int recvPin = 3;              //赤外線受信部ピン
boolean NEC_state = 0;
IRrecv irrecv(recvPin);       //受信開始コマンド
decode_results results;       //受信データ処理部
 
 
void setup() {
  
  radio.begin();                  // 無線オブジェクトの初期化
  radio.openWritingPipe(address); // データ送信先のアドレスを指定
  radio.setPALevel(RF24_PA_HIGH);  // 出力を最小に
  radio.stopListening();          // 送信側として設定
  irrecv.enableIRIn();  // 赤外線受信部開始
}
 
 
void loop(){
  if (irrecv.decode(&results)) // 赤外線受信したかどうかの確認 未受信＝0/受信＝1
  {   
    switch(results.value)
    {
      case 0xFFA25D:            // NEC 電源ボタンを押した場合
            NEC_state=1;        // フラグを1に
            break;
    }
    irrecv.resume(); // .decode()の返り値をリセット
  }
  radio.write(&NEC_state, sizeof(NEC_state));  // スイッチの状態を送信する
  NEC_state=0;        // フラグをリセット
  delay(100); 
}