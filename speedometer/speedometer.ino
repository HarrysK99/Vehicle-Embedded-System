#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int int_pin = 3;

volatile unsigned long prev = 0;
volatile float vel = 0.0;
volatile float prev_vel = 0.0;

bool inv = false;

volatile unsigned long now = 0;

const unsigned long interval = 1000;
unsigned long previousMillis = 0;

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  Serial.begin(9600);
  Serial.println("Hi");

  display.display();
  Serial.println("###1");
  delay(5000);
  Serial.println("###2");
  display.clearDisplay();

  // 텍스트 크기와 컬러 설정
  display.setTextSize(2); // 텍스트 크기를 2로 설정
  display.setTextColor(SSD1306_WHITE);

  pinMode(int_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(int_pin), myISR, RISING);

}

void myISR(){
  Serial.println("interrupt");
  now=millis();
  if(now-prev == 0);
  else{
    //Serial.println("1");
    //count(#)/1second * 3600seconds/1h * 1rot/6# * (2pi0.2286)*0.001km/1rot
    //count*600rot/1h*1.436336*0.001km/1rot
    //count*0.8618
    vel = 861.80151744/(now-prev);
  prev=now;
  }
  //Serial.println("2");
}

void loop(){
  unsigned long nowLoop = millis();

  if(nowLoop - previousMillis >= interval){
  previousMillis=nowLoop;
  Serial.println(vel);

  //if (abs(prev_vel - vel) > 20)
  //  vel = prev_vel;
/*
  if (vel < 7)
    vel = 0.0;
*/

  if (vel > 80)
    vel = 0.0;
  
  if(vel > 50)
    inv = !inv;
  else
    inv = false;

  ///*  
  char buffer[8];
  dtostrf(vel, 4, 2, buffer);
  //snprintf(buffer, sizeof(buffer), "%.2f", vel);

  //Serial.println("%%%%%%");
  //Serial.println(buffer);
  //Serial.println("%%%%%%");

  // 텍스트의 길이 계산 (글꼴 크기 2)
  int16_t textWidth = strlen(buffer) * 12; // 글꼴 크기 2일 때 각 문자의 너비는 12

  // X 좌표를 계산하여 텍스트를 중앙에 배치
  int16_t x = (SCREEN_WIDTH - textWidth) / 2;

  // Y 좌표를 계산하여 텍스트를 중앙에 배치
  int16_t y = (SCREEN_HEIGHT - 16) / 2; // 글꼴 크기 2일 때 높이는 16

  display.clearDisplay();
  
  // 텍스트를 중앙에 표시
  display.setCursor(x, y);
  display.println(buffer);
  display.setRotation(2);
  display.invertDisplay(inv);

  // 디스플레이 업데이트
  display.display();
  //*/
  }
}
