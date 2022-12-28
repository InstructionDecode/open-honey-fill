#include <Arduino.h>

#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>    // Hardware-specific library
#include <TFT_eWidget.h> // Widget and layout classes
#include <button.h>

enum State
{
  START,
  MAINPAGE,
  SETTINGS,
  CALIBRATION,
  TEST
};

enum State state = START;
enum State lastState = START;

TFT_eSPI tft = TFT_eSPI();

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

ButtonWidget btnL = ButtonWidget(&tft);

#define BUTTON_W 260
#define BUTTON_H 100

ButtonWidget *btn[] = {&btnL};
;
uint8_t buttonCount = sizeof(btn) / sizeof(btn[0]);

void btnL_pressAction(void)
{
  Serial.println("btnL pressed");
  state=MAINPAGE;
  // btnL.drawSmoothButton(true);
}

void btnL_releaseAction(void)
{
  // Serial.println("btnL released");
  // btnL.drawSmoothButton(false);
}

void initButtons()
{
  uint16_t x = (tft.width() - BUTTON_W) / 2;
  uint16_t y = tft.height() / 2 - BUTTON_H - 10;
  btnL.initButtonUL(x, y, BUTTON_W, BUTTON_H, TFT_WHITE, TFT_GREY, TFT_YELLOW, "Start", 1);
  btnL.setPressAction(btnL_pressAction);
  btnL.setReleaseAction(btnL_releaseAction);

  btnL.drawSmoothButton(false, 4, TFT_BLACK); // 3 is outline width, TFT_BLACK is the surrounding background colour for anti-aliasing

  y = tft.height() / 2 + 10;
}

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!LittleFS.begin())
  {
    Serial.println("Formating file system");
    LittleFS.format();
    LittleFS.begin();
  }

  // check if calibration file exists and size is correct
  if (LittleFS.exists(CALIBRATION_FILE))
  {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      LittleFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = LittleFS.open(CALIBRATION_FILE, "r");
      if (f)
      {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL)
  {
    // calibration data valid
    tft.setTouch(calData);
  }
  else
  {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL)
    {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = LittleFS.open(CALIBRATION_FILE, "w");
    if (f)
    {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

/*void buttonErkennungStart()
{
  for (uint8_t b = 0; b < buttonCount; b++)
  {
    if (pressed && btn[b]->contains(t_x, t_y))
    {
      btn[b]->press(true); // tell the button it is pressed
      btn[b]->pressAction(); // perform the button's onPress function [if it exists
    }
    else
    {
      btn[b]->press(false); // tell the button it is NOT pressed
    }
  }

  // Check if any key has changed state
  for (uint8_t b = 0; b < buttonCount; b++)
  {

    if (btn[b]->justReleased())
      btn[b]->drawButton(); // draw normal

    if (btn[b]->justPressed())
    {
      btn[b]->drawButton(true); // draw invert
    }
  }
}*/
void goTOMainpage()
{
  if(lastState!=MAINPAGE)
  {
    tft.fillScreen(TFT_YELLOW);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Main Page");
  lastState=MAINPAGE;
  }
  
}

void setup()
{
  
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(TFT_YELLOW);
  // tft.setFreeFont(FF18);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate();
  initButtons();
}

void loop()
{

  // Read the touch screen coordinates
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = tft.getTouch(&t_x, &t_y);
  
  switch (state)
  {
  case START:
    for (uint8_t b = 0; b < buttonCount; b++)
  {
    if (pressed && btn[b]->contains(t_x, t_y))
    {
      btn[b]->press(true); // tell the button it is pressed
      btn[b]->pressAction(); // perform the button's onPress function [if it exists
    }
    else
    {
      btn[b]->press(false); // tell the button it is NOT pressed
    }
  }

  // Check if any key has changed state
  for (uint8_t b = 0; b < buttonCount; b++)
  {

    if (btn[b]->justReleased())
      btn[b]->drawButton(); // draw normal

    if (btn[b]->justPressed())
    {
      btn[b]->drawButton(true); // draw invert
    }
  }
    break;
  case MAINPAGE:
    goTOMainpage();
    break;
  default:
    break;
  }
  // / Check if any key coordinate boxes contain the touch coordinates
  /*if (state==START){
  for (uint8_t b = 0; b < buttonCount; b++)
  {
    if (pressed && btn[b]->contains(t_x, t_y))
    {
      btn[b]->press(true); // tell the button it is pressed
      btn[b]->pressAction(); // perform the button's onPress function [if it exists
    }
    else
    {
      btn[b]->press(false); // tell the button it is NOT pressed
    }
  }

  // Check if any key has changed state
  for (uint8_t b = 0; b < buttonCount; b++)
  {

    if (btn[b]->justReleased())
      btn[b]->drawButton(); // draw normal

    if (btn[b]->justPressed())
    {
      btn[b]->drawButton(true); // draw invert
    }
  }
  }*/ //end if state==START
} // end loop