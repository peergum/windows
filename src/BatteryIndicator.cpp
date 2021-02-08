/**
 * @file BatteryIndicator.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "BatteryIndicator.h"

#include "DisplayDriver.h"
#include "screendefs.h"

extern DisplayDriver display;

/**
 * @brief Construct a new Comm Indicator:: Comm Indicator object
 *
 * @param x
 * @param y
 * @param bgColor
 */
BatteryIndicator::BatteryIndicator(int x, int y, uint16_t bgColor)
    : Indicator(x, y, BATTERY_INDICATOR_WIDTH, BATTERY_INDICATOR_HEIGHT,
                bgColor),
      blinkPeriod(BLINK_PERIOD_MS) {}

/**
 * @brief draw plug symbol
 * 
 */
void BatteryIndicator::drawPlug(void) {
  // display.showText(x, y, "AC", 1, WHITE);
  display.drawFastHLine(x, y + 4, 2, BATTERY_COLOR_GREEN);
  display.drawFastVLine(x + 2, y + 2, 5, BATTERY_COLOR_GREEN);
  display.drawRect(x + 3, y + 2, 3, 5, BATTERY_COLOR_GREEN);
  display.drawFastVLine(x + 7, y + 1, 7, BATTERY_COLOR_GREEN);
  display.drawFastHLine(x + 9, y + 2, 3, BATTERY_COLOR_GREEN);
  display.drawFastHLine(x + 9, y + 6, 3, BATTERY_COLOR_GREEN);
}

/**
 * @brief draw battery symbol
 * 
 * @param color 
 * @param percentile 
 * @param charging 
 */
void BatteryIndicator::drawBattery(uint16_t color, uint8_t percentile,
                                   bool charging) {
  uint16_t batteryColor = color;
  // if (!percentile) {
  //   batteryColor = RED;
  // }
  display.drawRect(x, y + 1, 12, 7, batteryColor);
  display.drawFastVLine(x + 14, y + 3, 3, batteryColor);
  display.fillRect(x + 1, y + 2, (uint16_t)percentile / 10, 5, color);
  if (charging) {
    // charging symbol?
  }
}

/**
 * @brief draw indicator
 * 
 */
void BatteryIndicator::draw(void) {
  if (!visible) {
    remove();
    return;
  }
  int level, type, state;
  if (callback) {
    callback(level, type, state);
  }
  if (level == batteryLevel) {
    return;
  }
  display.fillRect(x, y, w, h, bgColor);

  switch (level) {
    case 0:
      drawBattery(BATTERY_COLOR_RED, 0);
      break;
    case 1:
      drawBattery(BATTERY_COLOR_RED, 20);
      break;
    case 2:
      drawBattery(BATTERY_COLOR_GREEN, 40);
      break;
    case 3:
      drawBattery(BATTERY_COLOR_GREEN, 100);
      break;
    case 4:
    default:
      drawPlug();
      break;
  }
  batteryLevel = level;
}

/**
 * @brief refresh indicator
 * 
 * @param force 
 */
void BatteryIndicator::refresh(bool force) { draw(); }

/**
 * @brief Undraw BatteryIndicator
 *
 */
void BatteryIndicator::remove(void) { display.fillRect(x, y, w, h, bgColor); }
