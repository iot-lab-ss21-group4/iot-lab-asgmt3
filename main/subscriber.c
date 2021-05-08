#include "common.h"
#include "subscriber.h"
#include "commands.h"

#define MQTT_SUB_TOPIC "iot-lab-ss21-group4/count-event"
#define ENTERED_MSG "entered"
#define EXITED_MSG "exited"

static void custom_topic_handler(const char *data, int data_len)
{
	if (strncmp(data, ENTERED_MSG, data_len) == 0)
	{
		enterRoom();
	}
	else if (strncmp(data, EXITED_MSG, data_len) == 0)
	{
		leaveRoom();
	}
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
	esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
	esp_mqtt_client_handle_t client = event->client;
	int msg_id;
	// your_context_t *context = event->context;
	switch (event->event_id)
	{
	case MQTT_EVENT_CONNECTED:
		ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
		msg_id = esp_mqtt_client_subscribe(client, MQTT_SUB_TOPIC, 0);
		ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
		break;
	case MQTT_EVENT_DISCONNECTED:
		ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
		break;
	case MQTT_EVENT_SUBSCRIBED:
		break;
	case MQTT_EVENT_UNSUBSCRIBED:
		ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
		msg_id = esp_mqtt_client_subscribe(client, MQTT_SUB_TOPIC, 0);
		ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
		break;
	case MQTT_EVENT_PUBLISHED:
		break;
	case MQTT_EVENT_DATA:
		if (strncmp(event->topic, MQTT_SUB_TOPIC, event->topic_len) == 0)
		{
			custom_topic_handler(event->data, event->data_len);
		}
		ESP_LOGI(TAG, "TOPIC=%.*s", event->topic_len, event->topic);
		ESP_LOGI(TAG, "DATA=%.*s", event->data_len, event->data);
		break;
	case MQTT_EVENT_ERROR:
		ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
		break;
	default:
		ESP_LOGI(TAG, "Other event id:%d", event->event_id);
		break;
	}
}

void setup_subscriber()
{
	gpio_set_direction(TRIGGER_PIN_IN, GPIO_MODE_OUTPUT);
	gpio_set_direction(TRIGGER_PIN_OUT, GPIO_MODE_OUTPUT);

	esp_mqtt_client_config_t mqtt_cfg = {
		.uri = CONFIG_BROKER_URI,
	};
	esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
	esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
	esp_mqtt_client_start(client);
}
