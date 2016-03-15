(function() {
  loadOptions();
  generateexport();
  importHandler();
  submitHandler();
})();

function generateexport() {
  var $generatse = $('#generatse');
  
  if (localStorage.backgroundColor) {
  var options = {
    backgroundColor: localStorage.backgroundColor,
    twentyFourHourFormat: localStorage.twentyFourHourFormat === 'true',
    h1dir: localStorage.h1dir,
    h1numberColor: localStorage.h1numberColor,
    h1bandColor: localStorage.h1bandColor,
    h1x: localStorage.h1x,
    h1y: localStorage.h1y,
    h1delay: localStorage.h1delay,
    h1duration: localStorage.h1duration,
    h1outline: localStorage.h1outline === 'true',
    h1line: localStorage.h1line === 'true',
    h1linesColor: localStorage.h1linesColor,
    
    
    h2trans: localStorage.h2trans === 'true',
    h2dir: localStorage.h2dir,
    h2numberColor: localStorage.h2numberColor,
    h2bandColor: localStorage.h2bandColor,
    h2x: localStorage.h2x,
    h2y: localStorage.h2y,
    h2delay: localStorage.h2delay,
    h2duration: localStorage.h2duration,
    h2outline: localStorage.h2outline === 'true',
    h2line: localStorage.h2line === 'true',
    h2linesColor: localStorage.h2linesColor,   
    
    
    m1trans: localStorage.m1trans === 'true',
    m1dir: localStorage.m1dir,
    m1numberColor: localStorage.m1numberColor,
    m1bandColor: localStorage.m1bandColor,
    m1x: localStorage.m1x,
    m1y: localStorage.m1y,
    m1delay: localStorage.m1delay,
    m1duration: localStorage.m1duration,
    m1outline: localStorage.m1outline === 'true',
    m1line: localStorage.m1line === 'true',
    m1linesColor: localStorage.m1linesColor,   
    
    
    m2trans: localStorage.m2trans === 'true',
    m2dir: localStorage.m2dir,
    m2numberColor: localStorage.m2numberColor,
    m2bandColor: localStorage.m2bandColor,
    m2x: localStorage.m2x,
    m2y: localStorage.m2y,
    m2delay: localStorage.m2delay,
    m2duration: localStorage.m2duration,
    m2outline: localStorage.m2outline === 'true',
    m2line: localStorage.m2line === 'true',
    m2linesColor: localStorage.m2linesColor,   
    
    invertanimationdelay: localStorage.invertanimationdelay === 'true',
    changeallnumbers: localStorage.changeallnumbers === 'true',
    
    layer1: localStorage.layer1,
    layer2: localStorage.layer2,
    layer3: localStorage.layer3,
    layer4: localStorage.layer4,
  };
  
  //$generatse[0].value = encodeURIComponent(JSON.stringify(options));
  $generatse[0].value = JSON.stringify(options);
  }
}
function importdata($data){
   // var options = JSON.parse(decodeURIComponent($data));
  var options = JSON.parse($data);   
    
  localStorage.backgroundColor = options.backgroundColor;
  localStorage.twentyFourHourFormat = options.twentyFourHourFormat;
  localStorage.h1dir = options.h1dir;
  localStorage.h1numberColor = options.h1numberColor;
  localStorage.h1bandColor = options.h1bandColor;
  localStorage.h1x = options.h1x;
  localStorage.h1y = options.h1y;
  localStorage.h1delay = options.h1delay;
  localStorage.h1duration = options.h1duration;
  localStorage.h1outline = options.h1outline;
  localStorage.h1line = options.h1line;
  localStorage.h1linesColor = options.h1linesColor;
  
  
  localStorage.h2trans = options.h2trans;
  localStorage.h2dir = options.h2dir;
  localStorage.h2numberColor = options.h2numberColor;
  localStorage.h2bandColor = options.h2bandColor;
  localStorage.h2x = options.h2x;
  localStorage.h2y = options.h2y;
  localStorage.h2delay = options.h2delay;
  localStorage.h2duration = options.h2duration;
  localStorage.h2outline = options.h2outline;
  localStorage.h2line = options.h2line;
  localStorage.h2linesColor = options.h2linesColor;
  
  
  localStorage.m1trans = options.m1trans;
  localStorage.m1dir = options.m1dir;
  localStorage.m1numberColor = options.m1numberColor;
  localStorage.m1bandColor = options.m1bandColor;
  localStorage.m1x = options.m1x;
  localStorage.m1y = options.m1y;
  localStorage.m1delay = options.m1delay;
  localStorage.m1duration = options.m1duration;
  localStorage.m1outline = options.m1outline;
  localStorage.m1line = options.m1line;
  localStorage.m1linesColor = options.m1linesColor;
  
  
  localStorage.m2trans = options.m2trans;
  localStorage.m2dir = options.m2dir;
  localStorage.m2numberColor = options.m2numberColor;
  localStorage.m2bandColor = options.m2bandColor;
  localStorage.m2x = options.m2x;
  localStorage.m2y = options.m2y;
  localStorage.m2delay = options.m2delay;
  localStorage.m2duration = options.m2duration;
  localStorage.m2outline = options.m2outline;
  localStorage.m2line = options.m2line;
  localStorage.m2linesColor = options.m2linesColor;
  
  localStorage.invertanimationdelay = options.invertanimationdelay;
  localStorage.changeallnumbers = options.changeallnumbers;
  
  
  localStorage.layer1 = options.layer1;
  localStorage.layer2 = options.layer2;
  localStorage.layer3 = options.layer3;
  localStorage.layer4 = options.layer4;
    
    
    
    //
    var return_to = getQueryParam('return_to', 'pebblejs://close#');
    //document.location = return_to + $data;
    document.location = return_to + encodeURIComponent(JSON.stringify(options));
    
}
function png($num) {
  console.log('choosed');
  if($num==='1')  importdata('{"backgroundColor":"0x000000","twentyFourHourFormat":false,"h1dir":"8","h1numberColor":"0xFFFFFF","h1bandColor":"0x00AAFF","h1x":"40","h1y":"32","h1delay":"500","h1duration":"1000","h1outline":false,"h1line":false,"h1linesColor":"0x0055FF","h2trans":false,"h2dir":"7","h2numberColor":"0xFFFFFF","h2bandColor":"0x0055FF","h2x":"90","h2y":"32","h2delay":"0","h2duration":"1000","h2outline":false,"h2line":false,"h2linesColor":"0x000000","m1trans":false,"m1dir":"6","m1numberColor":"0xFFFFFF","m1bandColor":"0x00ff00","m1x":"40","m1y":"97","m1delay":"600","m1duration":"1000","m1outline":false,"m1line":false,"m1linesColor":"0x000000","m2trans":false,"m2dir":"7","m2numberColor":"0xFFFFFF","m2bandColor":"0x009600","m2x":"90","m2y":"97","m2delay":"100","m2duration":"1000","m2outline":false,"m2line":false,"m2linesColor":"0x000000","invertanimationdelay":true,"changeallnumbers":true,"layer1":"1","layer2":"2","layer3":"3","layer4":"4"}');
  if($num==='2')  importdata('{"backgroundColor":"0x000000","twentyFourHourFormat":false,"h1dir":"7","h1numberColor":"0xffffff","h1bandColor":"0x00AAFF","h1x":"28","h1y":"22","h1delay":"0","h1duration":"1000","h1outline":false,"h1line":false,"h1linesColor":"0x0055FF","h2trans":false,"h2dir":"3","h2numberColor":"0xffffff","h2bandColor":"0x0055FF","h2x":"63","h2y":"22","h2delay":"500","h2duration":"1000","h2outline":false,"h2line":false,"h2linesColor":"0x000000","m1trans":false,"m1dir":"7","m1numberColor":"0xffffff","m1bandColor":"0x759d76","m1x":"58","m1y":"94","m1delay":"600","m1duration":"1000","m1outline":false,"m1line":false,"m1linesColor":"0x000000","m2trans":false,"m2dir":"3","m2numberColor":"0xffffff","m2bandColor":"0x8ee69e","m2x":"93","m2y":"94","m2delay":"100","m2duration":"1000","m2outline":false,"m2line":false,"m2linesColor":"0x000000","invertanimationdelay":true,"changeallnumbers":true,"layer1":"2","layer2":"1","layer3":"3","layer4":"4"}');
  if($num==='3')  importdata('{"backgroundColor":"0x000000","twentyFourHourFormat":false,"h1dir":"8","h1numberColor":"0xffffff","h1bandColor":"0x00AAFF","h1x":"41","h1y":"31","h1delay":"0","h1duration":"1000","h1outline":false,"h1line":false,"h1linesColor":"0x0055FF","h2trans":false,"h2dir":"2","h2numberColor":"0xffffff","h2bandColor":"0xe35462","h2x":"73","h2y":"31","h2delay":"500","h2duration":"1000","h2outline":false,"h2line":false,"h2linesColor":"0x000000","m1trans":false,"m1dir":"6","m1numberColor":"0xffffff","m1bandColor":"0xafa072","m1x":"41","m1y":"87","m1delay":"600","m1duration":"1000","m1outline":false,"m1line":false,"m1linesColor":"0x000000","m2trans":false,"m2dir":"4","m2numberColor":"0xffffff","m2bandColor":"0x5c9b72","m2x":"73","m2y":"87","m2delay":"100","m2duration":"1000","m2outline":false,"m2line":false,"m2linesColor":"0x000000","invertanimationdelay":true,"changeallnumbers":true,"layer1":"2","layer2":"1","layer3":"3","layer4":"4"}');
  
}


