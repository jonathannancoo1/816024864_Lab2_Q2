// 816024864 ADC - Program for configuring and reading ADC via I2C protocol

#include "question_two.h"  // Include custom header file for non-volatile storage (NVS) functions

// I2C configuration structure for communication with the ADC
i2c_config_t pinconfig = {
    // Set mode to master
    .mode = I2C_MODE_MASTER,

    // Disable pull-up resistors on SDA and SCL lines
    .sda_pullup_en = GPIO_PULLUP_DISABLE,
    .scl_pullup_en = GPIO_PULLUP_DISABLE,

    // Set SCL (Serial Clock Line) to GPIO pin 0
    .scl_io_num = GPIO_NUM_0,

    // Set SDA (Serial Data Line) to GPIO pin 2
    .sda_io_num = GPIO_NUM_2,

    // Set clock stretch timing (1000 ticks)
    .clk_stretch_tick = 1000
};

// Initialize time structure for setting initial time
struct tm Time = {
    .tm_year = 116, // Year since 1900 (2016 - 1900)
    .tm_mon  = 9,   // Month (0-based)
    .tm_mday = 9,   // Day of the month
    .tm_hour = 13,  // Hour (24-hour format)
    .tm_min  = 50,  // Minutes
    .tm_sec  = 10   // Seconds
};

// Function to initialize the ADC using I2C protocol
int init_adc() {
    i2cdev_init();  // Initialize the I2C device driver

    // Create and configure I2C device descriptor
    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));  // Clear device descriptor memory

    dev.port = I2C_NUM_0;                // Assign I2C port
    dev.cfg = pinconfig;                 // Set I2C configuration
    dev.addr = ADS111X_ADDR_GND;         // Set ADC address on I2C bus

    // Initialize ADC descriptor with specific address and pins
    ads111x_init_desc(&dev, ADS111X_ADDR_GND, I2C_NUM_0, GPIO_NUM_2, GPIO_NUM_0);
    printf("hello world");

    return 0; // Successful initialization
}

// Function to read value from ADC pin 1
void Read_value_from_ADC_pin_1() {
    i2cdev_init();  // Initialize the I2C device driver

    // Define I2C device descriptor
    i2c_dev_t dev;
    dev.port = I2C_NUM_0;                // Assign I2C port
    dev.cfg = pinconfig;                 // Set I2C configuration
    dev.addr = ADS111X_ADDR_GND;         // Set ADC address on I2C bus

    // Initialize ADC descriptor with specific address and pins
    ads111x_init_desc(&dev, ADS111X_ADDR_GND, I2C_NUM_0, GPIO_NUM_2, GPIO_NUM_0);

    int16_t value;
    // Retrieve ADC value and print if successful
    if (ads111x_get_value(&dev, &value) == ESP_OK) {
        printf("Success %d", value);
    }
    printf("Done Conversion \n");
}

// Function to set multiplexer (MUX) configuration on the ADC based on input
void set_mux(int a) {
    // Define I2C device descriptor
    i2c_dev_t dev;
    dev.port = I2C_NUM_0;                // Assign I2C port
    dev.cfg = pinconfig;                 // Set I2C configuration
    dev.addr = ADS111X_ADDR_GND;         // Set ADC address on I2C bus

    // Initialize ADC descriptor with specific address and pins
    ads111x_init_desc(&dev, ADS111X_ADDR_GND, I2C_NUM_0, GPIO_NUM_2, GPIO_NUM_0);

    // Define multiplexer selection based on input parameter `a`
    ads111x_mux_t mux;
    if (a == 1) {
        mux = ADS111X_MUX_0_1;           // Configure MUX to read differential between channel 0 and 1
    } else if (a == 2) {
        mux = ADS111X_MUX_0_3;           // Configure MUX for channels 0 and 3
    } else if (a == 3) {
        mux = ADS111X_MUX_1_3;           // Configure MUX for channels 1 and 3
    } else if (a == 4) {
        mux = ADS111X_MUX_2_3;           // Configure MUX for channels 2 and 3
    } else if (a == 5) {
        mux = ADS111X_MUX_0_GND;         // Single-ended read on channel 0 to ground
    } else if (a == 6) {
        mux = ADS111X_MUX_1_GND;         // Single-ended read on channel 1 to ground
    } else if (a == 7) {
        mux = ADS111X_MUX_2_GND;         // Single-ended read on channel 2 to ground
    } else if (a == 8) {
        mux = ADS111X_MUX_3_GND;         // Single-ended read on channel 3 to ground
    } else {
        mux = ADS111X_MUX_3_GND;         // Default to channel 3 to ground if input is invalid
        printf("Invalid input\n");       // Print error for invalid input
    }

    // Apply the MUX configuration to the ADC
    ads111x_set_input_mux(&dev, mux);
}
