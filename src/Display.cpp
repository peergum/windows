/**
 * @file Display.cpp
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-05
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#include "Display.h"

#include "Adafruit_SSD1351_Photon.h"

template <>
Display<Adafruit_SSD1351>::Display(uint8_t CS, uint8_t RS, uint8_t SID,
                                  uint8_t SCLK, uint8_t RST)
    : Adafruit_GFX(SSD1351WIDTH, SSD1351HEIGHT),
      Adafruit_SSD1351(CS, RS, SID, SCLK, RST) {}

template <>
Display<Adafruit_SSD1351>::Display(uint8_t CS, uint8_t RS, uint8_t RST)
    : Adafruit_GFX(SSD1351WIDTH, SSD1351HEIGHT),
      Adafruit_SSD1351(CS, RS, RST) {}

template <>
void Display<Adafruit_SSD1351>::fill(color_t color) {
  Adafruit_SSD1351::fillScreen(color);
}

template <>
void Display<Adafruit_SSD1351>::clear(void) {
  fill(BLACK);
}

template <>
void Display<Adafruit_SSD1351>::on(void) {
  writeCommand(SSD1351_CMD_DISPLAYON);
}

template <>
void Display<Adafruit_SSD1351>::off(void) {
  writeCommand(SSD1351_CMD_DISPLAYOFF);
}

template <>
void Display<Adafruit_SSD1351>::begin(DisplayOrientation orientation) {
  setRotation(orientation);
  Adafruit_SSD1351::begin();
  clear();
  Adafruit_SSD1351::setFont(ARIAL_8);
  on();
}

template <>
int Display<Adafruit_SSD1351>::textWidth(char *text) {
  int w = 0;
  for (uint8_t i = 0; i < strlen(text); i++) {
    w += charWidth(text[i]);
  }
  return w;
}

template <>
void Display<Adafruit_SSD1351>::showText(uint16_t x, uint16_t y,
                                         const char *text, uint8_t size,
                                         uint16_t color) {
  setCursor(x, y);
  setTextSize(size);
  setTextColor(color);
  print(text);
}