function importHandler() {

  var $import = $('#import');
  var $generatse = $('#generatse');
    $import.on('click', function() {
    console.log('import');
    importdata($generatse.val());
    //

  /*  var options = JSON.parse(decodeURIComponent($generatse.val()));
    
  localStorage.backgroundColor = options.backgroundColor;
  localStorage.twentyFourHourFormat = options.twentyFourHourFormat;
  localStorage.h1dir = options.h1dir;
  localStorage.h1numberColor = options.h1numberColor;
  localStorage.h1bandColor = options.h1bandColor;
  localStorage.h1x = options.h1x;
  localStorage.h1y = options.h1y;
  localStorage.h1delay = options.h1delay;
  localStorage.h1duration = options.h1duration;
  localStorage.h1outline = options.h1outline;
  localStorage.h1line = options.h1line;
  localStorage.h1linesColor = options.h1linesColor;
  
  
  localStorage.h2trans = options.h2trans;
  localStorage.h2dir = options.h2dir;
  localStorage.h2numberColor = options.h2numberColor;
  localStorage.h2bandColor = options.h2bandColor;
  localStorage.h2x = options.h2x;
  localStorage.h2y = options.h2y;
  localStorage.h2delay = options.h2delay;
  localStorage.h2duration = options.h2duration;
  localStorage.h2outline = options.h2outline;
  localStorage.h2line = options.h2line;
  localStorage.h2linesColor = options.h2linesColor;
  
  
  localStorage.m1trans = options.m1trans;
  localStorage.m1dir = options.m1dir;
  localStorage.m1numberColor = options.m1numberColor;
  localStorage.m1bandColor = options.m1bandColor;
  localStorage.m1x = options.m1x;
  localStorage.m1y = options.m1y;
  localStorage.m1delay = options.m1delay;
  localStorage.m1duration = options.m1duration;
  localStorage.m1outline = options.m1outline;
  localStorage.m1line = options.m1line;
  localStorage.m1linesColor = options.m1linesColor;
  
  
  localStorage.m2trans = options.m2trans;
  localStorage.m2dir = options.m2dir;
  localStorage.m2numberColor = options.m2numberColor;
  localStorage.m2bandColor = options.m2bandColor;
  localStorage.m2x = options.m2x;
  localStorage.m2y = options.m2y;
  localStorage.m2delay = options.m2delay;
  localStorage.m2duration = options.m2duration;
  localStorage.m2outline = options.m2outline;
  localStorage.m2line = options.m2line;
  localStorage.m2linesColor = options.m2linesColor;
  
  localStorage.invertanimationdelay = options.invertanimationdelay;
  localStorage.changeallnumbers = options.changeallnumbers;
  
  
  localStorage.layer1 = options.layer1;
  localStorage.layer2 = options.layer2;
  localStorage.layer3 = options.layer3;
  localStorage.layer4 = options.layer4;
    
    
    
    //
    var return_to = getQueryParam('return_to', 'pebblejs://close#');
    document.location = return_to + $generatse.val();*/
  });
  
}

