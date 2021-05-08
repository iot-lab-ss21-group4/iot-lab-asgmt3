#include "common.h"
#include "commands.h"

void leaveRoom()
{
	ESP_LOGI(TAG, "Command: Leave");
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(500 / portTICK_RATE_MS);
}

void enterRoom()
{
	ESP_LOGI(TAG, "Command: Enter");
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(500 / portTICK_RATE_MS);
}
