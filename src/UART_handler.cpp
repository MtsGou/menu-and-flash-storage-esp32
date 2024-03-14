#include <UART_handler.hpp>
#include <user_menu.hpp>

///////////////////////////////////////////////////////////////////////////////////////
/* ///////////////////////// UART COMMUNICATION FUNCTIONS ///////////////////////////*/

/**------------------------------------------------------------------------------------
  * @brief Generate contingency timestamp buffer and send serial
  * for monitor.
  *
  * @param  none
  * 
  * @retval void
  */
void timestamp(){

  // String local to print only
  String BUFFER_TIMESTAMP = "";

  unsigned int long millis_time = millis()/1000;

  if (millis_time < 60){

    /* If less than 1 min */
    BUFFER_TIMESTAMP += "[00:00:";
    if (millis_time < 10){
      /* Less than 10 sec */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) millis_time;
  }
  else if (millis_time >= 60 &&  millis_time < 3600){

    /* If the time is greater than 1 min and less than 1 hour */
    uint16_t minutes = millis_time/60;
    uint16_t seconds = millis_time%60;

    BUFFER_TIMESTAMP += "[00:";
    if (minutes < 10){
      /* Less than 10 min */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) minutes;
    BUFFER_TIMESTAMP += ":";
    if (seconds < 10){
      /* Less than 10 sec */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) seconds;
  }
  else if (millis_time >= 3600){

    /* Time greater than 1 hour */
    uint16_t hours = millis_time/3600;
    BUFFER_TIMESTAMP += "[";
    if (hours < 10){
      /* Less than 10 hours */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) hours;
    BUFFER_TIMESTAMP += ":";

    millis_time = millis_time%3600;
    uint16_t minutes = millis_time/60;
    uint16_t seconds = millis_time%60;

    if (minutes < 10){
      /* Less than 10 min */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) minutes;
    BUFFER_TIMESTAMP += ":";
    if (seconds < 10){
      /* Less than 10 sec */
      BUFFER_TIMESTAMP += "0";
    }
    BUFFER_TIMESTAMP += (String) seconds;
  }
  BUFFER_TIMESTAMP += "]: ";

  Serial.printf("\n\r%s", (char *)BUFFER_TIMESTAMP.c_str());
  /* Fim da funcao */
}

/**------------------------------------------------------------------------------------
  * @brief Wait if the user wants to use the menu. Read data received by UART.
  *
  *
  * @param  time_ms:  Waiting time in ms
  * 
  * @retval void
  */
void wait_for_serial(uint32_t time_ms){
  uint32_t wait = 775*time_ms;

  delay(500);
  Serial.println();
  Serial.println("Digite Shift + M para configurar");

  do {
    if (Serial.available()){
      Handle_user();
    }
  } while (wait--);
  Serial.println("Iniciando...");
}

/**------------------------------------------------------------------------------------
  * @brief Handle data received via UART from the user.
  * If 'M', enter the Main Menu.
  *
  *
  * @param none
  * 
  * @retval void
  */
void Handle_user() {
  char upcommingdata = Serial.read();
  if (upcommingdata == 'M') {
      Menu();
  }
}