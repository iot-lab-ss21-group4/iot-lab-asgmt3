#include "common.h"

const char *TAG = "ASGM3";
volatile uint8_t count = 0;
xQueueHandle barrier_evt_q = NULL;
xQueueHandle count_display_q = NULL;

void init_logging()
{
    esp_log_level_set(TAG, ESP_LOG_INFO);
    ESP_LOGI(TAG, "Start");
}

void init_common_queues()
{
    if (barrier_evt_q == NULL)
    {
        barrier_evt_q = xQueueCreate(BARRIER_EVT_Q_SIZE, sizeof(barrier_evt_q_item));
    }
    if (count_display_q == NULL)
    {
        count_display_q = xQueueCreate(COUNT_DISPLAY_Q_SIZE, sizeof(count_display_q_item));
    }
}
