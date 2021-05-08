#include "common.h"

void setup_subscriber()
{
	gpio_set_direction(TRIGGER_PIN_IN, GPIO_MODE_OUTPUT);
	gpio_set_direction(TRIGGER_PIN_OUT, GPIO_MODE_OUTPUT);

	gpio_pulldown_en(TRIGGER_PIN_IN);
	gpio_pulldown_en(TRIGGER_PIN_OUT);

	//TODO MQTT
}
