/**
 * @file CommIndicator.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "CommIndicator.h"

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
CommIndicator::CommIndicator(int x, int y, color_t bgColor)
    : Indicator(x, y, COMM_INDICATOR_WIDTH, COMM_INDICATOR_HEIGHT, bgColor),
      blinkPeriod(BLINK_PERIOD_MS) {
}

/**
 * @brief draw Comm Indicator
 *
 */
void CommIndicator::draw(void) {
  if (!visible) {
    Indicator::remove();
    return;
  }
  toggle = ((millis() % blinkPeriod) < blinkPeriod / 2);
  if (callback) {
    callback(signal, type, state);
  }
  switch ((ConnectionState)state) {
    case NOT_CONNECTED:
      // case NOT_CONNECTED:
      // case SWITCH_CELL_OFF:
      remove();
      break;
    case SELECTED:
      // case CONNECT:
      // case CONNECT_3G:
      // case SWITCH_TO_SAT:
      // case CONNECT_SAT:
      // case DISCONNECTED:
      // case DISCONNECTING:
      // case LIGHT_DISCONNECT:
      drawSignal(WHITE, 0);
      break;
    case CONNECTING:
      // case CONNECTING:
      // case LIGHT_RECONNECT:
      if (toggle) {
        remove();
      } else {
        drawSignal(WHITE, signal);
      }
      break;
    case CONNECTED:
      // case CONNECTED:
      // drawShadow(DARKBLUE);
      drawSignal(WHITE, signal);
      break;
    case FAILED:
      // case SAT_TIMEOUT:
      // case CONNECTION_FAILED:
      drawSignal(WHITE, -1);
      break;
    default:
      break;
  }
}

/**
 * @brief refresh indicator
 *
 * @param force
 */
void CommIndicator::refresh(bool force) {
  if (force || checkTimer(_refreshTimer, 500UL)) {
    draw();
  }
}

/**
 * @brief Undraw CommIndicator
 *
 */
void CommIndicator::remove(void) { drawSignal(bgColor, -1); }

static uint16_t signalbars[4] = {1, 3, 5, 7};
static uint16_t signalcolors[4] = {COMM_INDICATOR_RED, COMM_INDICATOR_YELLOW,
                                   COMM_INDICATOR_YELLOW, COMM_INDICATOR_GREEN};

void CommIndicator::drawSignal(uint16_t color, int signal) {
  for (uint16_t i = 0; i < 4; i++) {
    uint16_t xi = x + 1 + 3 * i;
    uint16_t yi = y + h;
    uint16_t wi = 2;
    uint16_t hi = signalbars[i];
    uint16_t indicatorColor;
    if (signal < 0) {
      indicatorColor = TOPBAR_BG_COLOR;
    } else if (i < signal) {
      indicatorColor = signalcolors[i];
    } else {
      indicatorColor = COMM_INDICATOR_BG_COLOR;
    }
    display.fillRect(xi, yi - hi, wi, hi, indicatorColor);
  }
}