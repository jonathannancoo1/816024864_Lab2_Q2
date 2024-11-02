// 816024864 ADC
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/hw_timer.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "freertos/semphr.h"
#include "freertos/FreeRTOSConfig.h"
#include "ds3231.h"
#include <i2cdev.h>
#include "question_two.h"
#include "esp_timer.h"

// Timer callback function, triggered when the timer expires
void my_timer_callback(void* arg) {
    printf("Timer expired!\n");
    // Actions to perform when timer expires (keep actions brief)
}

// Function to initialize a microsecond timer
void init_microsecond_timer() {
    // Define timer configuration
    const esp_timer_create_args_t timer_args = {
        .callback = &my_timer_callback,          // Set the callback function
        .arg = NULL,                             // Argument passed to callback (optional)
        .dispatch_method = ESP_TIMER_TASK,       // Run in timer task
        .name = "microsecond_timer"              // Name the timer
    };

    // Create the timer with the specified configuration
    esp_timer_handle_t timer_handle;
    esp_err_t err = esp_timer_create(&timer_args, &timer_handle);
    if (err != ESP_OK) {
        printf("Failed to create timer: %s\n", esp_err_to_name(err));
        return;
    }

    // Start the timer with a 100,000-microsecond (0.1 second) interval
    err = esp_timer_start_periodic(timer_handle, 100000);
    if (err != ESP_OK) {
        printf("Failed to start timer: %s\n", esp_err_to_name(err));
        return;
    }

    printf("Microsecond timer started\n");
}

// Main application function
void app_main() {
    // Measure execution time of init_adc() function
    int32_t start_time = esp_timer_get_time(); // Get start time in microseconds
    init_adc();
    int32_t end_time = esp_timer_get_time();   // Get end time
    int32_t duration = end_time - start_time;  // Calculate elapsed time
    printf("Execution time: %d microseconds\n", duration);

    // Measure execution time of Read_value_from_ADC_pin_1() function
    start_time = esp_timer_get_time();
    Read_value_from_ADC_pin_1();
    end_time = esp_timer_get_time();
    duration = end_time - start_time;
    printf("Execution time: %d microseconds\n", duration);

    // Measure execution time of set_mux(1) function
    start_time = esp_timer_get_time();
    set_mux(1);
    end_time = esp_timer_get_time();
    duration = end_time - start_time;
    printf("Execution time: %d microseconds\n", duration);
}
