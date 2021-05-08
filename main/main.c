#include "common.h"
#include "oled.h"
#include "transitions.h"
#include "home_wifi.h"
#include "time_management.h"

void app_main(void)
{
	init_logging();
	init_common_queues();

	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	setup_wifi();
	setup_sntp();
	setup_oled();
	setup_transitions();

	while (1)
	{
		loop_oled();
		loop_transitions();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
