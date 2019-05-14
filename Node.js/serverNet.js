const fs = require('fs');

var writeStream = fs.createWriteStream('./log.txt');

process.on('uncaughtException', (err) => {
    writeStream.write(JSON.stringify(err));
    process.exit(1);
})

setTimeout(function(){
    const externalip = require('externalip');
    const net = require('net');
    // '198.105.215.36'
    const LOCAL_HOST = '127.0.0.1';
    const PORT = 80;
    let EXTERNAL_IP;
    externalip(function(err, ip){
        EXTERNAL_IP = ip;
    })
    writeStream.write("Port: " + PORT);

    let clients = [];

    let server = net.createServer(function(socket)
    {
        writeStream.write("IP: " + socket.remoteAddress);
        socket.write('Connected to server!\r\n');
        clients[clients.length] = socket;
        // if(clients.length > 1)
        // {
        //     //Send to client the clientServer port number.
        //     clients[clients.length - 1].write('' + clients[0].remotePort + ' ' + EXTERNAL_IP);
            
        //     //Send to client server other client port number.
        //     clients[0].write('' + clients[clients.length - 1].remotePort);
        // }
        // console.log('Port: ' + socket.remotePort + " IP: " + socket.remoteAddress);
        socket.on('data', function(data)
        {
            socket.write(data);
        });
    
    });
        server.listen(PORT);
}, 1000)    



