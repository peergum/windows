/**
 * @file CommIndicator.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __COMM_INDICATOR_H
#define __COMM_INDICATOR_H

#include "Indicator.h"

typedef enum {
  NOT_CONNECTED,
  SELECTED,
  CONNECTING,
  CONNECTED,
  FAILED,
} ConnectionState;

class CommIndicator : public virtual Indicator {
 public:
  CommIndicator(int x, int y, color_t bgColor);
  void draw(void);
  void refresh(bool force);
  void remove(void);

 private:
  void drawShadow(uint16_t color);
  void drawSignal(uint16_t color, int signal);

  int signal = 0;
  int type = 0;
  int state = 0;
  
  bool toggle = false;
  unsigned long blinkPeriod;
};

#endif