// 양방향 통신 차 쪽
// 차에서 응급차량 정보를 보내면 신호등에서 응급차량 정보를 받음
// 정보를 받은 뒤 강화학습을 돌려서 가야할 방향의 신호를 켬
// 신호등에서 차로 방향 정보를 보냄

#include <SoftwareSerial.h>
SoftwareSerial softSerial(2,3);

int rx;
char per[10];
char buff[10];

int i=0;
int a=0;

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  //default is receiver
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
}

 

void show(){
  int h = 0;
  for( int j=0 ; j<5; j++ ){
      Serial.print(per[j]); 
  }
}

void Send_buff(){
  for( int j=0; j<1; j++){  // 신호등에서 차로 방향 정보 하나만 보내기 때문에!!
    per[j] = buff[j];
    buff[j] = "";
  }
  show();
}


void loop() {
   int j;

   // 응급차량의 정보
   int tx[6];
   tx[0]=2;
   tx[1]=3;
   tx[2]=100;
   tx[3]=1;
   tx[4]=5;
   tx[5]=0;


   // 기본값이 수신 상태, 1을 누르면 증폭기가 꺼지고 송신을 시작한다. 
   if(Serial.read()=='1'){ //become TX
    digitalWrite(11, HIGH);
    //delay(2000);
    digitalWrite(10, LOW);

    for(j=0;j<3;j++){ // 응급차량의 정보가 확실히 보내기 위해 총 3번을 보낸다. 
      for(int i=0; i<6; i++){ // 응급차량의 정보가 총 6개
        softSerial.write(tx[i]);  // 응급차량의 정보를 보내는 코드
        Serial.println(tx[i]);  // Serial 모니터에서 출력
        delay(1000);
      }
    }
  }

  if(j==3){ //become RX
     digitalWrite(11, LOW);
     digitalWrite(10, HIGH);

     if(softSerial.available()){
       buff[i] = softSerial.read();
       i++;
     }

     if (i==1){
      Send_buff();
      i=0;
    } 
  }
}
