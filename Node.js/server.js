const fs = require('fs');
const net = require('net');

// var writeStream = fs.createWriteStream('./log.txt');

let count = 0;

// process.on('uncaughtException', (err) => {
//     // writeStream.write(JSON.stringify(err));
//     console.log(count);
//     count++;
//     process.exit(1);
// })


// setTimeout(createServer, 1000);

// let addr = '198.105.215.36';
let addr = '127.0.0.1';
let port = 8888;

createServer();

function createServer(){
    let clients = [];
    
    let server = net.createServer(function(socket)
    {
        console.log("Client Connected");
        // writeStream.write("IP: " + socket.remoteAddress);
        socket.write('Connected to server!\r\n');
        clients[clients.length] = socket;
        if(clients.length > 1)
        {
            //Send to client the clientServer port number.
            clients[clients.length - 1].write('' + clients[0].remotePort + ' ' + clients[0].remoteAddress);
            
            //Send to client server other client port number.
            clients[0].write('' + clients[clients.length - 1].remotePort + ' ' + clients[clients.length - 1].remoteAddress);
            server.close();
        }
        console.log('Port: ' + socket.remotePort + " IP: " + socket.remoteAddress);
        socket.on('data', function(data)
        {
            socket.write(data);
        });
    
    });
    server.listen(port, addr);
    console.log("Server Listening on " + addr + ':' + port);
}






