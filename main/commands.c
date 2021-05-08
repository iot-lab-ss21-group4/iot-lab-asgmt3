#include "common.h"
#include "commands.h"

// can be removed later
void test_trigger_pins()
{
	enterRoom();
	if (count == 1)
	{
		ESP_LOGI(TAG, "Test Enter Room: Ok");
	}
	else
	{
		ESP_LOGE(TAG, "Test Enter Room: Fail");
	}
	leaveRoom();
	if (count == 0)
	{
		ESP_LOGI(TAG, "Test Leave Room: Ok");
	}
	else
	{
		ESP_LOGE(TAG, "Test Leave Room: Fail");
	}
}

void enterRoom()
{
	ESP_LOGI(TAG, "Command: Enter");
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}

void leaveRoom()
{
	ESP_LOGI(TAG, "Command: Leave");
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}
