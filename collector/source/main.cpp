#include "Microbit.h"

MicroBit uBit;

int status = 0;

#define INTERVAL_OF_GET 80
#define NUM_OF_VALUES 6

int xValues[NUM_OF_VALUES];
int yValues[NUM_OF_VALUES];
int zValues[NUM_OF_VALUES];

void onButton(MicroBitEvent e)
{
	if(e.source == MICROBIT_ID_BUTTON_A &&
		e.value == MICROBIT_BUTTON_EVT_DOWN)
		status = 1;
	if(e.source == MICROBIT_ID_BUTTON_A &&
		e.value == MICROBIT_BUTTON_EVT_UP)
		status = 0;
	if(e.source == MICROBIT_ID_BUTTON_B &&
		e.value == MICROBIT_BUTTON_EVT_DOWN)
		status = 2;
	if(e.source == MICROBIT_ID_BUTTON_B &&
		e.value == MICROBIT_BUTTON_EVT_UP)
		status = 0;
}

void clear()
{
	int i;
	for(i = 0; i < NUM_OF_VALUES; i++) {
		xValues[i] = 0;
		yValues[i] = 0;
		zValues[i] = 0;
	}
}

void shift()
{
	int i;
	for(i = NUM_OF_VALUES - 1; i > 0; i--) {
		xValues[i] = xValues[i - 1];
		yValues[i] = yValues[i - 1];
		zValues[i] = zValues[i - 1];
	}
}

int main()
{
	
	uBit.init();
	
	uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButton);
	uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButton);
	
	while(1)
	{
		int accX = uBit.accelerometer.getX();
		int accY = uBit.accelerometer.getY();
		int accZ = uBit.accelerometer.getZ();

		shift();
		xValues[0] = accX;
		yValues[0] = accY;
		zValues[0] = accZ;

		int i = 0;
		for(i = 0; i < NUM_OF_VALUES; i++) {
			uBit.serial.printf("%d,%d,%d,",xValues[i], yValues[i], zValues[i]);
		}
		uBit.serial.printf("%d\r\n", status);
		
		uBit.sleep(INTERVAL_OF_GET);
	}
}
