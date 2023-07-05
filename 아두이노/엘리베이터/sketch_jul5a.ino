#include <Stepper.h>
#include <time.h>

int led_pin[] = {8,9,10,11,12,13,A5};  // A,B,C,D,E,F,G

// 각 숫자에 대한 LED 설정 값을 정의합니다.
// 숫자에 매칭되는 LED의 로직레벨을 LOW(0) 상태로 설정합니다.
int set_number[4][7] = {
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
};

int stepsPerRev = 2048; 
Stepper stepper (stepsPerRev, 4,5,6,7); // ( IN4,IN2,IN3,IN1)
int btn1 = 3;
int btn2 = 2;
int btn3 = 1;
int btn4 = 0;
int floors = 4; //현재 위치
int move = 0;
int num = 0;



void setup() {
  Serial.begin(9600);
  stepper.setSpeed(15); 

  for (int i = 0 ; i < 8; i ++){
    pinMode(led_pin[i], OUTPUT);
  }

  pinMode(btn1, INPUT_PULLUP);    //raspberry pi 에서는 GPIO 역활이다.
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);

    for (int i=0; i < 8; i++){
    digitalWrite(led_pin[i], set_number[3][i]);
  } 
}

void loop() {
  boolean btn1HL = digitalRead(btn1);
  boolean btn2HL = digitalRead(btn2);
  boolean btn3HL = digitalRead(btn3);
  boolean btn4HL = digitalRead(btn4);

  if (btn1HL == LOW) { // 버튼을 누를때 0
    for (int i=0; i < 8; i++){
      digitalWrite(led_pin[i], set_number[0][i]);
    } 
    move = floors - 1;
    Serial.println(move);
    stepper.step(stepsPerRev*move);  
    floors=1;
    btn1HL==HIGH;
    delay(1000);

  }

  else if (btn2HL == LOW) {
    for (int i=0; i < 8; i++){
      digitalWrite(led_pin[i], set_number[1][i]);
    } 
    move = floors - 2;
    Serial.println(move);
    stepper.step(stepsPerRev*move);
    delay(1000);

    floors=2;
    btn2HL==HIGH;
    delay(1000);

    
  }

  else if (btn3HL == LOW)
  { 
    for (int i=0; i < 8; i++){
      digitalWrite(led_pin[i], set_number[2][i]);
    } 
    move = floors - 3;
    Serial.println(move);
    stepper.step(stepsPerRev*move);
    floors=3;
    btn3HL==HIGH;
    delay(1000);


  }

  else if (btn4HL == LOW)
  {
    for (int i=0; i < 8; i++){  // 7segments 동작
      digitalWrite(led_pin[i], set_number[3][i]);
    }
    move = floors - 4;
    Serial.println(move);
    stepper.step(stepsPerRev*move);
    floors=4;
    btn4HL==HIGH;
    delay(1000);

  }

  else {

  }


}
//   선입선출x 정렬o. (층을 누르고 진행중에 누르는 버튼을 누르면 배엘에 다음 동작을 추가하는식 [1, 4, 2, 3]) 버블정렬. 