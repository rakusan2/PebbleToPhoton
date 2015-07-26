var x=0,y=0;
function sendToPhoton(){
  
}
Pebble.addEventListener('ready',function(e){
  console.log('PebbleKit JS ready!');
});
Pebble.addEventListener('appmessage',function(e){
  if(e.payload.Left_Value)x=e.payload.Left_Value;
  else if(e.payload.Right_Value)y=e.payload.Right_Value;
  console.log('AppMessage recieved! X='+x+' Y='+y);
});