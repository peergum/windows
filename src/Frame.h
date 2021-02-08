#ifndef __FRAME_H
#define __FRAME_H

#include "Particle.h"
#include "screendefs.h"

class Frame {
 public:
  Frame(int x, int y, int w, int h, uint16_t bgColor = BG_COLOR,
        uint16_t borderColor = BORDER_COLOR, bool hasTopBorder = false, bool hasBottomBorder = false);
  void clear(void);
  virtual void draw(void);
  virtual void refresh(bool force = false);

public:
  int _x;
  int _y;
  int _w;
  int _h;

 protected:
  bool hasTopBorder = false;
  bool hasBottomBorder = false;
  uint16_t _bgColor;

 private:
  uint16_t _borderColor;
  bool _visible = false;
};

#endif