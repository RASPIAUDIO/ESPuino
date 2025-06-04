// clang-format off

#ifndef __ESPUINO_SETTINGS_ESPA1S_H__
#define __ESPUINO_SETTINGS_ESPA1S_H__
    #include "Arduino.h"

    //######################### INFOS ####################################
    /* This is a develboard-specific config-file for *AI Tinker ESP32-A1S-AudioKit*. It's highly customized and almost certainly
    not suitable for a different develboard.
    Has a lot of stuff already onboard but needs some soldering rework as there are not all GPIOs exposed.
    PCB: Not necessary.
    Infos: https://github.com/Ai-Thinker-Open/ESP32-A1S-AudioKit
           https://forum.espuino.de/t/esp32-audio-kit-esp32-a1s/106
    Status: tested by kkloesner with RC522-I2C
    */


    #define NUM_INDICATOR_LEDS		1          	// number of Neopixel LEDs (formerly NUM_LEDS)
    #define NEOPIXEL_PIN                22              // Pin for the RGB LED on Muse Luxe
    #define NUMPIXELS                   1               // Muse Luxe has 1 RGB LED
	//#define RFID_READER_TYPE_MFRC522_I2C  // use MFRC522 via I2C
	#undef USEROTARY_ENABLE                // If rotary-encoder is used (don't forget to review WAKEUP_BUTTON if you disable this feature!)
    #undef IR_CONTROL_ENABLE

    //################## GPIO-configuration ##############################
    // SD
    // Make sure to enable SD_MMC_1BIT_MODE! GPIOs 2, 14, 15 are used therefore. Make sure to not assign them elsewhere!

    // RFID (via SPI; currently not supported!)
    #if defined(RFID_READER_TYPE_MFRC522_SPI)
        #define RST_PIN                         99          // Not necessary but has to be set anyway; so let's use a dummy-number
        #define RFID_CS                         15          // GPIO for chip select (RFID)
        #define RFID_MOSI                       13          // GPIO for master out slave in (RFID)
        #define RFID_MISO                       16          // GPIO for master in slave out (RFID)
        #define RFID_SCK                        14          // GPIO for clock-signal (RFID)
    #endif

    // RFID (via I2C)
    #if defined(RFID_READER_TYPE_MFRC522_I2C)
        #define MFRC522_RST_PIN                 99          // needed for initialisation -> MTDI on JTAG header
    #endif

    // I2C-configuration (necessary for RC522 [only via i2c - not spi!] or port-expander)
    #ifdef I2C_2_ENABLE
        #define ext_IIC_CLK                 23          // i2c-SCL (clock) [14 pin-header]
        #define ext_IIC_DATA                18          // i2c-SDA (data) [14 pin-header]
    #endif

    // bluetooth support seems to be too large for this HAL -> disable it for now
    // fix linker error "region 'iram0_0_seg' overflowed by xxx bytes"
    // https://forum.espuino.de/t/aktueller-stand-esp32-arduino-2/1389/218
    #ifdef BLUETOOTH_ENABLE
        #undef BLUETOOTH_ENABLE
    #endif

    // I2S (DAC)
    #define I2S_DOUT 26
    #define I2S_BCLK 5
    #define I2S_LRC  25

    // I2C (AC101)
    #define IIC_CLK                         23          // internal
    #define IIC_DATA                        18          // internal

    // Amp enable
    #define GPIO_PA_EN                      21          // internal


    // Control-buttons (set to 99 to DISABLE; 0->39 for GPIO; 100->115 for port-expander)
    #define NEXT_BUTTON                     32      // assign Volume Down to button 0
    #define PREVIOUS_BUTTON                 19      // assign Volume Up to button 1
    #define PAUSEPLAY_BUTTON                12      // assign Pause/Play to button 2
    #define ROTARYENCODER_BUTTON            99          // (set to 99 to disable; 0->39 for GPIO; 100->115 for port-expander)
    #define BUTTON_4                        99          // Button 4: unnamed optional button
    #define BUTTON_5                        99          // Button 5: unnamed optional button

    //#define BUTTONS_LED                   114         // Powers the LEDs of the buttons. Make sure the current consumed by the LEDs can be handled by the used GPIO



    // Wake-up button => this also is the interrupt-pin if port-expander is enabled!
    // Please note: only RTC-GPIOs (0, 4, 12, 13, 14, 15, 25, 26, 27, 32, 33, 34, 35, 36, 39, 99) can be used! Set to 99 to DISABLE.
    // Please note #2: this button can be used as interrupt-pin for port-expander. If so, all pins connected to port-expander can wake up ESPuino.
    #define WAKEUP_BUTTON                   PAUSEPLAY_BUTTON // Defines the button that is used to wake up ESPuino from deepsleep.

    // Power-control
    #define POWER                           19          // GPIO used to drive transistor-circuit, that switches off peripheral devices while ESP32-deepsleep
    #ifdef POWER
        //#define INVERT_POWER                          // If enabled, use inverted logic for POWER circuit, that means peripherals are turned off by writing HIGH
    #endif

    // (optional) Neopixel
    #if defined(NEOPIXEL_ENABLE)
        #define LED_PIN                     22          // GPIO for Neopixel-signaling
    #endif

    // (optinal) Headphone-detection
    #ifdef HEADPHONE_ADJUST_ENABLE
        //#define DETECT_HP_ON_HIGH                     // Per default headphones are supposed to be connected if HT_DETECT is LOW. DETECT_HP_ON_HIGH will change this behaviour to HIGH.
        #define HP_DETECT                   27          // GPIO that detects, if there's a plug in the headphone jack or not
    #endif

    // (optional) Monitoring of battery-voltage via ADC
    #ifdef MEASURE_BATTERY_VOLTAGE
        #define VOLTAGE_READ_PIN            34          // GPIO used to monitor battery-voltage. Change to 35 if you're using Lolin D32 or Lolin D32 pro as it's hard-wired there!
        constexpr float referenceVoltage = 3.30;                  // Voltage between 3.3V and GND-pin at the develboard in battery-mode (disconnect USB!)
        constexpr float offsetVoltage = 0.1;                      // If voltage measured by ESP isn't 100% accurate, you can add an correction-value here

        // Battery Level Thresholds for Muse Luxe when using ADC
        #define BATTERY_FULL 75
        #define BATTERY_LOW  25
        #define BATTERY_PIN  VOLTAGE_READ_PIN        // legacy ADC pin (not the I2C BMS mode)
    #endif

    // (optional) For measuring battery-voltage a voltage-divider is necessary. Their values need to be configured here.
    #ifdef MEASURE_BATTERY_VOLTAGE
        constexpr uint16_t rdiv1 = 129;                              // Rdiv1 of voltage-divider (kOhms) (measure exact value with multimeter!)
        constexpr uint16_t rdiv2 = 389;                              // Rdiv2 of voltage-divider (kOhms) (measure exact value with multimeter!) => used to measure voltage via ADC!
    #endif

 
#endif
