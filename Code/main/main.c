#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "driver/gpio.h"

#define RED     GPIO_NUM_2
#define GREEN   GPIO_NUM_0
#define BLUE    GPIO_NUM_3

#define BUTTON  GPIO_NUM_1

uint32_t LEDS[3] = {RED, GREEN, BLUE};

void app_main(){
    gpio_config_t ledConfig;
    ledConfig.pin_bit_mask = (1ULL << RED) | (1ULL << GREEN) | (1ULL << BLUE);
    ledConfig.mode = GPIO_MODE_OUTPUT;
    ledConfig.intr_type = GPIO_INTR_DISABLE;
    ledConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ledConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&ledConfig);
    
    gpio_set_intr_type(BUTTON, GPIO_INTR_HIGH_LEVEL);

    while(1){
        for(uint32_t i = 0; i < 3; i++){
            gpio_set_level(LEDS[i], 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }

        for(uint32_t i = 0; i < 3; i++){
            gpio_set_level(LEDS[i], 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }

    return;
}
