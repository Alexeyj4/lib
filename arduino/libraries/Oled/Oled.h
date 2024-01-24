#pragma once
#include <config.h>
#ifndef OLED_DISPLAY_TYPE 
//#error "please define in config.h: OLED_DISPLAY_TYPE. Example: #define OLED_DISPLAY_TYPE 96"
#endif		

#include <Adafruit_GFX.h>
#include <CourierCyr8.h>
#include <Adafruit_SSD1306.h>//debug
#if (OLED_DISPLAY_TYPE==96)
#include <Adafruit_SSD1306.h>
#elif (OLED_DISPLAY_TYPE==130)
#include <Adafruit_SH1106.h>
#endif

class Oled{
  public:
    Oled();
    void begin();
    void update();
    void print(int row, String s);        
    int screen_width; // OLED display width, in pixels
    int screen_height; // OLED display height, in pixels    
    int oled_string_pos[4];//positon for each string on oled
    String oled_text[4];//text on OLED
    bool oled_str_changed[4];//OLED strings needs to update
    bool oled_need_update;//OLED need update flag
	Adafruit_SSD1306 display;
	#if (OLED_OLED_DISPLAY_TYPE==96)	
	#pragma message "OLED type is SSD1306 0.96"
	//Adafruit_SSD1306 display;
	#elif (OLED_OLED_DISPLAY_TYPE==130)
	#pragma message "OLED type is SH1106 1.3"
	Adafruit_SH1106 display;		
	#endif    
};