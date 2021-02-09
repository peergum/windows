/**
 * @file Window.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-21
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __WINDOW_H
#define __WINDOW_H

#include "Frame.h"
#include "TopBar.h"
#include "BottomBar.h"
#include "ProgressBar.h"
#include "Alert.h"
#include "screendefs.h"

typedef enum {
  ALIGN_LEFT,
  ALIGN_RIGHT,
  ALIGN_CENTER,
} Alignment;

typedef struct {
  int16_t x;
  int16_t y;
  int16_t labelWidth;
  int16_t valueWidth;
  uint8_t labelAlign;
  uint8_t valueAlign;
  char label[40] = { 0 };
  float value;
  uint8_t decimals;
  char sValue[40] = { 0 };
  char unit[5] = { 0 };
  color_t labelColor = DEFAULT_LABEL_COLOR;
  color_t valueColor = DEFAULT_VALUE_COLOR;
  bool frame = false;
  bool set = false;
  uint8_t size = 1;
} Field;

class Window : public Frame {
public:
  Window(int topBarHeight, int bottomBarHeight, color_t bgColor,
    color_t borderColor, color_t topBarBgColor, color_t bottomBarBgColor);
  void clear(void);
  void draw(void);
  void refresh(bool force = false);
  void showTopBar(bool enabled);
  void showBottomBar(bool enabled);

  void setFieldDefaults(int index);
  Window& initFields(uint16_t labelWidth, uint16_t valueWidth,
    Alignment labelAlign, Alignment valueAlign,
    color_t labelColor = DEFAULT_LABEL_COLOR);
  Window& addFloat(const char* label, float floatValue, int decimals,
    color_t color = DEFAULT_VALUE_COLOR);
  Window& addInt(const char* label, int intValue,
    color_t color = DEFAULT_VALUE_COLOR);
  Window& addText(const char* label, const char* text,
    color_t color = DEFAULT_VALUE_COLOR);

  void updateFloat(int fieldIndex, float value);
  void updateInt(int fieldIndex, int value);
  void updateText(int fieldIndex, const char* text);

  void setProgressBar(ProgressBar *bar);
  void setProgress(int progress);

  TopBar topBar;
  BottomBar bottomBar;
  Alert* alert;

protected:
  ProgressBar* progressBar;

private:
  void initTimer(unsigned long& timer);
  bool checkTimer(unsigned long& timer, unsigned long durationMS);

  bool topBarVisible = false;
  bool bottomBarVisible = false;
  int topBarHeight;
  int bottomBarHeight;

  void drawField(int index, bool valueOnly = false);
  Field _fields[10];
  Alignment _labelAlign, _valueAlign;
  uint16_t _labelWidth, _valueWidth, _labelColor;
  int _count = 0;
  uint16_t _fieldY;
  bool _updated = false;
  unsigned long _refreshTimer;
};

#endif