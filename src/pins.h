#ifndef __PINS_H
#define __PINS_H

#include "Particle.h"

#define POWERGAUGE A0
#define FET_3V3_SW D3
#define WDG_WAKE WKP
#define WDG_DONE DAC

// --- Sensor comms
#ifdef __TEST
#define SENSOR_SERIAL Serial5
#else
#define SENSOR_SERIAL Serial1
#endif
#define DEC_A0 B5
#define DEC_A1 B4
#define DEC_A2 B3
#define DEnb B2
#define REnb B1
#define DE_v2 D7
#define RE_v2 D6

// --- interface
#define ENTER B0
#define DOWN D7
#define UP D6

// --- display & SD card
#define OLED_CS D5
#define OLED_RST D1
#define OLED_DC D0
#define OLED_SD_DI A5
#define SD_DO A4
#define OLED_SD_SCLK A3
#define SD_CS A2

// --- Rockblock
#define RB_SW D4
#define RB_SW_v2 C5
#define RB_TX C3
#define RB_RX C2

// --- GPS
#ifdef __TEST

#define GPS_SERIAL Serial1
#define GPS_PWR_EN D6
#define GPS_RST D2
#define GPS_RX TX
#define GPS_TX RX
#define GPS_SCL C5
#define GPS_SDA C4

#else

#define GPS_SERIAL Serial5
#define GPS_PWR_EN A1
#define GPS_RST D2
#define GPS_RX C1
#define GPS_TX C0
#define GPS_SCL C5
#define GPS_SDA C4

#endif

#endif
