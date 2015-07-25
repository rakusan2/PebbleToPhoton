#include <pebble.h>
#include "go.h"

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

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
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
  s_xy_values_layer = text_layer_create(GRect(0, 66, 124, 36));
  text_layer_set_background_color(s_xy_values_layer, GColorClear);
  text_layer_set_text_color(s_xy_values_layer, GColorWhite);
  text_layer_set_text(s_xy_values_layer, "000|000");
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
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_xy_values_layer);
  action_bar_layer_destroy(s_actionbarlayer_1);
  fonts_unload_custom_font(s_res_content_regular_12);
  fonts_unload_custom_font(s_res_content_regular_24);
  gbitmap_destroy(s_res_left_led);
  gbitmap_destroy(s_res_send_button);
  gbitmap_destroy(s_res_right_led);
}
// END AUTO-GENERATED UI CODE
static void Accel_Data_Handler(AccelData *data, uint32_t num_samples){
  int x=data->x;
  int y=data->y;
  static char buffer[]="000|000";
  snprintf(buffer,sizeof("000|000"),"%d|%d",x,y);
  text_layer_set_text(s_xy_values_layer, buffer);
    
}
static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  time_t temp = time(NULL);
  struct tm *tick_time2 = localtime(&temp);
  static char buffer[] = "00:00";
  if(clock_is_24h_style() == true){
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time2);
  }
  else{
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time2);
  }
  text_layer_set_text(s_time_layer,buffer);
}
static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_go(void) {
  initialise_ui();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  accel_data_service_subscribe(32, Accel_Data_Handler);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_go(void) {
  window_stack_remove(s_window, true);
}
