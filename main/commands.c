#include "common.h"
#include "commands.h"

static int expected_room_count = 0;

#define TEST_INIT_ROOM assert_room_count(expected_room_count, "Test Initial Counter");
#define TEST_ENTER_ROOM enterRoom(), expected_room_count++, assert_room_count(expected_room_count, "Test Enter Room");
#define TEST_LEAVE_ROOM leaveRoom(), expected_room_count--, assert_room_count(expected_room_count, "Test Leave Room");
#define TEST_PEAK_OUT_ROOM peakOutofRoom(), assert_room_count(expected_room_count, "Test Peak Out Of Room");
#define TEST_PEAK_IN_ROOM peakIntoRoom(), assert_room_count(expected_room_count, "Test Peak Into Room");
#define TEST_HALFWAY_LEAVE_ROOM halfwayLeave(), assert_room_count(expected_room_count, "Test Halfway Leave Room");
#define TEST_HALFWAY_ENTER_ROOM halfwayEnter(), assert_room_count(expected_room_count, "Test Halfway Enter Room");
#define TEST_MANIPULATION_ENTER_ROOM manipulationEnter(), assert_room_count(expected_room_count, "Test Manipulation Enter Room");
#define TEST_ALMOST_ENTER_ROOM almostEnterRoom(), assert_room_count(expected_room_count, "Test Almost Enter Room");
#define TEST_ALMOST_LEAVE_ROOM almostLeaveRoom(), assert_room_count(expected_room_count, "Test Almost Leave Room");

//////COMMANDS//////

void enterRoom()
{
	ESP_LOGI(TAG, "Command: Enter");
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}

void leaveRoom()
{
	ESP_LOGI(TAG, "Command: Leave");
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}

void almostEnterRoom()
{
	ESP_LOGI(TAG, "Command: Almost enter");
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);

	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}

void almostLeaveRoom()
{
	ESP_LOGI(TAG, "Command: Almost leave");
	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);

	gpio_set_level(TRIGGER_PIN_IN, 1);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN, 0);
	vTaskDelay(200 / portTICK_RATE_MS);
}

void peakIntoRoom(){
/*reach out one's head towards room, then lean back*/
    ESP_LOGI(TAG,"Command: Peak In");
    gpio_set_level(TRIGGER_PIN_OUT,1);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_OUT,0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

void peakOutofRoom(){
    ESP_LOGI(TAG,"Command: Peak Out");
    gpio_set_level(TRIGGER_PIN_IN,1);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_IN,0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

// halfwayEnter in forum but name makes no sense
void halfwayLeave(){
/*someone go to the middle of the doorway, and then turns around*/
    ESP_LOGI(TAG,"Command: Half Leave");
    gpio_set_level(TRIGGER_PIN_IN,1);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_OUT,1);
    vTaskDelay(50 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT,0);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_IN,0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

void halfwayEnter(){
/*someone go to the middle of the doorway, and then turns around*/
    ESP_LOGI(TAG,"Command: Half Enter");
    gpio_set_level(TRIGGER_PIN_OUT,1);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_IN,1);
    vTaskDelay(50 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN,0);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(TRIGGER_PIN_OUT,0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

void manipulationEnter(){
/*Someone is trying to manipulate the count by waving their arm through the barrier towards the inside
 Sequence is not possible if a person enters*/
	ESP_LOGI(TAG,"Command: Manipulation Enter");
	gpio_set_level(TRIGGER_PIN_IN,1);
	vTaskDelay(15 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_IN,0);
	vTaskDelay(15 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT,1);
	vTaskDelay(15 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT,0);
	vTaskDelay(500 / portTICK_RATE_MS);
}

void obstructionInside(){
	/*Someone is standing in the inside barrier, making counting impossible*/
	//TODO test needs separate task
	ESP_LOGI(TAG,"Command: Obstruction Inside");
	gpio_set_level(TRIGGER_PIN_IN,1);
	vTaskDelay(6000 / portTICK_RATE_MS);
	gpio_set_level(TRIGGER_PIN_OUT,1);
	vTaskDelay(3000 / portTICK_RATE_MS);
	/*resolve obstruction*/
	gpio_set_level(TRIGGER_PIN_IN,0);
	gpio_set_level(TRIGGER_PIN_OUT,0);
	vTaskDelay(500 / portTICK_RATE_MS);
}

///////////////////////////////////////

void assert_room_count(int expected_count, char* test_description){
	if(count == expected_count){
		ESP_LOGI(TAG, "%s: Ok", test_description);
	} else {
		ESP_LOGE(TAG, "%s: Fail", test_description);
	}
}

void test_trigger_pins()
{
	in_testing_scenario = true;
	ESP_LOGI(TAG, "Start testing");

	ESP_LOGI(TAG, "Inner Trigger PIN: %d", TRIGGER_PIN_IN);
	ESP_LOGI(TAG, "Outer Trigger PIN: %d", TRIGGER_PIN_OUT);
	ESP_LOGI(TAG, "Inner Barrier PIN: %d", INNER_BARRIER_PIN);
	ESP_LOGI(TAG, "Outer Barrier PIN: %d", OUTER_BARRIER_PIN);

	TEST_INIT_ROOM;

	TEST_ENTER_ROOM;

	TEST_PEAK_OUT_ROOM;

	TEST_ALMOST_LEAVE_ROOM;

	TEST_LEAVE_ROOM;

	TEST_PEAK_IN_ROOM;

	TEST_ALMOST_ENTER_ROOM;

	TEST_HALFWAY_LEAVE_ROOM;

	TEST_HALFWAY_ENTER_ROOM;

	TEST_MANIPULATION_ENTER_ROOM;

	// finish with normal behavior

	TEST_ENTER_ROOM;

	TEST_LEAVE_ROOM;

	in_testing_scenario = false;
	ESP_LOGI(TAG, "End testing");
}
