/**
 * @file Indicator.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __INDICATOR_H
#define __INDICATOR_H

#include "Particle.h"
#include "screendefs.h"

class Indicator {
 public:
  Indicator(int x, int y, int w, int h, color_t bgColor, color_t color = WHITE);
  virtual void draw(void);
  virtual void refresh(void);
  virtual void remove(void);
  void setCallback(void (*cb)(int &value, int &type, int &state));

  bool visible;
  
 protected:
  void initTimer(unsigned long &timer);
  bool checkTimer(unsigned long &timer, unsigned long durationMS);
  
  int x;
  int y;
  int w;
  int h;
  color_t bgColor;
  color_t color;
  bool updated;
  unsigned long _refreshTimer;
  void (*callback)(int &value, int &type, int &state);

};

#endif