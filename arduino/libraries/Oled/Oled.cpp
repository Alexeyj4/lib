#include <config.h>
#include "Oled.h"

Oled::Oled(){
	screen_width=128;
	screen_height=64;            
	oled_string_pos[0]=12; oled_string_pos[1]=28; oled_string_pos[2]=44; oled_string_pos[3]=62;  
	oled_text[0]=""; oled_text[1]=""; oled_text[2]=""; oled_text[3]=""; 
	oled_str_changed[0]=0; oled_str_changed[1]=0; oled_str_changed[2]=0; oled_str_changed[3]=0; 
	oled_need_update=0;
	//display=Adafruit_SSD1306(screen_width, screen_height, &Wire, -1);//debug
	#if(OLED_DISPLAY_TYPE==96)
	#pragma message "OLED type SSD1306 0.96 assign"
	display=Adafruit_SSD1306(screen_width, screen_height, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) 
	#elif(OLED_DISPLAY_TYPE==130)
	#pragma message "OLED type SH1306 1.3 assign"
	display=Adafruit_SH1106(21,22); // Declaration for an display connected to I2C (SDA, SCL pins) 
	#endif
	
}   
  
void Oled::begin(){ 
	//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//debug
	#if(OLED_DISPLAY_TYPE==96)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	#elif(OLED_DISPLAY_TYPE==130)
	display.begin(SH1106_SWITCHCAPVCC, 0x3C);
	#endif
  
  display.setFont(&CourierCyr8pt8b);
  display.setTextSize(1);             
  display.setTextColor(WHITE);  
  display.clearDisplay();
  display.setCursor(0,oled_string_pos[0]); 
  display.println("loading OS...");
  display.display(); 
  delay(500);       
}

void Oled::update(){
  if(oled_need_update){	  
	display.fillRect(0,0,screen_width,screen_height,BLACK); 
    for(int i=0;i<=3;i++){
      if(oled_str_changed[i]){
        display.setCursor(0,oled_string_pos[i]);
        display.print(oled_text[i]);
        oled_str_changed[i]=0;
      }
    }
    display.display();
    oled_need_update=0;
  }
}

void Oled::print(int row, String s){
  oled_need_update=1;
  oled_str_changed[row]=1;
  oled_text[row]=s;
}