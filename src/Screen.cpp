/**
 * @file Screen.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-21
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "Screen.h"

#include <math.h>

#include "Particle.h"

extern DisplayDriver display;

static const unsigned long SCREEN_REFRESH_MS = 100;

Screen::Screen(int topBarHeight, int bottomBarHeight, color_t bgColor,
               color_t borderColor, color_t topBarBgColor,
               color_t bottomBarBgColor)
    : window(topBarHeight, bottomBarHeight, bgColor, borderColor, topBarBgColor,
             bottomBarBgColor),
      bgColor(bgColor) {}

void Screen::showTopBar(bool enabled) { window.showTopBar(enabled); }

void Screen::showBottomBar(bool enabled) { window.showBottomBar(enabled); }

void Screen::clear(void) {
  display.fill(bgColor);
  window.clear();
}

void Screen::draw(void) { window.draw(); }

void Screen::refresh(bool force) {
  if (force || checkTimer(_refreshTimer, 100)) {
    window.refresh(force);
  }
}

void Screen::showTime(bool enabled) { window.topBar.showTime(enabled); }

// void Screen::bigClock(bool enabled = true) {
//   showTime(!enabled);
//   _bigClock = enabled;
//   _countdownStart = millis();
// }

// void Screen::wipePanel(bool hasProgressBar) {
//   display.fillRect(0, FIRST_ROW, display.width(),
//                    display.height() - FIRST_ROW - (hasProgressBar ? 16 :
//                    0), BLACK);
// }

void Screen::showSignal(bool enabled) { window.topBar.showSignal(enabled); }

// void Screen::signalDisplay(bool show) {
//   int signal = show ? display.getSignal() : -1;
//   if (_previousSignal != signal || signal < 0) {
//     display.fillRect(SIGNAL_LEFT, SIGNAL_TOP, SIGNAL_WIDTH, SIGNAL_HEIGHT,
//                      BLACK);
//   }
//   /*if (signal<0) {
//       return;
//   }*/
//   for (uint16_t i = 1; i <= 3; i++) {
//     uint16_t x = SIGNAL_LEFT + 4 * (i - 1);
//     uint16_t y = SIGNAL_TOP + SIGNAL_HEIGHT - 1;
//     uint16_t w = 3;
//     uint16_t h = i * 2;
//     if (i <= signal) {
//       uint16_t indicatorColor = DARKBLUE;
//       switch (signal) {
//         case 1:
//         case 2:
//         case 3:
//           indicatorColor = WHITE;
//           break;
//         default:
//           indicatorColor = DARKBLUE;
//           break;
//       }
//       display.fillRect(x, y - h, w, h, indicatorColor);
//     } else {
//       display.drawRect(x, y - h, w, h, DARKBLUE);
//     }
//   }
//   // if (signal <= 0) {
//   //
//   display.drawLine(SIGNAL_LEFT+2,SIGNAL_TOP+SIGNAL_HEIGHT-1,SIGNAL_LEFT+SIGNAL_WIDTH-1,SIGNAL_TOP,RED);
//   //     display.drawLine(SIGNAL_LEFT + 2, SIGNAL_TOP,
//   //                        SIGNAL_LEFT + SIGNAL_WIDTH - 1,
//   //                        SIGNAL_TOP + SIGNAL_HEIGHT - 1, RED);
//   // }
// }

// void Screen::drawBattery(uint16_t color, uint8_t percentile, bool
// charging) {
//   uint16_t batteryColor = WHITE;
//   if (!percentile) {
//     batteryColor = RED;
//   }
//   display.drawRect(display.width() - 16, TOP_ROW + 1, 12, 7, batteryColor);
//   display.drawFastVLine(display.width() - 2, TOP_ROW + 3, 3, batteryColor);
//   display.fillRect(display.width() - 15, TOP_ROW + 2, (uint16_t)percentile
//   / 10,
//                    5, color);
//   if (charging) {
//     // charging symbol?
//   }
// }

// void Screen::drawPlug(void) {
//   display.showText(TOP_ROW, display.width() - 28, "AC", 1, WHITE);
//   display.drawFastHLine(display.width() - 12, TOP_ROW + 4, 2, WHITE);
//   display.drawFastVLine(display.width() - 10, TOP_ROW + 2, 5, WHITE);
//   display.drawRect(display.width() - 9, TOP_ROW + 2, 3, 5, WHITE);
//   display.drawFastVLine(display.width() - 5, TOP_ROW + 1, 7, WHITE);
//   display.drawFastHLine(display.width() - 3, TOP_ROW + 2, 3, WHITE);
//   display.drawFastHLine(display.width() - 3, TOP_ROW + 6, 3, WHITE);
// }

