#include <Oled.h>
Oled oled;

void setup() {
  // put your setup code here, to run once:
  oled.begin();
}

void loop() {
  oled.print(0,"First string");
  oled.print(3,"Fourth string");
  oled.update();  
}
