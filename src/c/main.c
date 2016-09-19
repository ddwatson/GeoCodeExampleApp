#include <pebble.h>
#include <pebble-geocode-mapquest/pebble-geocode-mapquest.h>
#include <pebble-events/pebble-events.h>
static Window *s_main_window;
static TextLayer *s_text_layer;
static char APIKEY[]="tJsAZSQClbHE2pX451PUXw8XyLytiw7K";
static char Location[]="Seattle, WA";

static void geocode_fetch_callback(GeocodeMapquestCoordinates *coordinates, GeocodeMapquestStatus status) {
/*  switch(status) {
    case GeocodeMapquestStatusAvailable: {*/
      APP_LOG(APP_LOG_LEVEL_INFO, "latitude:%ld", coordinates->latitude);
      APP_LOG(APP_LOG_LEVEL_INFO, "longitude:%ld", coordinates->longitude);
      static char s_buffer[256];
      snprintf(s_buffer, sizeof(s_buffer),"Location:\n%s\nLatitude:%ld\nLongitude:%ld\nGeoCode Status:%d",Location,coordinates->latitude,coordinates->longitude,status);
      text_layer_set_text(s_text_layer, s_buffer);
/*      } 
    case GeocodeMapquestStatusBadKey:
      text_layer_set_text(s_text_layer, "GeocodeMapquestStatusBadKey");
      break;
    case GeocodeMapquestStatusFailed:
      text_layer_set_text(s_text_layer, "GeocodeMapquestStatusFailed");
      break;
    case GeocodeMapquestStatusNotYetFetched:
      text_layer_set_text(s_text_layer, "GeocodeMapquestStatusNotYetFetched");
      break;
    case GeocodeMapquestStatusBluetoothDisconnected:
      text_layer_set_text(s_text_layer, "GeocodeMapquestStatusBluetoothDisconnected");
      break;
    case GeocodeMapquestStatusPending:
      text_layer_set_text(s_text_layer, "GeocodeMapquestStatusPending");
      break;
  }*/
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context)
{
	Tuple *data = dict_find(iterator, MESSAGE_KEY_READY);
	if(data)
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Ready Received! Requesting location.");
		geocode_mapquest_fetch(Location, geocode_fetch_callback);
	}
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  s_text_layer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  text_layer_set_text(s_text_layer, "Ready.");
  text_layer_set_text_alignment(s_text_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_text_layer);
  
  //Destroy Window
  window_destroy(s_main_window);
}

static void init(void) {
    s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
  geocode_mapquest_init();
  geocode_mapquest_set_api_key(APIKEY);
  events_app_message_request_inbox_size(256);
	events_app_message_register_inbox_received(inbox_received_callback, NULL);
// I left these stubbed out as you really should have them, but I didn't want to add lines to the example code for these
//	events_app_message_register_inbox_dropped(inbox_dropped_callback, NULL);
//	events_app_message_register_outbox_failed(outbox_failed_callback, NULL);
//	events_app_message_register_outbox_sent(outbox_sent_callback, NULL);
  events_app_message_open();
}

static void deinit(void) {
  geocode_mapquest_deinit();
}

int main() {
  init();
  app_event_loop();
  deinit();
}