// void Screen::showBatteryIndicator(bool forceRefresh) {
//   if (_batteryLevel == display._batteryLevel && !forceRefresh) {
//     return;
//   }
//   display.fillRect(display.width() - 30, TOP_ROW, 30, 8, BLACK);
//   _batteryLevel = display._batteryLevel;
//   switch (_batteryLevel) {
//     case 0:
//       drawBattery(RED, 0);
//       break;
//     case 1:
//       drawBattery(RED, 20);
//       break;
//     case 2:
//       drawBattery(ORANGE, 40);
//       break;
//     case 3:
//       drawBattery(GREEN, 100);
//       break;
//     case 4:
//     default:
//       drawPlug();
//       break;
//   }
// }

// void Screen::showMemoryIndicator(void) {
//   if (checkTimer(_memoryOperationTimer, DISK_INDICATOR_DURATION_MS)) {
//     display._memoryOperation = false;
//   }
//   if (!memory.isPresent()) {
//     display.showText(SECOND_LINE + 1, 0, "SD", 1, RED);
//     return;
//   }
//   if (_memoryOperation == display._memoryOperation) {
//     return;
//   }
//   _memoryOperation = display._memoryOperation;
//   if (_memoryOperation) {
//     display.showText(SECOND_LINE + 1, 0, "S", 1, GREEN);
//   } else {
//     display.fillRect(0, SECOND_LINE + 1, display.textWidth("S"), 8, BLACK);
//   }
// }

// void Screen::showSensorIndicator(void) {
//   char buffer[2];
//   if (_activeSensor == display._activeSensor) {
//     return;
//   }
//   display.fillRect(0, display.height() - 8, 8, 8, BLACK);
//   if (display._activeSensor >= 0) {
//     buffer[0] = '0' + display._activeSensor;
//     buffer[1] = 0;
//     display.showText(display.height() - 8, 0, buffer, 1, MAGENTA);
//   }
//   _activeSensor = display._activeSensor;
// }

// void Screen::showConnectionIndicator(void) {
//   String connectionType = "";
//   /*if ((_connectionType == display._connectionType
//       && _connectionState == display._connectionState)
//       && (display._connectionState != CONNECTING &&
//       display._connectionState
//       !=
//   CONNECTED) ) { display.fillRect(0,0,16,8,BLACK); hideSignalDisplay();
//   _blinkOn = false; return;
//   }*/

//   if (display._connectionState == CONNECTED) {
//     _blinkOn = false;
//   } else if (checkTimer(_blinkTimer, INDICATOR_BLINKING_INTERVAL_MS)) {
//     _blinkOn = !_blinkOn;
//   }

//   // _blinkOn = false; // no blinking for now

//   if (_connectionType != display._connectionType || _blinkOn) {
//     display.fillRect(0, 0, 16, 8, BLACK);
//     hideSignalDisplay();
//   }

//   if (_blinkOn) {
//     return;
//   }

//   _connectionType = display._connectionType;
//   _connectionState = display._connectionState;

//   signalDisplay();
//   display.fillRect(SIGNAL_TYPE_LEFT, SIGNAL_TYPE_TOP, SIGNAL_TYPE_WIDTH,
//                    SIGNAL_HEIGHT, BLACK);
//   switch (display.getSignalType()) {
//     case Connector::SIGNAL_2G:
//       connectionType = LABEL_2G;
//       break;
//     case Connector::SIGNAL_3G:
//       connectionType = LABEL_3G;
//       break;
//     case Connector::SIGNAL_LTE:
//       connectionType = LABEL_LTE;
//       break;
//     case Connector::SIGNAL_SAT:
//       connectionType = LABEL_SAT;
//       break;
//     default:
//       connectionType = "";
//       break;
//   }
//   display.showText(SIGNAL_TYPE_TOP, SIGNAL_TYPE_LEFT, connectionType, 1,
//   WHITE);
// }

// void Screen::refresh(bool forceRefresh) { show(forceRefresh); }

// void Screen::showSensors(uint16_t x) {
//   uint16_t color;
//   for (int i = 0; i < MAX_SENSORS; i++) {
//     color = display._sensorPresent[i] ? GREEN : RED;
//     display.drawFastVLine(x - 2, display.height() - MAX_SENSORS * 4 + (i *
//     4),
//                           3, color);
//     display.drawFastVLine(x - 1, display.height() - MAX_SENSORS * 4 + (i *
//     4),
//                           3, color);
//     display.drawFastHLine(x, display.height() - MAX_SENSORS * 4 + (i * 4),
//     3,
//                           color);
//   }
// }

void Screen::showProgress(int value) {}

void Screen::hideProgressBar(void) {}

