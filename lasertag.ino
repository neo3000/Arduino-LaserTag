#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include "pins.h"
#include "config.h"

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

Adafruit_ILI9340 tft = Adafruit_ILI9340(tft_cs, tft_dc, tft_rst);

void setup() {
  Serial.begin(9600);
  pinMode(tft_bl, OUTPUT);
  pinMode(tft_cs, OUTPUT);
  pinMode(btn_fire, INPUT_PULLUP);
  value = map(analogRead(health), 0, 1023, 0, 220);
  analogWrite(tft_bl, 255);
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  GUI();
  PlayerID();
}

void loop(void) {
  HealthBar();
  Magazine();
  ShootBar();
  HealthPacks();
}

void ShootBar() {
  value = map(analogRead(health), 0, 1015, 0, 220);
  if (digitalRead(btn_fire) == LOW) {
    shoots = shoots - 1;
  }
  tft.setCursor(35, 100);
  tft.setTextColor(ILI9340_WHITE, ILI9340_BLACK);
  tft.setTextSize(4);
  if (shoots < 10) {
    tft.print("00");
    tft.print(shoots);
    tft.print("/500");
  }
  else if ((shoots > 10) && (shoots < 100)) {
    tft.print("0");
    tft.print(shoots);
    tft.print("/500");
  }
  else if ((shoots > 100)) {
    tft.print(shoots);
    tft.print("/500");
  }
}

void HealthBar() {
  tft.setCursor(0, 0);
  int h = map(value, 0, 220, 0, 100);
  tft.fillRect(value + 10, 10, 220 - value, 30, ILI9340_BLACK);
  if (h > 35) {
    tft.fillRect(10, 10, value, 30, ILI9340_GREEN);
  } else {
    tft.fillRect(10, 10, value, 30, ILI9340_RED);
  }
}

void Magazine() {
  tft.setCursor(40, 285);
  tft.setTextSize(3);
  if (stacks < 10) {
    tft.print("0");
    tft.print(stacks);
  }
  else {
    tft.print(stacks);
  }
}

void PlayerID() {
  tft.setCursor(10, 215);
  tft.setTextColor(ILI9340_YELLOW, ILI9340_BLACK);
  tft.setTextSize(2);
  tft.print("ID: ");tft.print(player_id);
}

void HealthPacks() {
  tft.setCursor(180, 285);
  tft.setTextSize(3);
  tft.print(healthPacks);
}

void GUI() {
  tft.drawRect(9, 9, 222, 32, ILI9340_WHITE);
  tft.drawLine(0, 245, 240, 245, ILI9340_WHITE);
  tft.drawLine(120, 245, 120, 320, ILI9340_WHITE);
  tft.setCursor(20, 253);
  tft.setTextColor(ILI9340_WHITE, ILI9340_BLACK);
  tft.setTextSize(2);
  tft.print("Stacks");
  tft.setCursor(145, 253);
  tft.setTextColor(ILI9340_WHITE, ILI9340_BLACK);
  tft.setTextSize(2);
  tft.print("H-Packs");
}
