#include "common.h"
#include "oled.h"
#include "transitions.h"
#include "home_wifi.h"
#include "time_management.h"

#define PUBLISHER true

void run_as_publisher(void){
	setup_transitions();
	while (1)
	{
		loop_oled();
		// TODO: transitions are duplicate code. Think of using a submodule and add as component if possible
		loop_transitions();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void run_as_subscriber(void){
	while (1)
	{
		loop_oled();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}


void app_main(void)
{
    init_logging();
    init_common_queues();

    //Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

    setup_wifi();
    setup_sntp();
    setup_oled();

    //TODO: MQTT events
    //TODO: can ESP be publisher and subscriber ?
    (PUBLISHER) ? run_as_publisher() : run_as_subscriber();
}
