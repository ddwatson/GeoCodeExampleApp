#include <pebble.h>
#include <pebble-geocode-mapquest/pebble-geocode-mapquest.h>
#include <pebble-events/pebble-events.h>

static void geocode_fetch_callback(GeocodeMapquestCoordinates *coordinates, GeocodeMapquestStatus status) {
    APP_LOG(APP_LOG_LEVEL_INFO, "latitude:%ld", coordinates->latitude);
    APP_LOG(APP_LOG_LEVEL_INFO, "longitude:%ld", coordinates->longitude);
}

static void init(void) {
  geocode_mapquest_init();
  geocode_mapquest_set_api_key("tJsAZSQClbHE2pX451PUXw8XyLytiw7K");
  geocode_mapquest_fetch("Seattle, WA", geocode_fetch_callback);
}

static void deinit(void) {
  geocode_mapquest_deinit();
}

int main() {
  init();
  app_event_loop();
  deinit();
}