#include "common.h"
#include "ssd1306.h"
#include "oled.h"

#define CHAR_BUFFER_SIZE 20

static char CHAR_BUFFER[CHAR_BUFFER_SIZE];

static void showRoomState();
static void oled_update_task(void *);

static void showRoomState()
{
    ssd1306_clearScreen();
    snprintf(CHAR_BUFFER, CHAR_BUFFER_SIZE, "Count: %d", count);
    ssd1306_printFixedN(0, 0, CHAR_BUFFER, STYLE_NORMAL, 1);
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