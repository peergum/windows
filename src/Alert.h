/**
 * @file Alert.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-31
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __ALERT_H
#define __ALERT_H

#include "screendefs.h"

class Alert {
 public:
  Alert(void);
  Alert(const char *text, uint16_t color = WHITE, bool framed = false);
  Alert &set(const char *text, uint16_t color = WHITE, bool framed = false);
  Alert &add(const char *text, uint16_t color = WHITE, int size = 1);
  void visible(void);
  void remove(void);
  void show(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

 private:
  char _text[5][40];
  uint16_t _color[5];
  int _size[5];
  int _counter = 0;
  bool _visible = false;
  bool _framed;
};

#endif