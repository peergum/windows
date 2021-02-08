/**
 * @file Window.cpp
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief
 * @version 0.1
 * @date 2021-01-19
 *
 * @copyright (c) 2021, WaterlooTI
 *
 */

#include "Window.h"
#include "DisplayDriver.h"

extern DisplayDriver display;

#define DRAW_VALUE_ONLY true

/**
 * @brief Construct a new Window:: Window object
 *
 * @param topBarHeight
 * @param bottomBarHeight
 * @param bgColor
 * @param borderColor
 */
Window::Window(int topBarHeight, int bottomBarHeight, color_t bgColor,
               color_t borderColor, color_t topBarBgColor,
               color_t bottomBarBgColor )
    : Frame(0, 0, display.width(), display.height(), bgColor, borderColor),
      topBar(topBarHeight, topBarBgColor, borderColor),
      bottomBar(bottomBarHeight, bottomBarBgColor, borderColor),
      topBarVisible(false),
      bottomBarVisible(false),
      alert(NULL) {}

/**
 * @brief clear window
 *
 */
void Window::clear(void) {
  Frame::clear();
  if (topBarVisible) {
    topBar.clear();
  }
  if (bottomBarVisible) {
    bottomBar.clear();
  }
}

/**
 * @brief draw window
 *
 */
void Window::draw(void) {
  if (topBarVisible) {
    topBar.draw();
  }
  if (bottomBarVisible) {
    bottomBar.draw();
  }

  for (int i = 0; i < _count; i++) {
    drawField(i);
  }
  _updated = false;
}

/**
 * @brief redraw window
 *
 * @param force
 */
void Window::refresh(bool force) {
  if (force || _updated || checkTimer(_refreshTimer, REFRESH_TIMER_MS)) {
    if (topBarVisible) {
      topBar.refresh(force);
    }
    if (bottomBarVisible) {
      bottomBar.refresh(force);
    }

    if (_updated) {
      for (int i = 0; i < _count; i++) {
        drawField(i, DRAW_VALUE_ONLY);
      }
      if (alert) {
        alert->show(_x, _y, _w, _h);
      }
    }
    _updated = false;
  }
}

/**
 * @brief activate top bar
 *
 * @param enabled
 */
void Window::showTopBar(bool enabled) {
  topBarVisible = enabled;
  if (enabled) {
    _y = topBar._h + 1;
  } else {
    _y = 0;
  }
  Serial.printlnf("y = %d",_y);
  _h = display.height() - _y - bottomBarVisible ? (bottomBarHeight + 1) : 0;
  clear();
  draw();
}

/**
 * @brief activate bottom bar
 *
 * @param enabled
 */
void Window::showBottomBar(bool enabled) {
  bottomBarVisible = enabled;
  _h = display.height() - _y - (topBarVisible ? (topBarHeight + 1) : 0) -
       (bottomBarVisible ? (bottomBarHeight + 1) : 0);
  clear();
  draw();
}

/**
 * @brief Initialize default field values and reset counter
 *
 * @param labelWidth
 * @param valueWidth
 * @param labelAlign
 * @param valueAlign
 * @param labelColor
 * @return Window&
 */
Window& Window::initFields(uint16_t labelWidth, uint16_t valueWidth,
                           Alignment labelAlign, Alignment valueAlign,
                           uint16_t labelColor) {
  _fieldY = 1;
  _labelAlign = labelAlign;
  _valueAlign = valueAlign;
  _labelWidth = labelWidth;
  _valueWidth = valueWidth;
  _labelColor = labelColor;
  _count = 0;
  return *this;
}

/**
 * @brief Set the field default values
 *
 * @param index
 */
void Window::setFieldDefaults(int index) {
  _fields[index].labelColor = _labelColor;
  _fields[index].labelWidth = _labelWidth;
  _fields[index].valueWidth = _valueWidth;
  _fields[index].labelAlign = _labelAlign;
  _fields[index].valueAlign = _valueAlign;
  _fields[index].y = 10 * index;
  _fields[index].x = 1;
}

