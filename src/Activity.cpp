/**
 * @file Activity.cpp
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-09
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#include "Activity.h"

#include "DisplayDriver.h"

extern DisplayDriver display;

/**
 * @brief Construct a new Activity:: Activity object
 *
 * @param x
 * @param y
 * @param w
 * @param h
 * @param bgColor
 * @param color
 */
Activity::Activity(int x, int y, int w, int h, color_t color, color_t bgColor) : Frame(x, y, w, h, bgColor, bgColor),
color(color) {

}

/**
 * @brief clear activity indicator
 *
 */
void Activity::clear(void) {
    Frame::clear();
}

/**
 * @brief draw activity indicator
 *
 */
void Activity::draw(void) {
    clear();
    start = end = 0;
    direction = 1;
    refresh(true);
}

/**
 * @brief refresh activity indicator
 *
 * @param force
 */
void Activity::refresh(bool force) {
    if (force || checkTimer(_refreshTimer, 10UL)) {
        int xs = _x + (_w - 1) * start / 100;
        int xe = _x + (_w - 1) * end / 100;
        if (xs > _x) {
            display.fillRect(_x, _y, (xs - _x), _h, _bgColor);
        }
        display.fillRect(xs, _y, (xe - xs), _h, color);
        if (xe < _x + _w) {
            display.fillRect(xe, _y, _x + _w - 1 - xe, _h, _bgColor);
        }
        if (direction > 0 && end < 100) {
            end += direction;
        }
        else if (direction > 0 && start<100) {
            start += direction;
        }
        else if (direction < 0 && start>0) {
            start += direction;
        }        
        else if (direction < 0 && end>0) {
            end += direction;
        } else {
            direction = -direction;
        }
    }
}
