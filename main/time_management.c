#include "common.h"

#define SNTP_SERVER "pool.ntp.org"

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

static void initialize_sntp(void){
	ESP_LOGI(TAG, "Initializing SNTP");
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	sntp_setservername(0, SNTP_SERVER);
	sntp_set_time_sync_notification_cb(time_sync_notification_cb);
	sntp_init();
}

static void obtain_time(void)
{
    // datatype for time in seconds since 1.1.1970
    time_t now = 0;

    // linux data structure with calendar data and time broken down into its components
    struct tm timeinfo = { 0 };
    // number of retries waiting for synchronization
    int retry = 0;
    const int retry_count = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    if(retry == retry_count){
    	ESP_LOGE(TAG, "Could not retrieve time.!\n");
    	esp_restart();
    }
    // retrieve time in seconds
    time(&now);
    localtime_r(&now, &timeinfo);
    ESP_LOGI(TAG, "Time set");
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time is: %s", strftime_buf);

    // hours and minutes
    int hours = timeinfo.tm_hour;
    int minutes = timeinfo.tm_min;
    //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

}

void setup_sntp(){
    ESP_ERROR_CHECK(nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    // TODO why failing?
    //ESP_ERROR_CHECK( esp_event_loop_create_default() );
	initialize_sntp();
	obtain_time();
}

struct tm read_time(){
	time_t now;
	struct tm timeinfo;
	time(&now);
	localtime_r(&now, &timeinfo);
	return timeinfo;
}
