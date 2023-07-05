#include <Stepper.h>

#define ILLUMI A0
#define LED  13

int flag = 0;

// 2048:한바퀴(360도), 1024:반바퀴(180도)...
const int stepsPerRevolution = 2048; 
// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,11,9,10,8); 

void setup() 
{
  Serial.begin(9600); //  Serial객체에 begin함수호출. 수신할 수 있는 비트율(bps)
  myStepper.setSpeed(14); 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() 
{
  int sensor = analogRead(ILLUMI);  //  A0핀에 있는 값을 아날로그 값으로 읽어온다. 

  if (flag == 0 and sensor<300) // 밝으면
  {
    digitalWrite(LED, HIGH);
    myStepper.step(stepsPerRevolution);
    flag = 1;
  }
  else if(flag == 1 and sensor>300)
  {
    digitalWrite(LED, LOW);
    myStepper.step(-stepsPerRevolution);
    flag = 0;
  }

  Serial.println(sensor);       //  센서값을 출력한다.
  delay(1000);
}
