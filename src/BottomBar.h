#ifndef __BOTTOMBAR_H
#define __BOTTOMBAR_H

#include "CommIndicator.h"
#include "Frame.h"

class BottomBar : public Frame {
 public:
  BottomBar(int h, color_t bgColor = BG_COLOR,
            color_t borderColor = BORDER_COLOR);
  void clear(void);
  void draw(void);
  void refresh(bool force = false);
  void setStatus(const char *status);

 private:
  char _content[40];
  bool _updated = false;
  //  CommIndicator commIndicator;
  //  BatteryIndicator batteryIndicator;
  //  TimeIndicator timeIndicator;
  //  MemoryIndicator memoryIndicator;
};

#endif