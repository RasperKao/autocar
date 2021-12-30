#include "SparkFun_TB6612.h"
#include "BluetoothSerial.h"

//bluetooth 
BluetoothSerial BT;//宣告藍芽物件，名稱為BT

//esp32
#define AIN1 16   // 控制輸入A1
#define AIN2 4   // 控制輸入A2
#define BIN1 5  // 控制輸入B1
#define BIN2 17   // 控制輸入B2
#define PWMA 26
#define PWMB 25
#define STBY 18  // 「待機」控制接Arduino的11腳

const int offsetA = 1;  // 正反轉設定A，可能值為1或-1。
const int offsetB = 1;  // 正反轉設定B，可能值為1或-1。
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// ultrasound
int trigPin = 26;                 
int echoPin = 27;
long distance;
const int dangerThresh = 1740; // xcm*58
byte dir = 0;

// function to calculate distance which preventing from collision
long ping(){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    return pulseIn(echoPin, HIGH);
  }

  // remote mode
 void remote_mode(String button);

 // auto_detection_mode
  void auto_detection(String button);


void setup() {
  //ultrasound
    pinMode(trigPin, OUTPUT);        
    pinMode(echoPin, INPUT);          
    //bluetooth name
    BT.begin("hey");
    // baud rate
    Serial.begin(115200);

}

void loop() {
    if (BT.available()) { 
      
        String button = BT.readString();
       
        if (button){

          remote_mode(button);
          auto_detection(button);
          
//            if(button == "u"){                
//                Serial.write("up");
//                forward(motor1, motor2, 150);  // 驅動雙馬達半速前進
//                 brake(motor1, motor2);   //煞車
//                delay(1000);               // 持續1秒
//                char text_a[] = "前進";
//                int i = 0;
//                while(text_a[i] != '\0'){
//                    BT.write(text_a[i]); 
//                    i++;
//                }         
//             }
//            else if (button == "d"){            
//                Serial.println("down");
//                back(motor1, motor2, -150);  // 驅動雙馬達半速前進
//                brake(motor1, motor2);   //煞車
//                delay(1000);
//                 char text_b[] = "後退";
//                  int i = 0;
//                  while(text_b[i] != '\0'){
//                      BT.write(text_b[i]); 
//                      i++;         
//                  }
//           } 
//          else if (button == "l"){
//              Serial.println("left");
//              left(motor1, motor2, 100);   // 左轉
//              brake(motor1, motor2);   //煞車
//              delay(1000);
//              char text_c[] = "左轉";
//              int i = 0;
//              while(text_c[i] != '\0'){
//                  BT.write(text_c[i]); 
//                  i++;         
//                }             
//            } 
//            else if (button == "r"){
//              Serial.println("right"); 
//              right(motor1, motor2, 100);   // 右轉
//              brake(motor1, motor2);   //煞車
//              delay(1000);
//              char text_d[] = "右轉";
//              int i = 0;
//              while(text_d[i] != '\0'){
//                  BT.write(text_d[i]); 
//                  i++;         
//                }              
//            }
        }                      
    }

}


 void remote_mode(String button){
                if(button == "u"){                
                Serial.write("up");
                forward(motor1, motor2, 150);  // 驅動雙馬達半速前進
                delay(1000);               // 持續1秒
                char text_a[] = "前進";
                int i = 0;
                while(text_a[i] != '\0'){
                    BT.write(text_a[i]); 
                    i++;
                }         
             }
            else if (button == "d"){            
                Serial.println("down");
                back(motor1, motor2, -150);  // 驅動雙馬達半速前進
                delay(1000);
                 char text_b[] = "後退";
                  int i = 0;
                  while(text_b[i] != '\0'){
                      BT.write(text_b[i]); 
                      i++;         
                  }
           } 
          else if (button == "l"){
              Serial.println("left");
              left(motor1, motor2, 100);   // 左轉
              delay(1000);
              char text_c[] = "左轉";
              int i = 0;
              while(text_c[i] != '\0'){
                  BT.write(text_c[i]); 
                  i++;         
                }             
            } 
            else if (button == "r"){
              Serial.println("right"); 
              right(motor1, motor2, 100);   // 右轉
              delay(1000);
              char text_d[] = "右轉";
              int i = 0;
              while(text_d[i] != '\0'){
                  BT.write(text_d[i]); 
                  i++;         
                }              
            }
            else if (button == "n"){
              Serial.println("stop"); 
              brake(motor1, motor2);     // 停止兩個馬達
              delay(1000);
              char text_d[] = "停止";
              int i = 0;
              while(text_d[i] != '\0'){
                  BT.write(text_d[i]); 
                  i++;         
                }              
            }
    }

    void auto_detection(String button){
      if (button == "s"){
      bool g  = true;
      while(g){
           distance = ping();
    Serial.print("Distance : ");
    Serial.println(distance);
    if (distance > dangerThresh){
        if ( dir != 0){
            dir = 0;
            brake(motor1, motor2);
            delay(500);
        }
        forward(motor1, motor2, 100);
      }else{
            if (dir != 1 ){
                dir = 1;
                brake(motor1, motor2); 
                delay(500);
              }
              right(motor1, motor2, 500);
        }
        delay(1000);
           Serial.println("start");
            if (BT.available()) { 
              if (BT.readString() == "e"){
                brake(motor1, motor2);   //煞車
                g = false;
                Serial.println("end");
                }
              }
        }
       
}
      }