function submitHandler() {
  var $submitButton = $('#submitButton');

  $submitButton.on('click', function() {
    console.log('Submit');

    var return_to = getQueryParam('return_to', 'pebblejs://close#');
    document.location = return_to + encodeURIComponent(JSON.stringify(getAndStoreConfigData()));
  });
}


function layerload($list,$value) {
  if($value==="1"){
    $list.innerHTML="First Hour Digit";
    $list.value="1";
  }
    if($value==="2"){
    $list.innerHTML="Second Hour Digit";
    $list.value="2";
  }
    if($value==="3"){
    $list.innerHTML="First Minute Digit";
    $list.value="3";
  }
    if($value==="4"){
    $list.innerHTML="Second Minute Digit";
    $list.value="4";
  }
  
}

function loadOptions() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');
  var $h1dirpic = $('#h1dirpic');
  var $h1numberColorPicker = $('#h1numberColorPicker');
  var $h1bandColorPicker = $('#h1bandColorPicker');
  var $h1xPicker = $('#h1xPicker');
  var $h1yPicker = $('#h1yPicker');
  var $h1delayPicker = $('#h1delayPicker');
  var $h1durationPicker = $('#h1durationPicker');
  var $h1outlineCheckbox = $('#h1outlineCheckbox');
  var $h1lineCheckbox = $('#h1lineCheckbox');
  var $h1linesColorPicker = $('#h1linesColorPicker');
  
  
  var $h2transCheckbox = $('#h2transCheckbox');
  var $h2dirpic = $('#h2dirpic');
  var $h2numberColorPicker = $('#h2numberColorPicker');
  var $h2bandColorPicker = $('#h2bandColorPicker');
  var $h2xPicker = $('#h2xPicker');
  var $h2yPicker = $('#h2yPicker');
  var $h2delayPicker = $('#h2delayPicker');
  var $h2durationPicker = $('#h2durationPicker');
  var $h2outlineCheckbox = $('#h2outlineCheckbox');
  var $h2lineCheckbox = $('#h2lineCheckbox');
  var $h2linesColorPicker = $('#h2linesColorPicker');
  
  
  var $m1transCheckbox = $('#m1transCheckbox');
  var $m1dirpic = $('#m1dirpic');
  var $m1numberColorPicker = $('#m1numberColorPicker');
  var $m1bandColorPicker = $('#m1bandColorPicker');
  var $m1xPicker = $('#m1xPicker');
  var $m1yPicker = $('#m1yPicker');
  var $m1delayPicker = $('#m1delayPicker');
  var $m1durationPicker = $('#m1durationPicker');
  var $m1outlineCheckbox = $('#m1outlineCheckbox');
  var $m1lineCheckbox = $('#m1lineCheckbox');
  var $m1linesColorPicker = $('#m1linesColorPicker');
  
  var $m2transCheckbox = $('#m2transCheckbox');
  var $m2dirpic = $('#m2dirpic');
  var $m2numberColorPicker = $('#m2numberColorPicker');
  var $m2bandColorPicker = $('#m2bandColorPicker');
  var $m2xPicker = $('#m2xPicker');
  var $m2yPicker = $('#m2yPicker');
  var $m2delayPicker = $('#m2delayPicker');
  var $m2durationPicker = $('#m2durationPicker');
  var $m2outlineCheckbox = $('#m2outlineCheckbox');
  var $m2lineCheckbox = $('#m2lineCheckbox');
  var $m2linesColorPicker = $('#m2linesColorPicker');
  
  
  var $invertanimationdelaycheckbox = $('#invertanimationdelaycheckbox');
  var $changeallnumberscheckbox = $('#changeallnumberscheckbox');
  
  var $Layerlist = $('#Layerlist');
  var $list = Layerlist.getElementsByTagName('li');

  layerload($list[0],localStorage.layer1);
  layerload($list[1],localStorage.layer2);
  layerload($list[2],localStorage.layer3);
  layerload($list[3],localStorage.layer4);
  //$list[0].innerHTML="hi";
  //$list[0].value=1;


  if (localStorage.backgroundColor) {
    $backgroundColorPicker[0].value = localStorage.backgroundColor;
    $timeFormatCheckbox[0].checked = localStorage.twentyFourHourFormat === 'true';
    $h1dirpic[0].value = localStorage.h1dir;
    $h1numberColorPicker[0].value = localStorage.h1numberColor;
    $h1bandColorPicker[0].value = localStorage.h1bandColor;
    $h1xPicker[0].value = localStorage.h1x;
    $h1yPicker[0].value = localStorage.h1y;
    $h1delayPicker[0].value = localStorage.h1delay;
    $h1durationPicker[0].value = localStorage.h1duration;
    $h1outlineCheckbox[0].checked = localStorage.h1outline === 'true';
    $h1lineCheckbox[0].checked = localStorage.h1line === 'true';
    $h1linesColorPicker[0].value = localStorage.h1linesColor;
    
    $h2transCheckbox[0].checked = localStorage.h2trans === 'true';
    $h2dirpic[0].value = localStorage.h2dir;
    $h2numberColorPicker[0].value = localStorage.h2numberColor;
    $h2bandColorPicker[0].value = localStorage.h2bandColor;
    $h2xPicker[0].value = localStorage.h2x;
    $h2yPicker[0].value = localStorage.h2y;
    $h2delayPicker[0].value = localStorage.h2delay;
    $h2durationPicker[0].value = localStorage.h2duration;
    $h2outlineCheckbox[0].checked = localStorage.h2outline === 'true';
    $h2lineCheckbox[0].checked = localStorage.h2line === 'true';
    $h2linesColorPicker[0].value = localStorage.h2linesColor;
    
    $m1transCheckbox[0].checked = localStorage.m1trans === 'true';
    $m1dirpic[0].value = localStorage.m1dir;
    $m1numberColorPicker[0].value = localStorage.m1numberColor;
    $m1bandColorPicker[0].value = localStorage.m1bandColor;
    $m1xPicker[0].value = localStorage.m1x;
    $m1yPicker[0].value = localStorage.m1y;
    $m1delayPicker[0].value = localStorage.m1delay;
    $m1durationPicker[0].value = localStorage.m1duration;
    $m1outlineCheckbox[0].checked = localStorage.m1outline === 'true';
    $m1lineCheckbox[0].checked = localStorage.m1line === 'true';
    $m1linesColorPicker[0].value = localStorage.m1linesColor;
    
    $m2transCheckbox[0].checked = localStorage.m2trans === 'true';
    $m2dirpic[0].value = localStorage.m2dir;
    $m2numberColorPicker[0].value = localStorage.m2numberColor;
    $m2bandColorPicker[0].value = localStorage.m2bandColor;
    $m2xPicker[0].value = localStorage.m2x;
    $m2yPicker[0].value = localStorage.m2y;
    $m2delayPicker[0].value = localStorage.m2delay;
    $m2durationPicker[0].value = localStorage.m2duration;
    $m2outlineCheckbox[0].checked = localStorage.m2outline === 'true';
    $m2lineCheckbox[0].checked = localStorage.m2line === 'true';
    $m2linesColorPicker[0].value = localStorage.m2linesColor;
    
    $invertanimationdelaycheckbox[0].checked = localStorage.invertanimationdelay === 'true';
    $changeallnumberscheckbox[0].checked = localStorage.changeallnumbers === 'true';
  }else{
    importdata('{"backgroundColor":"0x000000","twentyFourHourFormat":false,"h1dir":"8","h1numberColor":"0xFFFFFF","h1bandColor":"0x00AAFF","h1x":"40","h1y":"32","h1delay":"500","h1duration":"1000","h1outline":false,"h1line":false,"h1linesColor":"0x0055FF","h2trans":false,"h2dir":"7","h2numberColor":"0xFFFFFF","h2bandColor":"0x0055FF","h2x":"90","h2y":"32","h2delay":"0","h2duration":"1000","h2outline":false,"h2line":false,"h2linesColor":"0x000000","m1trans":false,"m1dir":"6","m1numberColor":"0xFFFFFF","m1bandColor":"0x00ff00","m1x":"40","m1y":"97","m1delay":"600","m1duration":"1000","m1outline":false,"m1line":false,"m1linesColor":"0x000000","m2trans":false,"m2dir":"7","m2numberColor":"0xFFFFFF","m2bandColor":"0x009600","m2x":"90","m2y":"97","m2delay":"100","m2duration":"1000","m2outline":false,"m2line":false,"m2linesColor":"0x000000","invertanimationdelay":true,"changeallnumbers":true,"layer1":"1","layer2":"2","layer3":"3","layer4":"4"}');
  }
}

