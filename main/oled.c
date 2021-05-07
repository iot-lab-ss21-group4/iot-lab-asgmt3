#include "common.h"
#include "ssd1306.h"
#include "oled.h"
#include "time_management.h"


#define IOT_LAB_COURSE_GROUP 4
#define GROUP_AND_TIME_PATTERN "G%d  %d:%d"
#define COUNTING_PATTERN "%d%d"

#define GROUP_AND_TIME_BUFFER_SIZE 20
static char GROUP_AND_TIME_BUFFER[GROUP_AND_TIME_BUFFER_SIZE];

#define COUNTING_BUFFER_SIZE 20
static char COUNTING_BUFFER[COUNTING_BUFFER_SIZE];

static void showRoomState();
static void oled_update_task(void *);

static void showRoomState()
{
    ssd1306_clearScreen();
    struct tm current_time = read_time();
    snprintf(GROUP_AND_TIME_BUFFER, GROUP_AND_TIME_BUFFER_SIZE, GROUP_AND_TIME_PATTERN, IOT_LAB_COURSE_GROUP, current_time.tm_hour, current_time.tm_min);
    ssd1306_printFixedN(0, 0, GROUP_AND_TIME_BUFFER, STYLE_NORMAL, 1);
}

static void oled_update_task(void *_)
{
    count_display_q_item local_count = 0;
    while (1)
    {
        while (xQueueReceive(count_display_q, &local_count, portMAX_DELAY) != pdTRUE)
            ;
        showRoomState();
    }
}

void setup_oled()
{
    ssd1306_128x64_i2c_init();
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    showRoomState();
    xTaskCreate(oled_update_task, "oled_update_task", 4096, NULL, 10, NULL);
}

void loop_oled()
{
}
