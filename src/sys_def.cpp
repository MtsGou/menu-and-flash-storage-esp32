#include <sys_def.h>

// BAUD RATE
const unsigned int long BAUD_RATE = 115200;

/* ================== GLOBAL VARIABLES ========================*/

// PARAMETERS
volatile uint8_t smallint_parameter = 100;
volatile uint32_t int_parameter = 500;
volatile float float_parameter = 20.5;
String string_parameter = "Test_menu";
uint8_t int_array_parameter[4] = {50, 100, 150, 200};

// Checksum divisor
String CHECKSUM_DIV = "*";
// Start byte
String start_byte = "@";
// End byte
String end_byte = "?";

// TIMEOUT
unsigned int long TimeOut = 3600;
