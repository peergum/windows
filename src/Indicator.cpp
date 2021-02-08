/**
 * @file Indicator.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "Indicator.h"
#include "DisplayDriver.h"

extern DisplayDriver display;

Indicator::Indicator(int x, int y, int w, int h, color_t bgColor, color_t color)
    : x(x),
      y(y),
      w(w),
      h(h),
      bgColor(bgColor),
      color(color),
      visible(true),
      updated(false),
      callback(NULL) {}


void Indicator::draw(void) {
  // display.fillCircle(x + w / 2, y + h / 2, w > h ? h / 2 : w / 2, color);
}

void Indicator::refresh(void) {
  if (updated) {
    remove();
    draw();
  }
}

void Indicator::remove(void) { display.fillRect(x, y, w, h, bgColor); }

void Indicator::setCallback(void (*cb)(int &value, int &type, int &state)) {
  callback = cb;
}

void Indicator::initTimer(unsigned long &timer) { timer = millis(); }

bool Indicator::checkTimer(unsigned long &timer, unsigned long durationMS) {
  if (millis() - timer >= durationMS) {
    initTimer(timer);
    return true;
  }
  return false;
}
