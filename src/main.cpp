/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Matheus Gouveia.
  * @brief   Menu application to the user and EEPROM storage application 
  *          for ESP32 using arduino framework.
  *
  ******************************************************************************
  *
  *  Created on: 11/03/2024
  */

#include <sys_def.h>
#include <user_menu.hpp>

/* SETUP */
void setup()
{
  // INIT EEPROM 
  EEPROM.begin(EEPROM_SIZE);

  // INIT UART COMMUNICATION
  Serial.begin(BAUD_RATE);

  // CHECK EEPROM FOR SAVED DATA AND INIT PARAMETERS
  Set_initial_config();

}

void loop()
{
  // CHECK FOR USER REQUEST
  wait_for_serial(28000);
}


/**********************************************************************************************
  Outubro, 2021.
  Codigo para implementacao do SEMA (parte ESP32) do caminhao autonomo
  Os direitos autorais devem ser incluidos em todas as copias ou partes substanciais do Software.
  Author:  Gouveia, Matheus.

***********************************************************************************************/
