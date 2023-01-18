#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>    // Hardware-specific library
#include <TFT_eWidget.h> // Widget and layout classes
#include <lvgl.h>

#define CALIBRATION_FILE "/TouchCalData2"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 50 ];
static lv_color_t buf_2[ screenWidth * 50 ];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_indev_t * my_indev;



static TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif


void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );

void touch_calibrate();

void init_tft();

void init_lvgl();

void init_display();