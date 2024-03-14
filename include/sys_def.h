/* Packages and headers used */

#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <EEPROM.h>
#include <UART_handler.hpp>
#include <data_transmission.hpp>

#define address_EEPROM      0 // flash address to save and get data
#define EMPTY_VALUE         0xFF // Erase flash location

#ifdef address_EEPROM // for future aplications
#define EEPROM_SIZE address_EEPROM + 512 //512 bytes
#endif

// BAUD RATE
extern const unsigned int long BAUD_RATE;

/* ================================= typedef =================================*/
typedef unsigned char byte;
typedef unsigned int uint;

/* ================== GLOBAL VARIABLES ========================*/

// PARAMETERS
extern volatile uint8_t smallint_parameter;
extern volatile uint32_t int_parameter;
extern volatile float float_parameter;
extern String string_parameter;
extern uint8_t int_array_parameter[4];

// Checksum divisor
extern String CHECKSUM_DIV;
// Start byte
extern String start_byte;
// End byte
extern String end_byte;

//Timeout
extern unsigned int long TimeOut;