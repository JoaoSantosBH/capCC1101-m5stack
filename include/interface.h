#pragma once
#include <Arduino.h>
#include <vector>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio();

/***************************************************************************************
** Function name: _post_setup_gpio()
** Location: main.cpp
** Description:   second stage gpio setup to make a few functions work
***************************************************************************************/
void _post_setup_gpio();

/***************************************************************************************
** Functions: adv_release_keyboard / adv_keyboard_restore / adv_flush_keyboard_events
** Location: boards/m5stack-cardputer/interface.cpp
** Description: ADV 3in1 G8/G9 multiplexing between TCA8418 I2C and NRF24 CE/SS.
**   adv_release_keyboard()      — flag NRF24 active; blocks I2C windows (pins stay OUTPUT)
**   adv_keyboard_restore()      — flag NRF24 done; re-enables I2C windows + flushes FIFO
**   adv_flush_keyboard_events() — drain TCA8418 FIFO + clear EscPress
**   No-ops on non-ADV profiles.
***************************************************************************************/
#ifdef TCA8418_I2C_ADDR
void adv_release_keyboard();
void adv_keyboard_restore();
void adv_flush_keyboard_events();
#endif

/***************************************************************************************
** Function name: _pre_storage_gpio()
** Location: main.cpp
** Description:   board gpio setup that must run after the first TFT use and before storage
***************************************************************************************/
void _pre_storage_gpio();

/***************************************************************************************
** Function name: getBattery()
** location: display.cpp
** Description:   Delivers the battery value from 1-100
***************************************************************************************/
int getBattery();


/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval);


/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void);

/*********************************************************************
** Function: pollEncoder
** location: interface.cpp (per board)
** Samples the rotary encoder A/B lines unconditionally, every task tick,
** decoupled from AnyKeyPress consumption -- mirrors how the Flipper
** port's encoder_poll() is never gated behind whether the previous
** input event was consumed. No-op on boards without HAS_ENCODER.
**********************************************************************/
void __attribute__((weak)) pollEncoder(void);


/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
**********************************************************************/
void powerOff();

/*********************************************************************
** Function: goToDeepSleep
** location: mykeyboard.cpp
** Puts the device into DeepSleep
**********************************************************************/
void goToDeepSleep();

/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to turnoff the device (name is odd btw)
**********************************************************************/
void checkReboot();

/***************************************************************************************
** Function name: isCharging()
** location: interface.cpp
** Description:   Determines if the device is charging
***************************************************************************************/
bool isCharging();
