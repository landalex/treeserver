"use strict";

$(document).ready(function() {
	var peers = ["http://009a877c.ngrok.io"];
	var gun = Gun(peers);
	var tree = gun.get("tree");

	var treeElement = "#treeImage";
	// socket.emit("turnOff", "off");
	tree.on(function(data) {
		if (data.isOn) {
			$(treeElement).removeClass("off").addClass("on");
		}
		else {
			$(treeElement).removeClass("on").addClass("off");
		}
	});
  $(treeElement).on("click", function() {
		tree.val(function(data) {
			tree.put({isOn: !data.isOn});
		});
      // if (isOn) {
      	// socket.emit("turnOff", "off");
          // $(treeElement).removeClass("on").addClass("off");
          // isOn = false;
      // }
      // else {
      	// socket.emit("turnOn", "on");
          // $(treeElement).removeClass("off").addClass("on");
          // isOn = true;
      // }
  });
});
