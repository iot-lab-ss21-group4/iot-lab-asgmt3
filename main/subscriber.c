#include "common.h"

void setup_subscriber(){
	gpio_set_direction(triggerPinIn, GPIO_MODE_OUTPUT);
	gpio_set_direction(triggerPinOut, GPIO_MODE_OUTPUT);

	gpio_pulldown_en(triggerPinIn);
	gpio_pulldown_en(triggerPinOut);

	//TODO MQTT
}




