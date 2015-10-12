var PARTICLE_API = 'https://api.particle.io/v1/devices/';
var DEVICE_ID='26001a000a47343232363230/';
var PARTICLE_PHOTON=PARTICLE_API+DEVICE_ID;
var PB_API_PUSH='https://api.pushbullet.com/v2/pushes';
var x=0,y=0;
var previousX=0, previousY=0;
var timer10;
function textToSend(x,y){
  var newX="",newY="";
  if(x!=previousX){
    newX=((x&0xF0)+65).toString()+(((x&0x0F)>>4)+65).toString();
  }
  if(y!=previousY){
    newY=((y&0xF0)+65).toString()+(((y&0x0F)>>4)+65).toString();
  }
}
function sendToPhotonCloud(request,type, callback,message){
  var PhotonCloud = new XMLHttpRequest();
  PhotonCloud.onLoad=function(){
    callback(this.responseText, this.status);
  };
  PhotonCloud.open(type,PARTICLE_PHOTON + request);
  PhotonCloud.setRequestHeader('Authorization', 'Bearer 82ab18e82b8c24785faa41dfd4dfe33395e17287');
  if(type=='POST')PhotonCloud.send(message);
  else PhotonCloud.send();
}
function sendToPB(callback,to_send){
  var PushBullet = new XMLHttpRequest();
  PushBullet.onLoad=function(){
    callback(this.responseText);
  };
  PushBullet.open('POST',PB_API_PUSH);
  PushBullet.setRequestHeader('Authorization', 'Bearer wpSInCiKw1l6vy1WnieFBgCiiaxfYotL');
  PushBullet.setRequestHeader('Content-Type', 'application/json');
  PushBullet.send(to_send);
}
Pebble.addEventListener('ready',function(e){
  console.log('PebbleKit JS ready!');
  //timer10=setInterval(function(){sendToPhotonTCP(function(text,status){},'T');},10000);
});
Pebble.addEventListener('appmessage',function(e){
  if(e.payload.Left_Value)x=e.payload.Left_Value;
  if(e.payload.Right_Value)y=e.payload.Right_Value;
  console.log('messege recieved');
  /*var sending = {
    type: "note",
    title: "PebbleCoords",
    body: ("X=" + x + " Y="+y)
  };
  sendToPB(function(resp){console.log(resp);},JSON.stringify(sending));
  console.log(JSON.stringify(sending));*/
});