#include "common.h"
#include "oled.h"
#include "transitions.h"
#include "home_wifi.h"
#include "time_management.h"
#include "commands.h"
#include "subscriber.h"

// can be removed later
void test_trigger_pins()
{
	enterRoom();
	if(count == 1){
		ESP_LOGI(TAG, "Test Enter Room: Ok");
	}else {
		ESP_LOGE(TAG, "Test Enter Room: Fail");
	}
	leaveRoom();
	if(count == 0){
		ESP_LOGI(TAG, "Test Leave Room: Ok");
	}else {
		ESP_LOGE(TAG, "Test Leave Room: Fail");
	}
}

void app_main(void)
{
	init_logging();
	init_common_queues();
	init_esp_dependencies();

	setup_wifi();
	setup_time_management();
	setup_oled();
	setup_transitions();

#if SUBSCRIBER
	setup_subscriber();
	test_trigger_pins();
#endif

	while (1)
	{
		loop_oled();
		loop_transitions();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
