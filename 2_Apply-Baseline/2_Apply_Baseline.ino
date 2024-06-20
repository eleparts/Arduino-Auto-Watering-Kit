#include <Wire.h>                                      // I2C 통신을 쉽게 사용할 수 있도록 해주는 라이브러리
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>                          // OLED 드라이버가 SSD1306인 제품을 쉽게 다룰 수 있게 해주는 라이브러리
#define soil_sensor A0                                 // 아날로그 0번 핀을 'soil_sensor' 라는 이름으로 지정

Adafruit_SSD1306 display(128,32);                      // SSD1306 OLED의 해상도를 128*32로 설정

void setup() {
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);                                  // 릴레이 모듈에 연결된 2번핀을 출력으로 설정

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);           // I2C 통신을 위해 OLED의 I2C 주소를 설정
  delay(2000);
  display.setTextSize(2);                              // OLED 글자 크기를 2로 설정
  display.clearDisplay();                              // 기존 OLED에 입력된 데이터 전체 삭제
  display.display();                                   // OLED에 입력 및 삭제와 같은 신호를 한 번에 OLED에 적용 (새로고침)
}

void loop() {
  int soil = analogRead(soil_sensor);                  // 'soil' 이라는 변수를 만들어 아날로그 토양 습도 센서값을 저장

  Serial.print("Moisture: ");                          // 아래 변수 출력과 함께 토양 습도 센서값 시리얼 모니터에 출력
  Serial.println(soil);

  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);  // OLED의 글자 색상을 흰색, 바탕 색상을 검은색으로 설정
  display.setCursor(0,0);                              // OLED의 글자 커서를 (x = 0, y = 0)으로 세팅
  display.println("MOISTURE :");                       // 아래 변수 출력과 함께 토양 습도 센서값 OLED에 출력
  display.print(soil); 

  if(1000 > soil){                                     // 센서값이 1000보다 작을 경우, 네 번째 자리 수를 제거
    display.setCursor(36,16);                          // 이를 하지 않을 경우 ex)
    display.print(" ");                                // 첫 번째 값 : 1023 -> 두 번째 값 : 453'3' 처럼 3 고정
  }
  display.display();

  digitalWrite(2,HIGH);                                // 릴레이 모듈을 통한 워터펌프 동작 테스트를 위해 1초간 동작
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);

  delay(3000);
}
