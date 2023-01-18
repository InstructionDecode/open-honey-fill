 #pragma once

 #include <lvgl.h>
 #include "displaysetup.h"

static void screen0_button_event_start(lv_event_t * e);
static void screen1_button_event_back(lv_event_t * e);
static void screen1_button_event_next(lv_event_t * e);
 static void event_handler_language(lv_event_t * e);
 static void screen2_button_event_back(lv_event_t * e);
static void screen2_button_event_next(lv_event_t * e);
 static void deletobj(lv_event_t * e);

void screen0_firststartup();
void screen1_language();
void screen2_calibration();

static void lv_spinbox_increment_event_cb(lv_event_t * e);
static void lv_spinbox_decrement_event_cb(lv_event_t * e);