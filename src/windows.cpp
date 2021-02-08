/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/phil/dev/windows/src/windows.ino"
/**
 * @file windows.ino
 * @author PeerGum (phil@peergum.com)
 * @brief
 * @version 0.1
 * @date 2021-02-05
 *
 * @copyright (c) 2021, PeerGum
 *
 */

#include "Particle.h"

void setPins(void);
void signalCB(int &signal, int &type, int &state);
void batteryCB(int &level, int &type, int &state);
void setup();
void loop();
#line 14 "/Users/phil/dev/windows/src/windows.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

#include "Adafruit_mfGFX.h"
#include "Adafruit_SSD1351_Photon.h"
#include "SdFat.h"

#include "Display.h"
#include "DisplayDriver.h"

#include "Screen.h"

#include "screendefs.h"
#include "pins.h"

const uint8_t SOFT_MISO_PIN = SD_DO;
const uint8_t SOFT_MOSI_PIN = OLED_SD_DI;
const uint8_t SOFT_SCK_PIN = OLED_SD_SCLK;
const uint8_t SD_CHIP_SELECT_PIN = SD_CS;

Display<Adafruit_SSD1351> display(OLED_CS, OLED_DC, OLED_SD_DI, OLED_SD_SCLK,
                                  OLED_RST);
Screen screen(TOPBAR_HEIGHT, BOTTOMBAR_HEIGHT, BG_COLOR, BORDER_COLOR);

// SdFatLibSpi SD;
// SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> SD;
// SdFat SD;

void setPins(void) {
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_SD_DI, OUTPUT);
  pinMode(OLED_SD_SCLK, OUTPUT);
  pinMode(OLED_RST, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  digitalWrite(OLED_CS, HIGH);

  pinMode(FET_3V3_SW, OUTPUT);
  digitalWrite(FET_3V3_SW, HIGH);

  delay(5);
}

void signalCB(int &signal, int &type, int &state) {
  signal = (millis() / 1000) % 5;
  type = 0;
  state = (int)CONNECTED;
}

void batteryCB(int &level, int &type, int &state) {
  level = (millis() / 1000) % 5;
  state = rand() % 3;
}

Alert alert;

void setup() {
  setPins();
  // SD.begin(SD_CS);
  display.begin();
  screen.window.topBar.commIndicator.setCallback(signalCB);
  screen.window.topBar.batteryIndicator.setCallback(batteryCB);
  screen.setStatus("Booting");
  screen.showTopBar(false);
  screen.showBottomBar(true);
  screen.window.initFields(40, 86, ALIGN_LEFT, ALIGN_RIGHT, TURQUOISE)
      .addText("Time", "value", GREEN)
      .addFloat("Float", (float)(rand() % 100000) / 1000, 4, YELLOW)
      .addInt("Int", (int)(rand() % 100000), RED);
  // .addText("Time", "value", GREEN)
  //     .addFloat("Float", (float)(rand() % 100000) / 1000, 4, YELLOW)
  //     .addInt("Int", (int)(rand() % 100000), RED);
  screen.show();
  screen.alert(alert.set("OKAY!", WHITE, true).add("blah...", TURQUOISE));
}

unsigned long timer;

void loop() {
  if (millis()-timer >= 1000UL) {
    timer = millis();
    struct tm *tm;
    time_t tTime = Time.now();
    char time[20];
    strftime(time, 20, "%H:%M", gmtime(&tTime));
    screen.window.updateText(0, time);
    screen.window.updateFloat(1, (float)rand() / 1000);
    screen.window.updateInt(2, (int)rand());
  }
    screen.refresh();
}