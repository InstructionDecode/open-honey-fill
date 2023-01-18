 #include "setupguide.h"


 void screen0_firststartup(){
    lv_obj_t * parent = lv_obj_create(lv_scr_act());
    lv_obj_set_size(parent, 320, 480);
    lv_obj_add_event_cb(parent, deletobj ,LV_EVENT_CHILD_DELETED , NULL);
    lv_obj_t * btn = lv_btn_create(parent);     /*Add a button the current screen*/
    //lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_align( btn, LV_ALIGN_CENTER, 0, 165 );
    lv_obj_set_size(btn, 220, 80);                          /*Set its size*/
    lv_obj_add_event_cb(btn, screen0_button_event_start, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Start");                     /*Set the labels text*/
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);
    lv_obj_center(label);

    lv_obj_t * label1 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_text(label1, "open_honey_fill");
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_26, 0);
    lv_obj_align( label1, LV_ALIGN_TOP_MID, 0, 30 );

    lv_obj_t * label2 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_text(label2, "Version 0.0.1");
    lv_obj_align( label2, LV_ALIGN_CENTER, 0, -155 );

    lv_obj_t * label3 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_long_mode(label3, LV_LABEL_LONG_WRAP);
    lv_label_set_text(label3, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr," 
    "sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat,"
    "sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. "
    "Stet clita kasd gubergren, no sea takimata sanctus est");
    lv_obj_set_width(label3, 280); 
    lv_obj_set_style_text_font(label3, &lv_font_montserrat_16, 0);
    lv_obj_align( label3, LV_ALIGN_CENTER, 0, -15);
 }

 void deletobj(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t * btn = lv_event_get_target(e);
        if(code == LV_EVENT_CHILD_DELETED) {
        lv_obj_del_async(btn);
        }
        
    }

 void screen0_button_event_start(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t * btn = lv_event_get_target(e);
        if(code == LV_EVENT_CLICKED) {
        //lv_obj_del(btn);
        screen1_language();
        lv_obj_del_async(btn);
        }
    }


 void screen1_language(){
     lv_obj_t * parent = lv_obj_create(lv_scr_act());
    lv_obj_set_size(parent, 320, 480);
 lv_obj_t * roller1 = lv_roller_create(parent);
lv_obj_set_width(roller1, 200);
    lv_roller_set_options(roller1,
                          "English\n"
                          "German\n"
                          "French\n"
                          "Spanish\n",
                          LV_ROLLER_MODE_NORMAL);

    lv_roller_set_visible_row_count(roller1, 4);
    lv_obj_center(roller1);
    lv_obj_add_event_cb(roller1, event_handler_language, LV_EVENT_ALL, NULL);

    lv_obj_t * btn = lv_btn_create(parent);     /*Add a button the current screen*/
    lv_obj_align( btn, LV_ALIGN_BOTTOM_RIGHT, -5, -20 );                          /*Set its position*/
    
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, screen1_button_event_next, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Next");                     /*Set the labels text*/
    lv_obj_center(label);


    lv_obj_t * btn1 = lv_btn_create(parent);     /*Add a button the current screen*/
    lv_obj_align( btn1, LV_ALIGN_BOTTOM_LEFT, 5, -20 );                          /*Set its position*/
    
    lv_obj_set_size(btn1, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn1, screen1_button_event_back, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label2 = lv_label_create(btn1);          /*Add a label to the button*/
    lv_label_set_text(label2, "Back");                     /*Set the labels text*/
    lv_obj_center(label2);

    lv_obj_t * label1 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_text(label1, "Select Language");
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_22, 0);
    //lv_obj_align( label1, LV_ALIGN_CENTER, 0, -120);
    lv_obj_align( label1, LV_ALIGN_TOP_MID, 0, 50);


 }

 void screen1_button_event_back(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        screen0_firststartup();
        lv_obj_del_async(btn);
    }
 }

 void screen1_button_event_next(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        screen2_calibration();
        lv_obj_del_async(btn);
    }
 }

 static void event_handler_language(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected month: %s\n", buf);
    }
}


void screen2_calibration(){
    lv_obj_t * parent = lv_obj_create(lv_scr_act());
    lv_obj_set_size(parent, 320, 480);

    lv_obj_t * label1 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_text(label1, "Calibration");
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_22, 0);
    //lv_obj_align( label1, LV_ALIGN_CENTER, 0, -120);
    lv_obj_align( label1, LV_ALIGN_TOP_MID, 0, 50);



    lv_obj_t * btn = lv_btn_create(parent);     /*Add a button the current screen*/
    lv_obj_align( btn, LV_ALIGN_BOTTOM_RIGHT, -5, -20 );                          /*Set its position*/
    
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, screen2_button_event_next, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Next");                     /*Set the labels text*/
    lv_obj_center(label);


    lv_obj_t * btn1 = lv_btn_create(parent);     /*Add a button the current screen*/
    lv_obj_align( btn1, LV_ALIGN_BOTTOM_LEFT, 5, -20 );                          /*Set its position*/
    
    lv_obj_set_size(btn1, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn1, screen2_button_event_back, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label2 = lv_label_create(btn1);          /*Add a label to the button*/
    lv_label_set_text(label2, "Back");                     /*Set the labels text*/
    lv_obj_center(label2);



    lv_obj_t * spinbox = lv_spinbox_create(parent);
    lv_obj_set_style_text_font(spinbox, &lv_font_montserrat_26, 0);
    lv_obj_set_style_text_align(spinbox, LV_TEXT_ALIGN_CENTER, 0);
    //lv_obj_align(spinbox, LV_ALIGN_CENTER, 0, 20);
    lv_spinbox_set_range(spinbox, 100, 2000);
    lv_spinbox_set_digit_format(spinbox, 4, 4);
    lv_spinbox_set_step(spinbox, 100);
    lv_spinbox_step_prev(spinbox);
    lv_obj_set_width(spinbox, 160);
    //lv_obj_set_height(spinbox, 50);
    lv_obj_center(spinbox);

    lv_coord_t h = lv_obj_get_height(spinbox);

    lv_obj_t * btn3 = lv_btn_create(parent);
    lv_obj_set_size(btn3, 1.5*h, 1.5*h);
    lv_obj_align_to(btn3, spinbox, LV_ALIGN_OUT_BOTTOM_RIGHT, 15, 5);
    lv_obj_set_style_bg_img_src(btn3, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn3, lv_spinbox_increment_event_cb, LV_EVENT_ALL,spinbox);

    btn3 = lv_btn_create(parent);
    lv_obj_set_size(btn3, 1.5*h, 1.5*h);
    lv_obj_align_to(btn3, spinbox, LV_ALIGN_OUT_BOTTOM_LEFT, -15, 5);
    lv_obj_set_style_bg_img_src(btn3, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn3, lv_spinbox_decrement_event_cb, LV_EVENT_ALL, spinbox);


    lv_obj_t * label4 = lv_label_create(parent);          /*Add a label to the button*/
    lv_label_set_text(label4, "g");
    lv_obj_set_style_text_font(label4, &lv_font_montserrat_26, 0);
    lv_obj_align( label4, LV_ALIGN_CENTER, 40, 0);
}

static void lv_spinbox_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = (lv_obj_t*) lv_event_get_user_data(e);
    
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        
        lv_spinbox_increment(btn);
    }
}

static void lv_spinbox_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t * btn = (lv_obj_t*) lv_event_get_user_data(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        
        lv_spinbox_decrement(btn);
    }
}

static void screen2_button_event_back(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        screen1_language();
        lv_obj_del_async(btn);
    }

}
static void screen2_button_event_next(lv_event_t * e){

}