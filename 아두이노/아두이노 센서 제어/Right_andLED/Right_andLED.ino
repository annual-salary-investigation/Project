#define ILLUMI A0
#define LED  13
void setup() 
{
  Serial.begin(9600); //  Serial객체에 begin함수호출. 수신할 수 있는 비트율(bps)
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() 
{
  int sensor = analogRead(ILLUMI);  //  A0핀에 있는 값을 아날로그 값으로 읽어온다. 

  if (sensor<300) // 밝으면
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }

  Serial.println(sensor);       //  센서값을 출력한다.
  delay(1000);
}
