
// Dependencies.
var express = require('express');
var http = require('http');
var path = require('path');
var socketIO = require('socket.io');


var app = express();
var server = http.Server(app);
var io = socketIO(server);


app.set('port', 8000);

app.use(express.static( '/home/xxx/multibridge/LibreBridge'));

// Routing
app.get('/', function(request, response) {

  response.sendFile(path.join( '/home/xxx/multibridge/LibreBridge.html')); 
});


server.listen(8000, function() {
  console.log('Starting server on port 8000');
}); 



io.on('connection', (socket)=> {
// socket.on('Play', function(message){
  socket.on('PlayAgain',(message)=> {
  console.log('PlayAgain Server')
  socket.broadcast.emit('Play')
    })
});



