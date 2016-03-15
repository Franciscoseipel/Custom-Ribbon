



var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};
function locationSuccess(pos) {
  // Construct URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + 'f31b67218b2b849040024601f9df4577';

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);

      // Temperature in Kelvin requires adjustment
      var temperature = Math.round(json.main.temp - 273.15);
      console.log('Temperature is ' + temperature);

      // Conditions
      var conditions = json.weather[0].main;      
      console.log('Conditions are ' + conditions);
      // Assemble dictionary using our keys
var dictionary = {
  KEY_TEMPERATURE: temperature,
  KEY_CONDITIONS: conditions
};

// Send to Pebble
Pebble.sendAppMessage(dictionary,
  function(e) {
    console.log('Weather info sent to Pebble successfully!');
  },
  function(e) {
    console.log('Error sending weather info to Pebble!');
  }
);
    }      
  );
}

function locationError(err) {
  console.log('Error requesting location!');
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}
// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    getWeather();
  }                     
);





Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
      // Get the initial weather
    getWeather();
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'http://lolamtisch.de/pebble/config/index.html';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));

  console.log('Configuration page returned: ' + JSON.stringify(configData));

  if (configData.backgroundColor) {
    Pebble.sendAppMessage({
      backgroundColor: parseInt(configData.backgroundColor, 16),
      h1dir: parseInt(configData.h1dir, 10),
      twentyFourHourFormat: configData.twentyFourHourFormat,
      h1numberColor: parseInt(configData.h1numberColor, 16),
      h1bandColor: parseInt(configData.h1bandColor, 16),
      h1x: parseInt(configData.h1x, 10),
      h1y: parseInt(configData.h1y, 10),
      h1duration: parseInt(configData.h1duration, 10),
      h1delay: parseInt(configData.h1delay, 10),
      h1outline: configData.h1outline,
      h1line: configData.h1line,
      h1linesColor: parseInt(configData.h1linesColor, 16),
      
      
      h2dir: parseInt(configData.h2dir, 10),
      h2trans: configData.h2trans,
      h2numberColor: parseInt(configData.h2numberColor, 16),
      h2bandColor: parseInt(configData.h2bandColor, 16),
      h2x: parseInt(configData.h2x, 10),
      h2y: parseInt(configData.h2y, 10),
      h2duration: parseInt(configData.h2duration, 10),
      h2delay: parseInt(configData.h2delay, 10),
      h2outline: configData.h2outline,
      h2line: configData.h2line,
      h2linesColor: parseInt(configData.h2linesColor, 16),
      
      
      m1dir: parseInt(configData.m1dir, 10),
      m1trans: configData.m1trans,
      m1numberColor: parseInt(configData.m1numberColor, 16),
      m1bandColor: parseInt(configData.m1bandColor, 16),
      m1x: parseInt(configData.m1x, 10),
      m1y: parseInt(configData.m1y, 10),
      m1duration: parseInt(configData.m1duration, 10),
      m1delay: parseInt(configData.m1delay, 10),
      m1outline: configData.m1outline,
      m1line: configData.m1line,
      m1linesColor: parseInt(configData.m1linesColor, 16),
      
      
      m2dir: parseInt(configData.m2dir, 10),
      m2trans: configData.m2trans,
      m2numberColor: parseInt(configData.m2numberColor, 16),
      m2bandColor: parseInt(configData.m2bandColor, 16),
      m2x: parseInt(configData.m2x, 10),
      m2y: parseInt(configData.m2y, 10),
      m2duration: parseInt(configData.m2duration, 10),
      m2delay: parseInt(configData.m2delay, 10),
      m2outline: configData.m2outline,
      m2line: configData.m2line,
      m2linesColor: parseInt(configData.m2linesColor, 16),
      
      invertanimationdelay: configData.invertanimationdelay,
      changeallnumbers: configData.changeallnumbers,
      
      layer1: parseInt(configData.layer1, 10),
      layer2: parseInt(configData.layer2, 10),
      layer3: parseInt(configData.layer3, 10),
      layer4: parseInt(configData.layer4, 10),
      
      
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});