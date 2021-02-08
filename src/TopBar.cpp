/**
 * @file TopBar.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "TopBar.h"

#include "DisplayDriver.h"

extern DisplayDriver display;

// TopBar::TopBar(void) {}

TopBar::TopBar(int h, color_t bgColor, color_t borderColor = BORDER_COLOR)
    : Frame(0, 0, display.width(), h, bgColor, borderColor, false, true),
      commIndicator(COMM_INDICATOR_X, COMM_INDICATOR_Y, bgColor),
      timeIndicator(TIME_INDICATOR_X, TIME_INDICATOR_Y, TIME_INDICATOR_COLOR, bgColor),
      batteryIndicator(BATTERY_INDICATOR_X, BATTERY_INDICATOR_Y, bgColor) {}

void TopBar::clear(void) { Frame::clear(); }

void TopBar::draw(void) {
  clear();
  commIndicator.draw();
  timeIndicator.draw();
  batteryIndicator.draw();
}

void TopBar::refresh(bool force) {
  commIndicator.refresh(force);
  timeIndicator.refresh(force);
  batteryIndicator.refresh(force);
}

void TopBar::showTime(bool enabled) {
  timeIndicator.visible = enabled;
}

void TopBar::showSignal(bool enabled) { commIndicator.visible = enabled; }