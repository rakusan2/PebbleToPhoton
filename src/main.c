#include <pebble.h>
#include <go.h>

Window *my_window;
TextLayer *none_layer;

void handle_init(void) {
  show_go();
}

void handle_deinit(void) {
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
