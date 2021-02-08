/**
 * @file colors.h
 * @author Phil Hilger (phil.hilger@waterlooti.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright (c) 2021, WaterlooTI
 * 
 */

#ifndef __COLORS_H
#define __COLORS_H

#include "Particle.h"

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0 // 00000.111 111.00000
#define DARKGREEN 0x01E0 // 00000.000 111.00000
#define CYAN 0x07FF
#define MAGENTA 0xF81F  // (PURPLE)
#define YELLOW 0xFFE0   // 11111 111.111 00000
#define WHITE 0xFFFF
#define ORANGE 0xFE00  // 11111 110.000 00000
#define DARKBLUE 0x0007
#define GREY 0x1042        // 00010 000.010 00010
#define DARKGREY 0x0821    // 00001 000.001 00001
#define MEDIUMGREY 0x2084  // 00100 000.100 00100
#define LIGHTGREY 0x8410   // 10000 100.000 10000
#define TURQUOISE 0x061F   // 00000 110.000 11111
#define BACKGROUND 0x0881

typedef uint16_t color_t;

#endif