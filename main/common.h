#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_sntp.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    ((byte)&0x80 ? '1' : '0'),     \
        ((byte)&0x40 ? '1' : '0'), \
        ((byte)&0x20 ? '1' : '0'), \
        ((byte)&0x10 ? '1' : '0'), \
        ((byte)&0x08 ? '1' : '0'), \
        ((byte)&0x04 ? '1' : '0'), \
        ((byte)&0x02 ? '1' : '0'), \
        ((byte)&0x01 ? '1' : '0')
#define FIRST_N_BITMASK(n) ((1 << n) - 1)
#define POWER_OF_TWO(x) (1 << (x))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define LOGICAL_NOT(c) ((c) ? false : true)
#define STATIC_ASSERT(COND, MSG) typedef char static_assertion_##MSG[(COND) ? 1 : -1]

typedef uint8_t count_display_q_item;

extern const char *TAG;
extern volatile uint8_t count;
extern const uint16_t COUNT_DISPLAY_Q_SIZE;
extern xQueueHandle count_display_q;

void init_logging();
void init_common_queues();
void init_esp_dependencies();

#endif