/**
 * @brief add a float field
 *
 * @param label
 * @param floatValue
 * @param decimals
 * @param color
 * @return Window&
 */
Window& Window::addFloat(const char* label, float floatValue, int decimals,
                    color_t color) {
  setFieldDefaults(_count);
  strcpy(_fields[_count].label, label);
  _fields[_count].value = floatValue;
  _fields[_count].decimals = decimals;
  _fields[_count].valueColor = color;
  _fields[_count].sValue[0] = 0;
  _count++;
  return *this;
}

/**
 * @brief add a int field
 *
 * @param label
 * @param intValue
 * @param color
 * @return Window&
 */
Window& Window::addInt(const char* label, int intValue, color_t color) {
  return addFloat(label, (float)intValue, 0, color);
}

/**
 * @brief add a text field
 *
 * @param label
 * @param text
 * @param color
 * @return Window&
 */
Window& Window::addText(const char* label, const char* text, color_t color) {
  setFieldDefaults(_count);
  strcpy(_fields[_count].label, label);
  strcpy(_fields[_count].sValue, text);
  _fields[_count].valueColor = color;
  _count++;
  return *this;
  ;
}

/**
 * @brief draw a full field or refresh the value
 *
 * @param field
 */
void Window::drawField(int index, bool valueOnly) {
  uint16_t textWidth;
  uint16_t x,y ;
  y = _y + _fields[index].y;
  Serial.println(y);
  if (!valueOnly) {
    textWidth = display.textWidth(_fields[index].label);
    x = _x + _fields[index].x;
    if (_fields[index].labelAlign == ALIGN_RIGHT) {
      x += _fields[index].labelWidth - textWidth;
    } else if (_fields[index].labelAlign == ALIGN_CENTER) {
      x += (_fields[index].labelWidth - textWidth) / 2;
    }

    display.setCursor(x, y);
    display.setTextSize(_fields[index].size);
    display.setTextColor(_fields[index].labelColor);
    display.print(_fields[index].label);
    // if (_fields[index].labelAlign == ALIGN_LEFT) {
    //   display.drawFastHLine(x+textWidth,y+9,_fields[index].labelWidth-textWidth,DARKBLUE);
    // }
  }
  char value[40];
  sprintf(value, "%.*f", _fields[index].decimals, _fields[index].value);
  textWidth = display.textWidth(value);
  x = _x + _fields[index].x + _fields[index].labelWidth;
  display.fillRect(x,y,_fields[index].valueWidth,9,_bgColor);
  if (_fields[index].valueAlign == ALIGN_RIGHT) {
    x += _fields[index].valueWidth - textWidth;
  } else if (_fields[index].valueAlign == ALIGN_CENTER) {
    x += (_fields[index].valueWidth - textWidth) / 2;
  }
  display.setCursor(
      x, _y + _fields[index].y);
  display.setTextSize(_fields[index].size);
  display.setTextColor(_fields[index].valueColor);
  display.print(value);
    // if (_fields[index].valueAlign == ALIGN_RIGHT) {
    //   display.drawFastHLine(_x + _fields[index].x + _fields[index].labelWidth,y+9,_fields[index].labelWidth-textWidth,DARKBLUE);
    // }

}

/**
 * @brief update float field
 *
 * @param field
 * @param value
 */
void Window::updateFloat(int fieldIndex, float value) {
  _fields[fieldIndex].value = value;
  _updated = true;
}

/**
 * @brief update int field
 *
 * @param field
 * @param value
 */
void Window::updateInt(int fieldIndex, int value) {
  _fields[fieldIndex].value = value;
  _updated = true;
}

/**
 * @brief update text field
 * 
 * @param fieldIndex 
 * @param text 
 */
void Window::updateText(int fieldIndex, const char *text) {
  strcpy(_fields[fieldIndex].sValue,text);
  _updated = true;
}

void Window::initTimer(unsigned long &timer) { timer = millis(); }

bool Window::checkTimer(unsigned long &timer, unsigned long durationMS) {
  if (millis() - timer >= durationMS) {
    initTimer(timer);
    return true;
  }
  return false;
}
