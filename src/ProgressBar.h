/**
 * @file ProgressBar.h
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-08
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#ifndef __PROGRESSBAR_H
#define __PROGRESSBAR_H

#include "Frame.h"
#include "screendefs.h"

class ProgressBar : public Frame {
 public:
  ProgressBar(int x, int y, int w, int h, int r, color_t color1 = PROGRESSBAR_COLOR_1,
              color_t color2 = PROGRESSBAR_COLOR_2, color_t bgColor = BG_COLOR,
              color_t borderColor = BORDER_COLOR);
  void draw(void);
  void refresh(bool force = false);

  int progress = 0; //!< 0 to 100 %
 private:
  color_t color1, color2;
  int radius;
  unsigned long _refreshTimer;
  int color1Count = 3; 
  int color2Count = 8; 
  unsigned long refreshRateMS = 100UL;
};

#endif