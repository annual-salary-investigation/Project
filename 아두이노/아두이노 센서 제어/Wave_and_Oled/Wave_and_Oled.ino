#include <SPI.h>
#include <Wire.h> // i2c통신을 사용하기 때문에 아두이노의 i2c 통신용 라이브러리가 필요
#include <Adafruit_GFX.h> // adafruit의 그래픽 관련 라이브러리
#include <Adafruit_SSD1306.h> // ssd1306 제어용 라이브러리

#define SCREEN_WIDTH 128 // OLED display 가로 픽셀수
#define SCREEN_HEIGHT 64 // OLED display 세로 픽셀수

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin 있는 리셋핀에 연결한 아두이노의 핀 번호  없으면 임의로
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // 디스플레이 객체 생성

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

#define TRIG 7
#define ECHO 8

void setup() 
{
  Serial.begin(9600); // PC 모니터로 센서값을 확인하기 위해 시리얼 통신 정의
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() 
{
  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH); // 물체에 반사되어 돌아온 초음파의 시간을 변수에 저장
  //pulseln() => 핀으로 입력되는 펄스의 시간을 측정하는 함수

  distance = duration*17 / 1000;

  Serial.println(duration); // 초음파가 반사되어 돌아오는 시간
  Serial.print("\nDistance : ");
  Serial.print(distance);
  Serial.println(" Cm");
  delay(1000);

  if (distance<= 5)
  {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))// 0x3C주소로 디스플레이 장치를 초기화
    { 
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // 버퍼를 지움
    display.clearDisplay();

    display.invertDisplay(false);
    delay(3000);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,28);
    display.print("Hello Yeseo!");
    display.write(3);
    display.display();
    delay(5000);

    display.clearDisplay();
    display.display();
  }
}
