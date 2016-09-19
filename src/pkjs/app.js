var GeocodeMapquest = require('pebble-geocode-mapquest');
var geocodeMapquest = new GeocodeMapquest();

Pebble.addEventListener('ready', function(e) {
  console.log('PebbleKit JS ready!');
	var msg = "OK";
	var dictionary = {"READY": msg};
	Pebble.sendAppMessage(dictionary, function(e) {console.log("Ready sent to Pebble successfully!");}, function(e) {console.log('Error sending ready info to Pebble.');});
});

Pebble.addEventListener('appmessage', function(e) {
    geocodeMapquest.appMessageHandler(e);
 });