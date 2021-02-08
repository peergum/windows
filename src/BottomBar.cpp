/**
 * @file BottomBar.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "BottomBar.h"

#include "DisplayDriver.h"

extern DisplayDriver display;

BottomBar::BottomBar(int h, color_t bgColor, color_t borderColor)
    : Frame(0, display.height() - h, display.width(), h, bgColor, borderColor,
            true, false) {}

/**
 * @brief clear bottom bar
 *
 */
void BottomBar::clear(void) { Frame::clear(); }

/**
 * @brief display bar
 *
 */
void BottomBar::draw(void) {
  int textWidth = display.textWidth(_content);
  display.showText(_x + (_w - textWidth) / 2, _y+1, _content, 1, WHITE);
  _updated = false;
}

/**
 * @brief refresh bottom bar
 *
 * @param force
 */
void BottomBar::refresh(bool force) {
  if (_updated || force) {
    clear();
    draw();
  }
}

/**
 * @brief Set the Status object
 * 
 * @param status 
 */
void BottomBar::setStatus(const char *status) {
  strcpy(_content, status);
  _updated = true;
}