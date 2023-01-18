#include <Arduino.h>

#include "FS.h"
#include <SPI.h>
#include "setupguide.h"
#include "displaysetup.h"





void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
  	
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    init_display();
    screen0_firststartup();
}

void loop()
{
  //Serial.println("tick_thread0");
    lv_task_handler(); /* let the GUI do its work */

    delay(2);   /*Sleep for 5 millisecond*/
    lv_tick_inc(2); 
    //Serial.println("tick_thread");
}

