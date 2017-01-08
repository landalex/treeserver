#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define UDP_SERVER_PORT 1337

#define MESSAGE_MAX_LEN 8
#define MESSAGE_ON "on"
#define MESSAGE_ON_LEN 2
#define MESSAGE_OFF "off"
#define MESSAGE_OFF_LEN 3

static int socketFileDesc;
static struct sockaddr_in socketAddress;
static unsigned int socketAddressLen;

static void createAndBindSocket()
{
	socketFileDesc = socket(PF_INET, SOCK_DGRAM, 0);
	if (socketFileDesc == -1) {
		perror("Unable to create UDP socket.");
		exit(EXIT_FAILURE);
	}

	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	socketAddress.sin_port = htons(UDP_SERVER_PORT);

	socketAddressLen = sizeof(socketAddress);

	int bindValue = bind(socketFileDesc, (struct sockaddr *) &socketAddress,
						 socketAddressLen);
	if (bindValue == -1) {
		perror("Unable to bind socket to port UDP_SERVER_PORT.");
		exit(EXIT_FAILURE);
	}
}

static void receiveMessage(char* message, int len)
{
	int bytesRead = recvfrom(socketFileDesc, message, len, 0,
						(struct sockaddr *) &socketAddress, &socketAddressLen);
	message[bytesRead] = '\0';
}

static void sendMessage(char* message)
{
	sendto(socketFileDesc, message, strlen(message),
		   0, (struct sockaddr *) &socketAddress, socketAddressLen);
}

static void handleMessage(char* message, int len)
{
	if (strncmp(message, MESSAGE_ON, MESSAGE_ON_LEN) == 0) {
		GPIO_turnTreeOn();
	}
	else if (strncmp(message, MESSAGE_OFF, MESSAGE_OFF_LEN) == 0) {
		GPIO_turnTreeOff();
	}
}

int main()
{
	GPIO_initialize();

	createAndBindSocket();

	char message[MESSAGE_MAX_LEN];
	while (1) {
		receiveMessage(message, MESSAGE_MAX_LEN);
		printf("RECEIVED: %s\n", message);
		handleMessage(message, MESSAGE_MAX_LEN);
		sendMessage(message);
	}
}