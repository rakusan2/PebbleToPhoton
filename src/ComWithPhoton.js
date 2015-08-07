var PARTICLE_API = 'https://api.particle.io/v1/devices/';
var DEVICE_ID='26001a000a47343232363230/';
var PARTICLE_PHOTON=PARTICLE_API+DEVICE_ID;
var PB_API_PUSH='https://api.pushbullet.com/v2/pushes';
var SSID_from_Photon ='localSSID?';
var localIP_of_Photon ='localIP?';
var x=0,y=0;
/*function sendToPhoton(request,type, callback){
  var PhotonCloud = new XMLHttpRequest();
  PhotonCloud.onLoad=function(){
    callback(this.responseText);
  }
  PhotonCloud.open(type,PARTICLE_PHOTON + request);
  PhotonCloud.setRequestHeader('Authorization', 'Bearer 0969152112a516860c1da9d679e171745da8a00c');
  PhotonCloud.send();
}*/
function sendToPB(callback,to_send){
  var PhotonCloud = new XMLHttpRequest();
  PhotonCloud.onLoad=function(){
    callback(this.responseText);
  };
  PhotonCloud.open('POST',PB_API_PUSH);
  PhotonCloud.setRequestHeader('Authorization', 'Bearer wpSInCiKw1l6vy1WnieFBgCiiaxfYotL');
  PhotonCloud.setRequestHeader('Content-Type', 'application/json');
  PhotonCloud.send(to_send);
}
Pebble.addEventListener('ready',function(e){
  console.log('PebbleKit JS ready!');
  //sendToPhoton(SSID_from_Photon,'GET',);
  //sendToPhoton(localIP_of_Photon,'GET',);
});
Pebble.addEventListener('appmessage',function(e){
  if(e.payload.Left_Value)x=e.payload.Left_Value;
  if(e.payload.Right_Value)y=e.payload.Right_Value;
  console.log('messege recieved');
  var sending = {
    type: "note",
    title: "PebbleCoords",
    body: ("X=" + x + " Y="+y)
  };
  sendToPB(function(resp){console.log(resp);},JSON.stringify(sending));
  console.log(JSON.stringify(sending));
});