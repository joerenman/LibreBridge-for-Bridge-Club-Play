//  example websocket
const WebSocket = require('ws');
const fs = require('fs')
const readline = require('readline');
var ws = new WebSocket.Server({ port: 8010 });
var message='string'
 console.log('Starting WebSocket server on port 8010');
global.startDeal= 'String';

fs.readFile('/home/xxx/multibridge/startdeal.txt', 'utf8', function(err, data) {
  if (err) throw err;
  global.startDeal = data;
});

ws.on('connection', function connection(wsConnection) {
  wsConnection.on('message', function incoming(message) {
    console.log(ws.clients.size,` server received: ${message}`);   
       ws.clients.forEach(function (client) {
   if (client !== wsConnection){ client.send(message) }
   	 if (client ==wsConnection) { 	
    var startupDetected = message.includes('SeatStatusRequest')
    if (startupDetected) {console.log('Startup Detected');
         console.log(global.startDeal);
         client.send(global.startDeal);        
         }
       }
    });      
  });
});




