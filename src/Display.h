/**
 * @file Display.h
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-05
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#ifndef __DISPLAY_H
#define __DISPLAY_H

#define SSD1351WIDTH 128
#define SSD1351HEIGHT 128

#include "Adafruit_mfGFX.h"
#include "colors.h"

typedef enum DisplayOrientation {
  DISPLAY_UP = 3,
  DISPLAY_LEFT = 2,
  DISPLAY_DOWN = 1,
  DISPLAY_RIGHT = 0,
} DisplayOrientation;

template <class T>
class Display : public T {
 public:
  Display(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST);
  Display(uint8_t CS, uint8_t RS, uint8_t RST);
  void begin(DisplayOrientation orientation = DISPLAY_UP);
  void clear(void);
  void fill(color_t color = RED);
  void on(void);
  void off(void);
  int textWidth(char *text);
  void showText(uint16_t x, uint16_t y, const char *text, uint8_t size = 1,
                uint16_t color = WHITE);

 private:
  uint8_t _cs;
};

#endif