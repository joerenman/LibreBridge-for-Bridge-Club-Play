//  example websocket
const WebSocket = require('ws');
const fs = require('fs')
var ws = new WebSocket.Server({ port: 8001 });
var message='string'
 console.log('Starting WebSocket server on port 8001');
 
 var d = new Date();
var filename = "/home/xxx/multibridge/T1_" + (d.getDate()) + (d.getMonth() + 1) +
(d.getFullYear());
var fileextension = ".txt";
var file = filename + fileextension;

ws.on('connection', function connection(wsConnection) {
  wsConnection.on('message', function incoming(message) {
    console.log(ws.clients.size,` server received: ${message}`);
    
       ws.clients.forEach(function (client) {
 
   if (client !== wsConnection) client.send(message) 
          
    });
    var scoreDetected = message.includes('Score:')
    if (scoreDetected) {console.log('Detected Score:');
    const newline ='\n';
    fs.appendFile(file, message, (err) => {
    if (err) {
    console.error(err)
    return  }
    })
    
    fs.appendFile(file, newline, (err) => {
    if (err) {
    console.error(err)
    return  }
    })
    }

  });

});




