#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initialising...");
  delay(1000);
}

int timer_lcd_voltage = 0;
void loop() {
  float voltage = (analogRead(A0) * 5.0) / 1024.0;
  // Serial.println(voltage);
  int timer_check = timer_lcd_voltage % 50;
  Serial.println(timer_check);
  if (!timer_check) {
    lcd.clear();
    lcd.print(voltage);
    lcd.print("V");
  }
  timer_lcd_voltage ++;
}
