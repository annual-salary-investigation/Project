#define LED 11
#define FLAME 13
#define BUZ 12
#define RE 288
#define TI 480
int state = 0;
int music[] = {RE,TI};

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(FLAME, INPUT);
  Serial.begin(9600);
  digitalWrite(LED, LOW);
}

void loop() {
  state = digitalRead(FLAME);

  if(state == 0)
  {
    Serial.println("ON");
    digitalWrite(LED, HIGH);
    music_play();
  }
  else
  {
    Serial.println("OFF");
    digitalWrite(LED, LOW);
  }
  delay(1000);
}

void music_play()
{
    for(int i =0; i<sizeof(music)/sizeof(int);i++)
    {
      tone(BUZ, music[i]*2, 100);
      delay(300);
    }
}
