#include <pebble.h>
#include <go.h>

Window *my_window;
TextLayer *none_layer;

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

void handle_init(void) {
  app_message_register_inbox_received(inbox_recieved_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  show_go();
}

void handle_deinit(void) {
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
