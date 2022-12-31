#include <Arduino.h>

#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>    // Hardware-specific library
#include <TFT_eWidget.h> // Widget and layout classes
#include <button.h>


#include <lvgl.h>
#include "demos/lv_demos.h"

#define CALIBRATION_FILE "/TouchCalData2"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

//lv_obj_t * scr1 = lv_obj_create(NULL);
//lv_obj_t * scr2 = lv_obj_create(NULL);

lv_obj_t * obj1;
void secondscreen();
void firstscreen();

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    //Serial.print( " Test " );
        

    bool touched = tft.getTouch( &touchX, &touchY, 600); 

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
    }
}



/*void lv_example_get_started_2(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());    
    //lv_obj_set_pos(btn, 10, 10);                           
    /*lv_obj_align( btn, LV_ALIGN_CENTER, 0, 0 );
    lv_obj_set_size(btn, 120, 50);                         
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);          

    lv_obj_t * label = lv_label_create(btn);          
    lv_label_set_text(label, "Button");                    
    lv_obj_center(label);
}*/

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        secondscreen();
    }
}

static void btn_event_cb2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        firstscreen();
    }
}

void firstscreen(){
  
  //obj1 = lv_obj_create(lv_scr_act());
  //lv_obj_set_size(obj1, 320, 480);
  

    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    //lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_align( btn, LV_ALIGN_CENTER, 0, 165 );
    lv_obj_set_size(btn, 220, 80);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Start");                     /*Set the labels text*/
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);
    lv_obj_center(label);

    lv_obj_t * label1 = lv_label_create(lv_scr_act());          /*Add a label to the button*/
    lv_label_set_text(label1, "open_honey_fill");
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_26, 0);
    lv_obj_align( label1, LV_ALIGN_CENTER, 0, -185 );

    lv_obj_t * label2 = lv_label_create(lv_scr_act());          /*Add a label to the button*/
    lv_label_set_text(label2, "Version 0.0.1");
    lv_obj_align( label2, LV_ALIGN_CENTER, 0, -155 );

    lv_obj_t * label3 = lv_label_create(lv_scr_act());          /*Add a label to the button*/
    lv_label_set_long_mode(label3, LV_LABEL_LONG_WRAP);
    lv_label_set_text(label3, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr," 
    "sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat,"
    "sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. "
    "Stet clita kasd gubergren, no sea takimata sanctus est");
    lv_obj_set_width(label3, 280); 
    lv_obj_set_style_text_font(label3, &lv_font_montserrat_16, 0);
    lv_obj_align( label3, LV_ALIGN_CENTER, 0, -15);
}

void secondscreen(){
  lv_obj_t * obj2;
  obj2 = lv_obj_create(lv_scr_act());
  lv_obj_set_size(obj2, 320, 480);

  lv_obj_t * btn = lv_btn_create(obj2);     /*Add a button the current screen*/
    //lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_align( btn, LV_ALIGN_CENTER, 0, 0 );
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb2, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "2");                     /*Set the labels text*/
    lv_obj_center(label);
}





void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
  	
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 2 ); /* Landscape orientation, flipped */

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    /*uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
    tft.setTouch( calData );*/
    touch_calibrate();

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_t * my_indev = lv_indev_drv_register( &indev_drv );

    /* Create simple label */
   /* lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, LVGL_Arduino.c_str() );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );*/

    //lv_example_get_started_2();
    firstscreen();
    Serial.println( "Setup done" );
}

void loop()
{
  //Serial.println("tick_thread0");
    lv_task_handler(); /* let the GUI do its work */

     delay(5);   /*Sleep for 5 millisecond*/
    lv_tick_inc(5); 
    //Serial.println("tick_thread");
}

