/**
 * @file TimeIndicator.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-31
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __TIMEINDICATOR_H
#define __TIMEINDICATOR_H

#include "Indicator.h"

class TimeIndicator : public virtual Indicator {
 public:
  TimeIndicator(int x, int y, uint16_t color, uint16_t bgColor);
  void draw(void);
  void refresh(bool force);

 private:
  uint16_t color;
};

#endif