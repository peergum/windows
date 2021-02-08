/**
 * @file Screen.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-21
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#ifndef __SCREEN_H
#define __SCREEN_H

#include "Alert.h"
// #include "BottomBar.h"
#include "DisplayDriver.h"
// #include "TopBar.h"
#include "Window.h"

class Screen {
 public:
  Screen(int topBarHeight, int bottomBarHeight, color_t bgColor = BG_COLOR,
         color_t borderColor = BORDER_COLOR, color_t topBarBgColor = TOPBAR_BG_COLOR,
         color_t bottomBarBgColor = BOTTOMBAR_BG_COLOR);
  void clear(void);

  void draw(void);

  void showSignal(bool enabled);
  // void signalDisplay(bool show = true);
  void create(const char *title, const char *subtitle = "");
  void update(const char *title, const char *subtitle = "");
  void setStatus(const char *status);
  void show(void);
  void showTime(bool enabled);
  void showTopBar(bool enabled);
  void showBottomBar(bool enabled);

  // void bigClock(bool enabled);
  // void wipePanel(bool hasProgressBar = false);
  void refresh(bool force = false);
  // void setCountdownDurationMS(unsigned long durationMS);
  // void showRGBLed(void);
  // void showMemoryIndicator(void);
  // void showSensorIndicator(void);
  // void showConnectionIndicator(void);
  // void showBatteryIndicator(bool forceRefresh = false);

  void alert(Alert &alert);

  void showProgress(int value = -1);
  void hideProgressBar(void);
  // void drawBattery(uint16_t color, uint8_t percentile, bool charging =
  // false); void drawPlug(void);

  // Display *_display;
  // Panel *_panel = NULL;
  // CenteredPanel *_cpanel = NULL;
  // RealtimePanel *_rtpanel = NULL;

  // Panel *_activePanel = NULL;

  // unsigned long _displayDelay = 1000;
  Window window;

 protected:
 private:
  bool _updated = false;
  unsigned long _refreshTimer = 0;
  color_t bgColor;

  bool _showTime = true;
  bool _bigClock = false;

  void showTime(void);
  void panelClock(void);
  void initTimer(unsigned long &timer);
  bool checkTimer(unsigned long &timer, unsigned long durationMS);
  void showSensors(uint16_t y);

  uint8_t _activeSensor = -1;
  bool _memoryOperation = false;
  uint8_t _batteryLevel = 255;

  unsigned long _indicatorTimer = 0;
  unsigned long _blinkTimer = 0;
  bool _blinkOn = false;
  int _previousSignal = -1;
};

#endif
