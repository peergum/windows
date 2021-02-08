/**
 * @file BatteryIndicator.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __BATTERY_INDICATOR_H
#define __BATTERY_INDICATOR_H

#include "Indicator.h"

class BatteryIndicator : public virtual Indicator {
 public:
  BatteryIndicator(int x, int y, uint16_t bgColor);
  void draw(void);
  void refresh(bool force);
  void remove(void);

 private:
  void drawPlug(void);
  void drawBattery(uint16_t color, uint8_t percentile, bool charging = false);

  int batteryLevel = 0;
  bool toggle = false;
  unsigned long blinkPeriod;
};

#endif