#include "gpio.h"
#include <stdio.h>
#include <pthread.h>

#define GPIO_EXPORT_FILENAME "/sys/class/gpio/export"
#define GPIO_DIRECTION_FILENAME "/sys/class/gpio/gpio3/direction"
#define GPIO_VALUE_FILENAME "/sys/class/gpio/gpio3/value"
#define GPIO_PIN 3

pthread_mutex_t pinMutex = PTHREAD_MUTEX_INITIALIZER;

static int enablePin()
{
	FILE* pGpioExportFile = fopen(GPIO_EXPORT_FILENAME, "w");
	if (pGpioExportFile == NULL) {
		printf("Error opening GPIO export file.\n");
		return 1;
	}

	int charWritten = fprintf(pGpioExportFile, "%d", GPIO_PIN);
	if (charWritten <= 0) {
		printf("Error writing to GPIO export file.\n");
		fclose(pGpioExportFile);
		return 1;
	}

	fclose(pGpioExportFile);
	return 0;
}

static int setPinDirection()
{
	FILE* pGpioDirectionFile = fopen(GPIO_DIRECTION_FILENAME, "w");
	if (pGpioDirectionFile == NULL) {
		printf("Error opening GPIO direction file.\n");
		return 1;
	}

	int charWritten = fprintf(pGpioDirectionFile, "out");
	if (charWritten <= 0) {
		printf("Error writing to GPIO direction file.\n");
		fclose(pGpioDirectionFile);
		return 1;
	}

	fclose(pGpioDirectionFile);
	return 0;
}

static int writeValueToPin(int value)
{
	FILE* pGpioValueFile = fopen(GPIO_VALUE_FILENAME, "w");
	if (pGpioValueFile == NULL) {
		printf("Error opening GPIO value file.\n");
		return 1;
	}

	int charWritten = fprintf(pGpioValueFile, "%d", value);
	if (charWritten <= 0) {
		printf("Error writing to GPIO value file.\n");
		fclose(pGpioValueFile);
		return 1;
	}

	fclose(pGpioValueFile);
	return 0;
}

void GPIO_initialize()
{
	enablePin();
	setPinDirection();
}

void GPIO_turnTreeOn()
{
	int result = 0;
	pthread_mutex_lock(&pinMutex);
	{
		result = writeValueToPin(1);
	}
	pthread_mutex_unlock(&pinMutex);
	printf("Result of writing 1 to pin: %d\n", result);
}

void GPIO_turnTreeOff()
{
	int result = 0;
	pthread_mutex_lock(&pinMutex);
	{
		result = writeValueToPin(0);
	}
	pthread_mutex_unlock(&pinMutex);
	printf("Result of writing 0 to pin: %d\n", result);
}

