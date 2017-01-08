"use strict";

var socketio = require("socket.io");
var io;

exports.listen = function(server, tree) {
	// io = socketio.listen(server);
	// io.sockets.on("connection", function(socket) {
	// 	registerCommands(socket);
	// });
	registerCommands(tree);
};

// function registerCommands(socket) {
// 	socket.on("turnOn", function(data) {
// 		sendPacket(socket, "on");
// 	});
//
// 	socket.on("turnOff", function(data) {
// 		sendPacket(socket, "off");
// 	});
// };

function registerCommands(tree) {
	tree.on(function(data) {
		if (data.isOn) {
			sendPacket("on");
		}
		else {
			sendPacket("off");
		}
	})
}

var dgram = require('dgram');
var PORT = 1337;
var HOST = '127.0.0.1';
function sendPacket(data) {
	var buffer = new Buffer(data);
	var client = dgram.createSocket('udp4');
	client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
	    if (err)
	    	throw err;
	});

	// client.on('message', function (message, remote) {
	// 	socket.emit("status", message);
	// });
};
