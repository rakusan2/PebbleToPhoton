#include <pebble.h>
#include "go.h"

bool stoppedL=false, stoppedR=false,Btransmitting=false, accel_subscribed=false;;
static int16_t x=0, y=0;
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_content_regular_12;
static GFont s_res_content_regular_24;
static GBitmap *s_res_left_led;
static GBitmap *s_res_send_button;
static GBitmap *s_res_right_led;
static TextLayer *s_time_layer;
static TextLayer *s_xy_values_layer;
static ActionBarLayer *s_actionbarlayer_1;
static BitmapLayer *s_left_stop;
static BitmapLayer *s_right_stop;
static BitmapLayer *s_transmitting;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
  #endif
  
  s_res_content_regular_12 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_content_regular_12));
  s_res_content_regular_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_content_regular_24));
  s_res_left_led = gbitmap_create_with_resource(RESOURCE_ID_Left_LED);
  s_res_send_button = gbitmap_create_with_resource(RESOURCE_ID_Send_Button);
  s_res_right_led = gbitmap_create_with_resource(RESOURCE_ID_Right_LED);
  // s_time_layer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 18));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, s_res_content_regular_12);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time_layer);
  
  // s_xy_values_layer
  s_xy_values_layer = text_layer_create(GRect(13, 66, 99, 36));
  text_layer_set_background_color(s_xy_values_layer, GColorClear);
  text_layer_set_text_color(s_xy_values_layer, GColorWhite);
  text_layer_set_text(s_xy_values_layer, "000 000");
  text_layer_set_text_alignment(s_xy_values_layer, GTextAlignmentCenter);
  text_layer_set_font(s_xy_values_layer, s_res_content_regular_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_xy_values_layer);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_left_led);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_send_button);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_right_led);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_left_stop
  s_left_stop = bitmap_layer_create(GRect(40, 53, 15, 15));
  bitmap_layer_set_bitmap(s_left_stop, s_res_left_led);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_left_stop);
  
  // s_right_stop
  s_right_stop = bitmap_layer_create(GRect(70, 53, 15, 15));
  bitmap_layer_set_bitmap(s_right_stop, s_res_right_led);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_right_stop);
  
  // s_transmitting
  s_transmitting = bitmap_layer_create(GRect(55, 105, 15, 15));
  bitmap_layer_set_bitmap(s_transmitting, s_res_send_button);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_transmitting);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_xy_values_layer);
  action_bar_layer_destroy(s_actionbarlayer_1);
  bitmap_layer_destroy(s_left_stop);
  bitmap_layer_destroy(s_right_stop);
  bitmap_layer_destroy(s_transmitting);
  fonts_unload_custom_font(s_res_content_regular_12);
  fonts_unload_custom_font(s_res_content_regular_24);
  gbitmap_destroy(s_res_left_led);
  gbitmap_destroy(s_res_send_button);
  gbitmap_destroy(s_res_right_led);
}
// END AUTO-GENERATED UI CODE


static void inbox_recieved_callback(DictionaryIterator *iterator,void *context){
  APP_LOG(APP_LOG_LEVEL_INFO, "Inbox recieved success");
}
static void inbox_dropped_callback(AppMessageResult reason, void *context){
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped");
}
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason,void *context){
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox sent failed");
}
static void outbox_sent_callback(DictionaryIterator *iterator,void *context){
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success");
}

static void transmit_to_phone(){
  DictionaryIterator *iterator;
  app_message_outbox_begin(&iterator);
  dict_write_int16(iterator, 0, x);
  dict_write_int16(iterator, 1, y);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "X=%d Y=%d", x,y);
  app_message_outbox_send();
}
static void Accel_Data_Handler(AccelData *data, uint32_t num_samples){
  if(!stoppedL){
    int temp_x=0;
    temp_x=(data[0].x+500)/4;
    if(temp_x<0)temp_x=0;
    else if(temp_x>255)temp_x=255;
    x=temp_x;
  }
  if(!stoppedR){
    int temp_y=0;
    temp_y=(data[0].y+750)/4;
    if(temp_y<0)temp_y=0;
    else if(temp_y>255)temp_y=255;
    y=temp_y;
  }
  static char buffer[]="000 000";
  snprintf(buffer,sizeof("000 000"),"%03d %-3d",x,y);
  text_layer_set_text(s_xy_values_layer, buffer);
    if(Btransmitting)transmit_to_phone();
}
static void check_complete_stop(){
  if(!stoppedR && !stoppedL){
    accel_data_service_unsubscribe();
    accel_subscribed=false;
  }
  else if(!accel_subscribed){
    accel_subscribed=true;
    accel_data_service_subscribe(1, Accel_Data_Handler);
  }
}
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_set_hidden(bitmap_layer_get_layer(s_left_stop),stoppedL);
  stoppedL=!stoppedL;
  check_complete_stop();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  transmit_to_phone();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_set_hidden(bitmap_layer_get_layer(s_right_stop),stoppedR);
  stoppedR=!stoppedR;
  check_complete_stop();
}static void long_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_set_hidden(bitmap_layer_get_layer(s_transmitting),Btransmitting);
  Btransmitting=!Btransmitting;
  transmit_to_phone();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  static char buffer[16];
  clock_copy_time_string(buffer, sizeof(buffer));
 
  text_layer_set_text(s_time_layer,buffer);
}
static void handle_window_unload(Window* window) {
  destroy_ui();
}
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, long_down_click_handler, NULL);
}

void show_go(void) {
  initialise_ui();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  accel_data_service_subscribe(1, Accel_Data_Handler);
  accel_subscribed=true;
  app_message_register_inbox_received(inbox_recieved_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, click_config_provider);
  window_stack_push(s_window, true);
  layer_set_hidden(bitmap_layer_get_layer(s_left_stop),true);
  layer_set_hidden(bitmap_layer_get_layer(s_right_stop),true);
  layer_set_hidden(bitmap_layer_get_layer(s_transmitting),true);
  
}

void hide_go(void) {
  window_stack_remove(s_window, true);
}
