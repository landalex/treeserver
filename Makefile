WORKDIR=$(HOME)/treeserver

SRC=treeServer.c gpio.c
OPTS=-Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 

all: clean tree

clean:
	rm -rf treeServer

tree:
	arm-linux-gnueabihf-gcc $(OPTS) -o treeServer $(SRC)
	cp -r * /mnt/hgfs/AlexLand/GitHub/treeserver/
	scp -r ../treeserver pi@192.168.0.11:~/

# wav:
# 	mkdir -p $(PUBDIR)/beatbox-wav-files/ 
# 	cp -R beatbox-wav-files/* $(PUBDIR)/beatbox-wav-files/ 

# node:
# 	mkdir -p $(PUBDIR)/beatbox-server-copy/ 
# 	cp -R as3-server/* $(PUBDIR)/beatbox-server-copy/
