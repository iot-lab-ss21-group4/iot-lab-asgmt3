#include "common.h"

#define SNTP_SERVER "pool.ntp.org"
#define SNTP_SYNC_RETRY 10
// ESP time should be running in 2021
#define ESP_EXPECTED_TIME_YEARS (2021 - 1900)

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

static void initialize_sntp(void)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, SNTP_SERVER);
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
    sntp_init();
}

static void obtain_time(void)
{
    int retry = 0;
    const int retry_count = SNTP_SYNC_RETRY;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    if (retry == retry_count)
    {
        ESP_LOGE(TAG, "Could not retrieve time.!\n");
        esp_restart();
    }
    // Set timezone to MESZ
    setenv("TZ", "UTC-2", 1);
    tzset();
    ESP_LOGI(TAG, "System time set.");
}

struct tm read_time()
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    return timeinfo;
}

bool is_time_set()
{
    struct tm timeinfo = read_time();
    return timeinfo.tm_year >= ESP_EXPECTED_TIME_YEARS;
}

void setup_sntp()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    // TODO why failing?
    //ESP_ERROR_CHECK( esp_event_loop_create_default() );

    initialize_sntp();
    if (!is_time_set())
    {
        obtain_time();
    }
}
