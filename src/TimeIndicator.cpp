/**
 * @file TimeIndicator.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-31
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "TimeIndicator.h"

#include <time.h>

#include "DisplayDriver.h"
#include "Particle.h"
#include "screendefs.h"

extern DisplayDriver display;

TimeIndicator::TimeIndicator(int x, int y, uint16_t color, uint16_t bgColor)
    : Indicator(x, y, TIME_INDICATOR_WIDTH, TIME_INDICATOR_HEIGHT, bgColor),
      color(color) {}

void TimeIndicator::draw(void) {
  remove();
  time_t tTime;

  tTime = Time.now();
  struct tm *tm = gmtime(&tTime);
  char time[12];
  strftime(time, 12, "%H:%M:%S", tm);
  uint16_t textWidth = display.textWidth(time);
  display.showText(x+(TIME_INDICATOR_WIDTH-textWidth)/2,y,time,1,color);
}

void TimeIndicator::refresh(bool force) {
  if (force || checkTimer(_refreshTimer, 1000UL)) {
    draw();
  }
}