/**
 * @brief present alert on screen
 * 
 * @param alert 
 */
void Screen::alert(Alert &alert) {
  alert.visible();
  window.alert = &alert;
  _updated = true;
  refresh(); 
}

/**
 * @brief Remove alert from screen
 * 
 */
void Screen::endAlert(void) {
  window.alert = NULL;
  _updated = true;
}

void Screen::show() {
  // showRGBLed();
  /*showSensors(display.width()-1);*/

  window.draw();
}

void Screen::setStatus(const char *status) {
  window.bottomBar.setStatus(status);
}

// void Screen::showTime() {
//   if (Time.now() == _lastTimeRead) {
//     return;
//   }
//   _lastTimeRead = Time.now();
//   display.fillRect(32, TOP_ROW, 64, ROW_HEIGHT, BLACK);
//   if (_showTime) {
//     // display.setFont(GLCDFONT);
//     display.centerText(TOP_ROW,
//                        Time.isValid() ? Time.format(_lastTimeRead,
//                        "%H:%M:%S")
//                                       : String("--:--:--"),
//                        1, false, WHITE);
//     // display.setFont(ARIAL_8);
//   } else if (_bigClock) {
//     return panelClock();
//   }
// }

// void Screen::setCountdownDurationMS(unsigned long durationMS) {
//   _countdownDuration = durationMS;
// }

// void Screen::panelClock(void) {
//   time_t timeNow = Time.now();
//   unsigned long diffSec = 0;
//   if (timeNow == _panelClockRead) {
//     return;
//   }
//   diffSec = timeNow - _panelClockRead;
//   _panelClockRead = timeNow;

//   display.setFont(DEFAULT_FONT);
//   // display.fillRect(0,FIRST_ROW+10,display.width(),30,BLACK);
//   // display a shortening line
//   uint8_t timePassed = (millis() - _countdownStart >= _countdownDuration)
//                            ? 255
//                            : floor(256 * (float)(millis() -
//                            _countdownStart)
//                            /
//                                    _countdownDuration);
//   uint16_t color = display.Color565(timePassed, 255 - timePassed, 0);
//   int16_t lineLength = floor((display.width() - 30) * timePassed) / 255;

//   uint16_t charWidth = display.charWidth('x') * 2;
//   uint16_t clockWidth = charWidth * 8;
//   uint16_t pos = charWidth;
//   if (diffSec >= 10 || timeNow % 10 == 0) {
//     pos += charWidth;
//   }
//   if (diffSec >= 60 || timeNow % 60 == 0) {
//     pos += 2 * charWidth;
//   }
//   if (diffSec >= 600 || timeNow % 600 == 0) {
//     pos += charWidth;
//   }
//   if (diffSec >= 3600 || timeNow % 3600 == 0) {
//     pos += 2 * charWidth;
//   }
//   if (diffSec >= 36000 || timeNow % 36000 == 0) {
//     pos += charWidth;
//   }

//   display.fillRect(display.width() - (display.width() - clockWidth) / 2 -
//   pos,
//                    FIRST_ROW + 15, pos, 19, BLACK);
//   display.centerText(FIRST_ROW + 15, Time.format(_panelClockRead,
//   "%H:%M:%S"),
//                      2, false, color);

//   display.fillRoundRect((display.width() + clockWidth) / 2 + 5, FIRST_ROW +
//   15,
//                         8, 8, 4, _saveMode ? BLUE : BLACK);

//   display.drawFastHLine(15, FIRST_ROW + 35, display.width() - 30,
//   DARKBLUE); display.drawFastHLine(15, FIRST_ROW + 35, lineLength, WHITE);

//   long timeLeft = (_countdownDuration - (millis() - _countdownStart)) /
//   1000; display.fillRect(0, display.height() - 9 - ROW_SPACING,
//   display.width() - 10,
//                    9 + ROW_SPACING, BLACK);
//   display.centerText(display.height() - 8,
//                      String::format("%02d:%02d:%02d", timeLeft / 3600,
//                                     (timeLeft % 3600) / 60, timeLeft % 60),
//                      1, false, YELLOW);

//   display.setFont(ARIAL_8);
//   _updated = true;
// }

// void Screen::showRGBLed(void) {
//   uint16_t ledColor;
//   if (display.ledChanged(ledColor)) {
//     display.fillRoundRect(display.width() - 8, SECOND_LINE, 8, 8, 4,
//     ledColor);
//   }
// }

void Screen::initTimer(unsigned long &timer) { timer = millis(); }

bool Screen::checkTimer(unsigned long &timer, unsigned long durationMS) {
  if (millis() - timer >= durationMS) {
    initTimer(timer);
    return true;
  }
  return false;
}
