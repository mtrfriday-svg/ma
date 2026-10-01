#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef TFT_BLACK
#define TFT_BLACK 0
#define TFT_WHITE 1
#define TFT_RED 1
#define TFT_GREEN 1
#define TFT_BLUE 1
#define TFT_CYAN 1
#define TFT_MAGENTA 1
#define TFT_YELLOW 1
#define TFT_ORANGE 1
#define TFT_LIGHTGREY 1
#endif

#ifndef TFT_WIDTH
#define TFT_WIDTH 128
#endif
#ifndef TFT_HEIGHT
#define TFT_HEIGHT 64
#endif

class TFT_eSPI_Button {
  int16_t _x=0,_y=0,_w=0,_h=0; bool _pressed=false; uint16_t _outline=1,_fill=0,_text=1; String _label;
public:
  void initButton(Adafruit_SSD1306* tft, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline, uint16_t fill, uint16_t text, char* label, uint8_t textsize) { _x=x;_y=y;_w=w;_h=h;_outline=outline;_fill=fill;_text=text;_label=label?label:""; }
  void initButton(Adafruit_SSD1306* tft, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline, uint16_t fill, uint16_t text, String label, uint8_t textsize) { _x=x;_y=y;_w=w;_h=h;_outline=outline;_fill=fill;_text=text;_label=label; }
  void drawButton(bool inverted=false) { (void)inverted; }
  void press(bool p) { _pressed=p; }
  bool justReleased() { bool r=!_pressed; return r; }
  bool contains(int16_t x,int16_t y) const { return x>=_x-_w/2 && x<=_x+_w/2 && y>=_y-_h/2 && y<=_y+_h/2; }
  void setLabelDatum(int16_t,int16_t,int8_t=MC_DATUM) {}
};

class TFT_eSPI {
  Adafruit_SSD1306* d;
  uint8_t _textSize=1; uint16_t _color=1; int16_t _cx=0,_cy=0;
public:
  TFT_eSPI():d(nullptr) {}
  void init() { begin(); }
  void begin() {
    static Adafruit_SSD1306 oled(TFT_WIDTH,TFT_HEIGHT,&Wire,-1);
    d=&oled;
    Wire.begin(MDEE_OLED_SDA, MDEE_OLED_SCL);
    d->begin(SSD1306_SWITCHCAPVCC, MDEE_OLED_ADDR);
    d->clearDisplay(); d->setTextColor(SSD1306_WHITE); d->setTextSize(1); d->display();
  }
  void setRotation(uint8_t r) { if(d) d->setRotation(r&1 ? 1:0); }
  void fillScreen(uint16_t c) { if(!d)return; d->fillScreen(c?SSD1306_WHITE:SSD1306_BLACK); }
  void setCursor(int16_t x,int16_t y) { _cx=x;_cy=y; if(d)d->setCursor(x,y); }
  int16_t getCursorY() const { return _cy; }
  void setTextSize(uint8_t s) { _textSize=s; if(d)d->setTextSize(s); }
  void setTextColor(uint16_t c, uint16_t bg=0) { (void)bg; _color=c; if(d)d->setTextColor(c?SSD1306_WHITE:SSD1306_BLACK); }
  void setTextWrap(bool w) { if(d)d->setTextWrap(w); }
  void setFreeFont(const void*) {}
  size_t print(const String& s) { if(!d)return 0; size_t n=d->print(s); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  size_t print(const char* s) { if(!d)return 0; size_t n=d->print(s); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  size_t print(int v) { if(!d)return 0; size_t n=d->print(v); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  size_t println(const String& s) { if(!d)return 0; size_t n=d->println(s); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  size_t println(const char* s) { if(!d)return 0; size_t n=d->println(s); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  size_t println(int v) { if(!d)return 0; size_t n=d->println(v); _cx=d->getCursorX();_cy=d->getCursorY(); return n; }
  int16_t textWidth(const String& s) { if(!d)return 0; int16_t x1,y1;uint16_t w,h;d->getTextBounds(s,0,0,&x1,&y1,&w,&h);return w; }
  void drawString(const String& s,int32_t x,int32_t y,uint8_t font=1) { (void)font;setCursor(x,y);print(s); }
  void drawCentreString(const String& s,int32_t x,int32_t y,uint8_t font=1) { (void)font;setCursor(x-textWidth(s)/2,y);print(s); }
  void drawRightString(const String& s,int32_t x,int32_t y,uint8_t font=1) { (void)font;setCursor(x-textWidth(s),y);print(s); }
  void fillRect(int32_t x,int32_t y,int32_t w,int32_t h,uint32_t c) { if(d)d->fillRect(x,y,w,h,c?SSD1306_WHITE:SSD1306_BLACK); }
  void drawRect(int32_t x,int32_t y,int32_t w,int32_t h,uint32_t c) { if(d)d->drawRect(x,y,w,h,c?SSD1306_WHITE:SSD1306_BLACK); }
  void drawLine(int32_t x0,int32_t y0,int32_t x1,int32_t y1,uint32_t c) { if(d)d->drawLine(x0,y0,x1,y1,c?SSD1306_WHITE:SSD1306_BLACK); }
  void drawFastHLine(int32_t x,int32_t y,int32_t w,uint32_t c) { if(d)d->drawFastHLine(x,y,w,c?SSD1306_WHITE:SSD1306_BLACK); }
  void fillCircle(int32_t x,int32_t y,int32_t r,uint32_t c) { if(d)d->fillCircle(x,y,r,c?SSD1306_WHITE:SSD1306_BLACK); }
  void drawRoundRect(int32_t x,int32_t y,int32_t w,int32_t h,int32_t r,uint32_t c) { if(d)d->drawRoundRect(x,y,w,h,r,c?SSD1306_WHITE:SSD1306_BLACK); }
  void fillRoundRect(int32_t x,int32_t y,int32_t w,int32_t h,int32_t r,uint32_t c) { if(d)d->fillRoundRect(x,y,w,h,r,c?SSD1306_WHITE:SSD1306_BLACK); }
  void drawXBitmap(int16_t x,int16_t y,const uint8_t*b,int16_t w,int16_t h,uint16_t c) { if(d)d->drawXBitmap(x,y,b,w,h,c?SSD1306_WHITE:SSD1306_BLACK); }
  bool getTouch(uint16_t*,uint16_t*,uint16_t=600) { return false; }
};
