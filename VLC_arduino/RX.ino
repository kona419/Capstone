#include <SoftwareSerial.h>

SoftwareSerial softSerial(2,3);

int rx;
int per[6];
int buff[18];

int i=0;
int a = 0;
int incomingByte;

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(6, OUTPUT); //red
  pinMode(7, OUTPUT); //green
  
  pinMode(8, OUTPUT); //red
  pinMode(9, OUTPUT); //green

  //2번 신호등
  pinMode(8, OUTPUT); //red
  pinMode(12, OUTPUT); //green

  //3번 신호등
  pinMode(4, OUTPUT); //?
  pinMode(5, OUTPUT); //?
  

  //default is receiver
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  
  digitalWrite(6, HIGH); //red

  //2번신호등 디폴트
  digitalWrite(8, HIGH); //red

  //3번 신호등 디폴트
  digitalWrite(4, HIGH); // red

}

void show(){
  int h = 0;
  for( int j=0 ; j<18; j++ ){
    if(per[j]==2){                 // per[j] == 2이면 , ex = j가 3이면 
      for(h=j; h<j+6; h++){        // h=3, h가 j+6=9가 될때까지 반복
        Serial.print(per[h]);      // h=3부터 h=9까지 반복 , h=3이면 per[h]==per[j]==per[3]
       }
       Serial.println();           // 파이썬으로 한 번에 패킷 보내기 위함.
      }
    }
}

void Send_buff(){
    for( int j=0; j<18; j++){
      per[j] = buff[j];
      buff[j] = "";
    }
    show();
  }

void loop() {
   int j;
   char down[] = "right";

   if (Serial.available() > 0){
    incomingByte = Serial.read();
    if(incomingByte == 'D'){
        digitalWrite(7, LOW); // yellow
        digitalWrite(6, LOW); //red
        digitalWrite(9, HIGH); // green
        //2번 신호등
        digitalWrite(12, HIGH); //green
        digitalWrite(8, LOW); //red

        //3번 신호등
        digitalWrite(4, LOW); // red
        digitalWrite(5, HIGH); // red
      
      //릴레이 교체하고 신호보내기
        digitalWrite(11, HIGH);
        delay(2000);
        digitalWrite(10, LOW);
        delay(3000);
        for(j=0;j<5;j++){
          softSerial.write(down[j]);
          Serial.println(down[j]);
        }
      }

      else if(incomingByte == 'U'){
        //1번 신호등
        digitalWrite(7, HIGH); // yellow
        digitalWrite(6, LOW); // red
        digitalWrite(9, LOW); // green
        //2번 신호등
        digitalWrite(12, LOW); //green
        digitalWrite(8, HIGH); //red

        //3번 신호등
        digitalWrite(4, HIGH); // red
        digitalWrite(5, LOW); // green
      
      //릴레이 교체하고 신호보내기
        digitalWrite(11, HIGH);
        delay(2000);
        digitalWrite(10, LOW);
        delay(3000);
        for(j=0;j<5;j++){
          softSerial.write(down[j]);
          Serial.println(down[j]);
        }
      }
   }
   
   if(j==5){ //become RX
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      
     if(softSerial.available()){
      delay(1000);
       buff[i] = softSerial.read();
       i++;
     }
     if (i==18){
      Send_buff();
      i=0;
    } 
  }

}
