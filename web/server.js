"use strict";

var http = require('http');
var server = http.createServer(function(request, response) {
	var filePath = false;

	if (request.url == '/') {
		filePath = 'public/index.html';
	} else {
		filePath = 'public' + request.url;
	}

	var absPath = './' + filePath;
	serveStatic(response, absPath);
});

var PORT_NUMBER = 80;
server.listen(PORT_NUMBER, function() {
	console.log("Server listening on port " + PORT_NUMBER);
});

var fs = require('fs');
function serveStatic(response, absPath) {
	fs.exists(absPath, function(exists) {
		if (exists) {
			fs.readFile(absPath, function(err, data) {
				if (err) {
					send404(response);
				} else {
					sendFile(response, absPath, data);
				}
			});
		} else {
			send404(response);
		}
	});
}

function send404(response) {
	response.writeHead(404, {'Content-Type': 'text/plain'});
	response.write('Error 404: resource not found.');
	response.end();
}

var mime = require('mime');
var path = require('path');
function sendFile(response, filePath, fileContents) {
	response.writeHead(
			200,
			{"content-type": mime.lookup(path.basename(filePath))}
		);
	response.end(fileContents);
}

var Gun = require('gun');
var gun = Gun();
gun.wsp(server);

var tree = gun.get("tree");
tree.put({isOn: false});
tree.on(function(data) {
	console.log("Updated tree!", data);
});

var udpServer = require('./lib/udpServer.js');
udpServer.listen(server, tree);


// "use strict";
//
// var net = require('net');
// var HOST = "127.0.0.1";
// var PORT = 1337;
//
// net.createServer(function(socket) {
// 	socket.on('data', function(data) {
// 		if (data === "on") {
// 			sendPacket(socket, "on");
// 		}
// 		else {
// 			sendPacket(socket, "off");
// 		}
// 	});
// }).listen(PORT, HOST);
//
// var dgram = require('dgram');
// function sendPacket(socket, data) {
// 	var buffer = new Buffer(data);
// 	var client = dgram.createSocket('udp4');
// 	client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
//     if (err)
//     	throw err;
// 	});
//
// 	client.on('message', function (message, remote) {
// 		socket.write(message);
// 	});
// };
