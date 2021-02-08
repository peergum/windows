/**
 * @file Alert.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-31
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "Alert.h"

#include "DisplayDriver.h"

extern DisplayDriver display;

Alert::Alert(void) {}

Alert::Alert(const char *text, uint16_t color, bool framed) {
  set(text, color, framed);
}

Alert &Alert::set(const char *text, uint16_t color, bool framed) {
  strncpy(_text[0], text, 40);
  _color[0] = color;
  _size[0] = 1;
  _counter = 1;
  _framed = framed;
  return *this;
}

Alert &Alert::add(const char *text, uint16_t color, int size) {
  if (_counter < 6) {
    strncpy(_text[_counter], text, 40);
    _color[_counter] = color;
    _size[_counter] = size;
    _counter++;
  }
  return *this;
}

void Alert::visible(void) { _visible = true; }
void Alert::remove(void) { _visible = false; }
void Alert::show(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  Serial.println("Alert");
  if (_visible) {
    uint16_t maxWidth = 0;
    uint16_t textWidth;
    int yi = y + (h - 10 * _counter) / 2;
    for (int i = 0; i < _counter; i++) {
      textWidth = display.textWidth(_text[i]);
      if (textWidth > maxWidth) {
        maxWidth = textWidth;
      }
    }
    if (_framed) {
      display.fillRect(x + (w - maxWidth) / 2 - 8, yi - 8, maxWidth + 16,
                       _counter * 10 + 16, ALERT_BG_COLOR);
    }
    for (int i = 0; i < _counter; i++) {
      textWidth = display.textWidth(_text[i]);
      if (textWidth > maxWidth) {
        maxWidth = textWidth;
      }
      display.setCursor(x + (w - textWidth) / 2, yi + (10 * i));
      display.setTextColor(_color[i]);
      display.setTextSize(_size[i]);
      display.print(_text[i]);
    }
    if (_framed) {
      display.drawRect(x + (w - maxWidth) / 2 - 8, yi - 8, maxWidth + 16,
                            _counter * 10 + 16, WHITE);
      // display.drawFastHLine(x + (w - maxWidth) / 2 - 7, yi + _counter * 10 + 9,
      //                       maxWidth + 17, MEDIUMGREY);
      // display.drawFastVLine(x + (w + maxWidth) / 2 + 9, yi - 7,
      //                       _counter * 10 + 17, MEDIUMGREY);
    }
  }
}