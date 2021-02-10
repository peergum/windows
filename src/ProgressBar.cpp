/**
 * @file ProgressBar.cpp
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-08
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#include "ProgressBar.h"

#include "DisplayDriver.h"

extern DisplayDriver display;

ProgressBar::ProgressBar(int x, int y, int w, int h, int r, color_t color1,
                         color_t color2, color_t bgColor, color_t borderColor)
    : Frame(x, y, w, h, bgColor, borderColor, false, false),
      color1(color1),
      color2(color2),
      radius(r) {}

void ProgressBar::draw(void) {
  refresh(true);
}

void ProgressBar::refresh(bool force) {
  char text[6];
  if (force || checkTimer(_refreshTimer, refreshRateMS)) {
    int yi, wi, index;
    display.drawRoundRect(_x-1, _y-1, _w+2, _h+2, radius, _borderColor);

    for (int i = 1; i < _h - 1; i++) {
      yi = _y + i;
      wi = (_w - 1) * progress / 100;
      for (int j = 1; j < _w - 1; j++) {
        index = (j + i + (millis() / refreshRateMS)) % (color1Count + color2Count);
        if (j < wi) {
          display.drawPixel(_x + j, yi, index < color1Count ? color1 : color2);
        }
        else {
          display.drawPixel(_x + j, yi, _bgColor);
        }
      }
    }
#if PROGRESSBAR_SHOW_VALUE
    sprintf(text, "%d%%", progress);
    uint16_t textWidth = display.textWidth(text);
    display.fillRect(_x + (_w - textWidth) / 2 -2, _y + (_h - 8) / 2-1,textWidth+4,10,PROGRESSBAR_TEXT_SHADOW);
    display.setCursor(_x + (_w - textWidth) / 2, _y + (_h - 8) / 2);
    display.setTextColor(PROGRESSBAR_TEXT_COLOR);
    display.print(text);
#endif
  }
}