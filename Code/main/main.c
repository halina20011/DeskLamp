#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include <esp_http_server.h>
#include "esp_system.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "server.h"
#include "wifi.h"

#include "esp_log.h"

#define RED     GPIO_NUM_2
#define GREEN   GPIO_NUM_0
#define BLUE    GPIO_NUM_3

#define BUTTON      GPIO_NUM_1
#define STATUS_LED  GPIO_NUM_1

// #ifndef __ESP_FILE__
// #define __ESP_FILE__
// #endif

uint32_t LEDS[3] = {RED, GREEN, BLUE};

void app_main(){
    ESP_ERROR_CHECK(nvs_flash_init());

    gpio_config_t ledConfig;
    ledConfig.pin_bit_mask = (1ULL << GREEN) | (1ULL << BLUE);
    ledConfig.mode = GPIO_MODE_OUTPUT;
    ledConfig.intr_type = GPIO_INTR_DISABLE;
    ledConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ledConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&ledConfig);

    ledConfig.pin_bit_mask = (1ULL << RED);
    ledConfig.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&ledConfig);
    
    // gpio_set_intr_type(BUTTON, GPIO_INTR_HIGH_LEVEL);
    // for(uint8_t i = 0; i < 3; i++){
    //     gpio_set_level(LEDS[i], 0);
    // }

    wifiInit();

    // while(1){
    //     for(uint32_t i = 0; i < 3; i++){
    //         gpio_set_level(LEDS[i], 1);
    //         vTaskDelay(1000 / portTICK_RATE_MS);
    //         gpio_set_level(LEDS[i], 0);
    //         vTaskDelay(1000 / portTICK_RATE_MS);
    //     }
    // }
}
