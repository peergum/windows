/**
 * @file TopBar.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-29
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __TOPBAR_H
#define __TOPBAR_H

#include "BatteryIndicator.h"
#include "CommIndicator.h"
#include "Frame.h"
#include "TimeIndicator.h"
#include "screendefs.h"

class TopBar : public Frame {
 public:
  TopBar(int h, color_t bgColor, color_t borderColor);
  void clear(void);
  void draw(void);
  void refresh(bool force = false);
  void showTime(bool enabled);
  void showSignal(bool enabled);

  CommIndicator commIndicator;
  TimeIndicator timeIndicator;
  BatteryIndicator batteryIndicator;

  protected:
  
  //  MemoryIndicator memoryIndicator;
 private:
};

#endif