function getAndStoreConfigData() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');
  var $h1dirpic = $('#h1dirpic');
  var $h1numberColorPicker = $('#h1numberColorPicker');
  var $h1bandColorPicker = $('#h1bandColorPicker');
  var $h1xPicker = $('#h1xPicker');
  var $h1yPicker = $('#h1yPicker');
  var $h1delayPicker = $('#h1delayPicker');
  var $h1durationPicker = $('#h1durationPicker');
  var $h1outlineCheckbox = $('#h1outlineCheckbox');
  var $h1lineCheckbox = $('#h1lineCheckbox');
  var $h1linesColorPicker = $('#h1linesColorPicker');
  
  
  var $h2transCheckbox = $('#h2transCheckbox');
  var $h2dirpic = $('#h2dirpic');
  var $h2numberColorPicker = $('#h2numberColorPicker');
  var $h2bandColorPicker = $('#h2bandColorPicker');
  var $h2xPicker = $('#h2xPicker');
  var $h2yPicker = $('#h2yPicker');
  var $h2delayPicker = $('#h2delayPicker');
  var $h2durationPicker = $('#h2durationPicker');
  var $h2outlineCheckbox = $('#h2outlineCheckbox');
  var $h2lineCheckbox = $('#h2lineCheckbox');
  var $h2linesColorPicker = $('#h2linesColorPicker');
  
  
  var $m1transCheckbox = $('#m1transCheckbox');
  var $m1dirpic = $('#m1dirpic');
  var $m1numberColorPicker = $('#m1numberColorPicker');
  var $m1bandColorPicker = $('#m1bandColorPicker');
  var $m1xPicker = $('#m1xPicker');
  var $m1yPicker = $('#m1yPicker');
  var $m1delayPicker = $('#m1delayPicker');
  var $m1durationPicker = $('#m1durationPicker');
  var $m1outlineCheckbox = $('#m1outlineCheckbox');
  var $m1lineCheckbox = $('#m1lineCheckbox');
  var $m1linesColorPicker = $('#m1linesColorPicker');
  
  
  var $m2transCheckbox = $('#m2transCheckbox');
  var $m2dirpic = $('#m2dirpic');
  var $m2numberColorPicker = $('#m2numberColorPicker');
  var $m2bandColorPicker = $('#m2bandColorPicker');
  var $m2xPicker = $('#m2xPicker');
  var $m2yPicker = $('#m2yPicker');
  var $m2delayPicker = $('#m2delayPicker');
  var $m2durationPicker = $('#m2durationPicker');
  var $m2outlineCheckbox = $('#m2outlineCheckbox');
  var $m2lineCheckbox = $('#m2lineCheckbox');
  var $m2linesColorPicker = $('#m2linesColorPicker');
  
  var $invertanimationdelaycheckbox = $('#invertanimationdelaycheckbox');
  var $changeallnumberscheckbox = $('#changeallnumberscheckbox');
  
  var $Layerlist = $('#Layerlist');
  $list = Layerlist.getElementsByTagName('li');

  var options = {
    backgroundColor: $backgroundColorPicker.val(),
    twentyFourHourFormat: $timeFormatCheckbox[0].checked,
    h1dir: $h1dirpic.val(),
    h1numberColor: $h1numberColorPicker.val(),
    h1bandColor: $h1bandColorPicker.val(),
    h1x: $h1xPicker.val(),
    h1y: $h1yPicker.val(),
    h1delay: $h1delayPicker.val(),
    h1duration: $h1durationPicker.val(),
    h1outline: $h1outlineCheckbox[0].checked,
    h1line: $h1lineCheckbox[0].checked,
    h1linesColor: $h1linesColorPicker.val(),
    
    
    h2trans: $h2transCheckbox[0].checked,
    h2dir: $h2dirpic.val(),
    h2numberColor: $h2numberColorPicker.val(),
    h2bandColor: $h2bandColorPicker.val(),
    h2x: $h2xPicker.val(),
    h2y: $h2yPicker.val(),
    h2delay: $h2delayPicker.val(),
    h2duration: $h2durationPicker.val(),
    h2outline: $h2outlineCheckbox[0].checked,
    h2line: $h2lineCheckbox[0].checked,
    h2linesColor: $h2linesColorPicker.val(),   
    
    
    m1trans: $m1transCheckbox[0].checked,
    m1dir: $m1dirpic.val(),
    m1numberColor: $m1numberColorPicker.val(),
    m1bandColor: $m1bandColorPicker.val(),
    m1x: $m1xPicker.val(),
    m1y: $m1yPicker.val(),
    m1delay: $m1delayPicker.val(),
    m1duration: $m1durationPicker.val(),
    m1outline: $m1outlineCheckbox[0].checked,
    m1line: $m1lineCheckbox[0].checked,
    m1linesColor: $m1linesColorPicker.val(),   
    
    
    m2trans: $m2transCheckbox[0].checked,
    m2dir: $m2dirpic.val(),
    m2numberColor: $m2numberColorPicker.val(),
    m2bandColor: $m2bandColorPicker.val(),
    m2x: $m2xPicker.val(),
    m2y: $m2yPicker.val(),
    m2delay: $m2delayPicker.val(),
    m2duration: $m2durationPicker.val(),
    m2outline: $m2outlineCheckbox[0].checked,
    m2line: $m2lineCheckbox[0].checked,
    m2linesColor: $m2linesColorPicker.val(),   
    
    invertanimationdelay: $invertanimationdelaycheckbox[0].checked,
    changeallnumbers: $changeallnumberscheckbox[0].checked,
    
    layer1: $list[0].value,
    layer2: $list[1].value,
    layer3: $list[2].value,
    layer4: $list[3].value,
  };

  localStorage.backgroundColor = options.backgroundColor;
  localStorage.twentyFourHourFormat = options.twentyFourHourFormat;
  localStorage.h1dir = options.h1dir;
  localStorage.h1numberColor = options.h1numberColor;
  localStorage.h1bandColor = options.h1bandColor;
  localStorage.h1x = options.h1x;
  localStorage.h1y = options.h1y;
  localStorage.h1delay = options.h1delay;
  localStorage.h1duration = options.h1duration;
  localStorage.h1outline = options.h1outline;
  localStorage.h1line = options.h1line;
  localStorage.h1linesColor = options.h1linesColor;
  
  
  localStorage.h2trans = options.h2trans;
  localStorage.h2dir = options.h2dir;
  localStorage.h2numberColor = options.h2numberColor;
  localStorage.h2bandColor = options.h2bandColor;
  localStorage.h2x = options.h2x;
  localStorage.h2y = options.h2y;
  localStorage.h2delay = options.h2delay;
  localStorage.h2duration = options.h2duration;
  localStorage.h2outline = options.h2outline;
  localStorage.h2line = options.h2line;
  localStorage.h2linesColor = options.h2linesColor;
  
  
  localStorage.m1trans = options.m1trans;
  localStorage.m1dir = options.m1dir;
  localStorage.m1numberColor = options.m1numberColor;
  localStorage.m1bandColor = options.m1bandColor;
  localStorage.m1x = options.m1x;
  localStorage.m1y = options.m1y;
  localStorage.m1delay = options.m1delay;
  localStorage.m1duration = options.m1duration;
  localStorage.m1outline = options.m1outline;
  localStorage.m1line = options.m1line;
  localStorage.m1linesColor = options.m1linesColor;
  
  
  localStorage.m2trans = options.m2trans;
  localStorage.m2dir = options.m2dir;
  localStorage.m2numberColor = options.m2numberColor;
  localStorage.m2bandColor = options.m2bandColor;
  localStorage.m2x = options.m2x;
  localStorage.m2y = options.m2y;
  localStorage.m2delay = options.m2delay;
  localStorage.m2duration = options.m2duration;
  localStorage.m2outline = options.m2outline;
  localStorage.m2line = options.m2line;
  localStorage.m2linesColor = options.m2linesColor;
  
  localStorage.invertanimationdelay = options.invertanimationdelay;
  localStorage.changeallnumbers = options.changeallnumbers;
  
  
  localStorage.layer1 = options.layer1;
  localStorage.layer2 = options.layer2;
  localStorage.layer3 = options.layer3;
  localStorage.layer4 = options.layer4;


  console.log('Got options: ' + JSON.stringify(options));
  return options;
}

function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}
