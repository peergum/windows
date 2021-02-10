/**
 * @file Activity.h
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-09
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#ifndef __ACTIVITY_H
#define __ACTIVITY_H

#include "Frame.h"
#include "screendefs.h"

class Activity : public Frame {
public:
    Activity(int x, int y, int w, int h, color_t bgColor, color_t color);
    void clear(void);
    void draw(void);
    void refresh(bool force = false);
private:
    unsigned long _refreshTimer;
    color_t color;
    int start = 0;
    int end = 0;
    int direction = 10;
};

#endif