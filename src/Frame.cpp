/**
 * @file Frame.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "Frame.h"
#include "colors.h"
#include "DisplayDriver.h"

extern DisplayDriver display;

Frame::Frame(int x, int y, int w, int h, uint16_t bgColor, uint16_t borderColor,
             bool hasTopBorder, bool hasBottomBorder)
    : _x(x),
      _y(y),
      _w(w),
      _h(h),
      _bgColor(bgColor),
      _borderColor(borderColor),
      hasTopBorder(hasTopBorder),
      hasBottomBorder(hasBottomBorder) {}

void Frame::clear(void) {
  display.fillRect(_x, _y, _w, _h, _bgColor);
  if (hasTopBorder) {
    display.drawFastHLine(_x, _y - 1, _w, _borderColor);
  }
  if (hasBottomBorder) {
    display.drawFastHLine(_x, _y + _h, _w, _borderColor);
  }
}

void Frame::draw(void) {}

void Frame::refresh(bool force) {}