var GeocodeMapquest = require('pebble-geocode-mapquest');
var geocodeMapquest = new GeocodeMapquest();

Pebble.addEventListener('appmessage', function(e) {
    geocodeMapquest.appMessageHandler(e);
 });