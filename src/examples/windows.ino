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


SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

#define __TEST
// #define USE_BITMAP

#include "Adafruit_mfGFX.h"
#include "Adafruit_SSD1351_Photon.h"

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

#ifdef USE_BITMAP
#include "SdFat.h"
// SdFatLibSpi SD;
// SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> SD;
SdFat SD;
#endif

void setPins(void) {
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_SD_DI, OUTPUT);
  pinMode(OLED_SD_SCLK, OUTPUT);
  pinMode(OLED_RST, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(OLED_CS, HIGH);
  digitalWrite(SD_CS, HIGH);

#ifdef __TEST
  // load switch to activate display/card
  #define LOAD_SWITCH D3
  pinMode(LOAD_SWITCH, OUTPUT);
  digitalWrite(LOAD_SWITCH, HIGH);
#endif

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
 
  display.begin();
#ifdef USE_BITMAP
  if (!SD.begin(SD_CS,SPISettings(9000000,MSBFIRST,SPI_MODE3))) {
    Serial.println("Fail");
  }
  Bitmap *bitmap = new Bitmap("test.bmp"); //!< uncompressed BMP file using 16bit colors
  bitmap->draw(0, 0);
  delay(2000);
#endif
  screen.window.topBar.commIndicator.setCallback(signalCB);
  screen.window.topBar.batteryIndicator.setCallback(batteryCB);
  screen.setStatus("Booting");
  screen.showTopBar(true);
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
    time_t tTime = Time.now();
    struct tm *tm = gmtime(&tTime);
    char time[20];
    strftime(time, 20, "%H:%M:%S", tm);
    screen.window.updateText(0, time);
    screen.window.updateFloat(1, (float)rand() / 1000);
    screen.window.updateInt(2, (int)rand());
    screen.alert(alert.set(time,BLUE,true));
  }
  screen.refresh();
}