#include <user_menu.hpp>

///////////////////////////////////////////////////////////////////////////////////////
/* /////////////// USER MENU FOR PARAMETERS CONFIGURATION////////////////////////////*/

/**------------------------------------------------------------------------------------
  * @brief Resets EEPROM data.
  *
  * @OBS After resetting, the microcontroller must be reset or turned off
  * to return to default values.
  * 
  * @param none
  * 
  * @retval void
  */
void reset_data(){
   for (int i = 0; i < EEPROM_SIZE; i++){
    EEPROM.write(i, EMPTY_VALUE);
   }
   EEPROM.commit();
   Serial.println("EEPROM erased.");
}

/**------------------------------------------------------------------------------------
  * @brief Check if there is data saved in EEPROM memory
  * If there is, check that there is no corrupted data
  * If data is safe, captures and initializes it
  * with data saved in memory.
  *
  * @OBS Only during initialization
  * 
  * @param none
  * 
  * @retval void
  */
void Set_initial_config() {

  String getArray;

  /* Get string saved in flash */
  String getEEPROM = EEPROM.readString(address_EEPROM);

  if (getEEPROM.length() > 0){

    Serial.println("DADOS ARMAZENADOS NA MEMORIA: ");
    Serial.print(getEEPROM);

    /* If there is data in flash, get CRC */
    String data_mem = getEEPROM.substring(0,getEEPROM.indexOf(CHECKSUM_DIV));
    String CRC_arrived = getEEPROM.substring(getEEPROM.indexOf(CHECKSUM_DIV), getEEPROM.indexOf('$'));
    CRC_arrived.remove(0, 1); 
    char* DataEEPROM = (char *)data_mem.c_str();
    String CRC_str = CRC(getBitsFromString(DataEEPROM));
    uint8_t CRC_int = strbin_to_dec(CRC_str);
    String CRC_verify = String(CRC_int, HEX);
    CRC_verify.toUpperCase();

    /* Verify CRC */
    if (CRC_arrived.equals(CRC_verify)){
      /* If CRC checks, get data and configure parameters */

      string_parameter = getValue(data_mem, ',', 0);
      getArray = getValue(data_mem, ',', 1);
      TimeOut = 3600*(getValue(data_mem,',',2).toFloat());
      int_parameter = getValue(data_mem,',',3).toInt();
      smallint_parameter = getValue(data_mem,',',4).toInt();
      float_parameter = getValue(data_mem,',',5).toFloat();

      int_array_parameter[0] = getValue(getArray,'.',0).toInt();
      int_array_parameter[1] = getValue(getArray,'.',1).toInt();
      int_array_parameter[2] = getValue(getArray,'.',2).toInt();
      int_array_parameter[3] = getValue(getArray,'.',3).toInt();
    }
    
  }

}

/**------------------------------------------------------------------------------------
  * @brief Print menu.
  * 
  * @param none
  * 
  * @retval void
  */
void Print_menu() {
  Serial.println("\f");
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("\n\rMENU\r\n");
  Serial.print("\n\rSELECT       Shift + key\n\r");
  Serial.print("\n\rSTRING PARAMETER            A");
  Serial.print("\n\rTIMEOUT                     B");
  Serial.print("\n\rINT PARAMETER               C");
  Serial.print("\n\rSMALL INT PARAMETER         D");
  Serial.print("\n\rFLOAT PARAMETER             E");
  Serial.print("\n\rINT ARRAY PARAMETER         F");
  Serial.print("\n\rSEE SAVED PARAMETERS        G");
  Serial.print("\n\rSAVE DATA IN FLASH          S");
  Serial.print("\n\rERASE FLASH MEMORY          R");
  Serial.println("\n\rLEAVE MENU                X");
}

/**------------------------------------------------------------------------------------
  * @brief Print current parameters saved.
  * 
  * @param none
  * 
  * @retval void
  */
void Print_parameters() {
  Serial.print("\r\nSTRING PARAMETER:    ");
  Serial.print(string_parameter);
  Serial.print("\r\nTIMEOUT: ");
  Serial.print((float)TimeOut/3600);
  Serial.print("\r\nINT PARAMETER: ");
  Serial.print(int_parameter,3);
  Serial.print("\r\nSMALL INT PARAMETER: ");
  Serial.print(smallint_parameter,3);
  Serial.print("\r\nFLOAT PARAMETER: ");
  Serial.print(float_parameter,3);
  Serial.print("\r\nINT ARRAY PARAMETER: ");
  Serial.printf("%d.%d.%d.%d", int_array_parameter[0],int_array_parameter[1], 
                               int_array_parameter[2], int_array_parameter[3]);
  Serial.println();
}

/**------------------------------------------------------------------------------------
  * @brief Main loop for user menu.
  *
  * 
  * @param none
  * 
  * @retval void
  */
void Menu() {

  Print_menu();

  while (1) {
    if (Serial.available()) {
      char userdata = Serial.read();
      if (userdata == 'A') {
        Serial.println();
        Serial.println("\r\nCurrent STRING PARAMETER: ");
        Serial.println(string_parameter);
        Serial.println("Write new STRING PARAMETER: (x -> cancel) ");
        string_parameter = Change_parameters_char(string_parameter);
        Print_menu();
        Serial.println("\r\nSTRING PARAMETER saved: ");
        Serial.print(string_parameter);
      }
      else if (userdata == 'B') {
        user_interface(1);
      }
      else if (userdata == 'C') {
        user_interface(2);
      }
      else if (userdata == 'D') {
        user_interface(3);
      }
      else if (userdata == 'E') {
        user_interface(4);
      }
      else if (userdata == 'F') {
        user_interface(5);
      }
      else if (userdata == 'G') {
        Print_parameters();
      }
      else if (userdata == 'S') {
        EEPROM.writeString(address_EEPROM, BufferToSave());
        EEPROM.commit();
        Serial.println();
        Serial.println("\rSaved in flash.");
      }
      else if (userdata == 'R') {
        reset_data();
      }
      else if (userdata == 'X') {
        break;
      }
    }
  }
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


/**------------------------------------------------------------------------------------
  * @brief Edit float parameters interactively.
  *
  * 
  * @param var: float parameter to edit.
  * 
  * @retval float var;
  */
float Change_parameters_float(float var) {

  /* Digit to edit */
  int house = 3;

  /* Decimal digit */ 
  float decimal = 0.001;

  /* Std value, case cancel */
  float Stan = var;

  while (1)
  {
    if (Serial.available()) {
      char command = Serial.read();
      if (command == '\n' || command == '\r') {}
      else {
        if (command == 'x' || command == 'X') {
          /* Cancel */
          Print_menu();
          var = Stan;
          break;
        }

        if (command == 'S') {
          /* Save */
          Print_menu();
          break;
        }

        if (command == 'd') {
          house++;
          if (house > 3) {
            house = 3;
          }
        }
        else if (command == 'a') {
          house--;
          if (house < 1) {
            house = 1;
          }
        }

        switch (house) {
          case 1:
            decimal = 0.1;
            break;

          case 2:
            decimal = 0.01;
            break;

          case 3:
            decimal = 0.001;
            break;
        }

        if (command == 'w') {
          var += decimal;
        }
        else if (command == 's') {
          var -= decimal;
        }


        if (var > 1) {
          var = 1;
        }
        else if (var < 0) {
          var = 0;
        }
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.println(var, 3);
      }
    }
  }
  return var;
}

/**------------------------------------------------------------------------------------
  * @brief Edit integer parameter interactively.
  *
  * 
  * @param variable: integer parameter to edit.
  * 
  * @retval int variable;
  */
int Change_parameters_int(int variable) {

  /* Digit to edit */
  int house = 1;

  /* Decimal digit */
  int decimal = 1;

  /* Std value to return case cancel */
  int Standard = variable;

  while (1)
  {
    if (Serial.available()) {
      char command = Serial.read();

      if (command == '\n' || command == '\r') {}

      else {

        if (command == 'x' || command == 'X') {
          /* Cancel */
          Print_menu();
          variable = Standard;
          break;
        }

        if (command == 'S') {
          /* Save */
          Print_menu();
          break;
        }

        if (command == 'a') {
          house--;
          if (house < 1) {
            house = 1;
          }
        }
        else if (command == 'd') {
          house++;
          if (house > 2) {
            house = 2;
          }
        }

        switch (house) {
          case 1:
            decimal = 10;
            break;

          case 2:
            decimal = 1;
            break;
        }

        if (command == 'w') {
          variable += decimal;
        }
        else if (command == 's') {
          variable -= decimal;
        }


        if (variable > 100) {
          variable = 100;
        }
        else if (variable < 0) {
          variable = 0;
        }
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.println(variable);
      }
    }
  }
  return variable;
}

/**------------------------------------------------------------------------------------
  * @brief Capture string wrote by user and save inplace of string parameter.
  *
  * 
  * @param enter: String to edit.
  * 
  * @retval String digit;
  */
String Change_parameters_char(String enter) {
  String digit = "";
  while (1) {
    if (Serial.available()) {
      digit = Serial.readStringUntil('\n');
      if (digit.equals("x") || digit.equals("X")) {
        /* Cancel */
        digit = enter;
        break;
      }
      if (!digit.length()){
      }
      else{
        break;
      }
    }
  }
  return digit;
}

/**------------------------------------------------------------------------------------
  * @brief Edit numeric parameter in a simpler way, not as interactively.
  *
  * 
  * @param ID:        Identify case. 0 -> TimeOut config. 1-> 0 - 255 float.
  * @param STANDARD:  Integer to edit. 
  * 
  * @retval (int) multiplier_output * reading
  */
int32_t Change_parameters_simple(int ID, int STANDARD) {
  String getuserdata = "";
  float reading;
  float min, max, multiplier_output;

  switch (ID) {
    case 0:
    /* Case config timeout */
      min = 0.01;
      max = 100;
      multiplier_output = 3600;
      break;

    case 1:
    /* Case 0 - 255 */
      min = 0;
      max = 255;
      multiplier_output = 1;
      break;
  }

  while (1) {
    if (Serial.available()) {
      getuserdata = "";
      getuserdata = Serial.readStringUntil('\n');
      reading = getuserdata.toFloat();

      if (getuserdata.equals("X") || getuserdata.equals("x")) {
        /* Cancel */
        if (!ID) {
          /* Return to menu */
          Print_menu();
          reading = STANDARD / 3600;
        }
        else {
          /* */
          reading = -1;
        }
        break;
      }

      if ((reading < min || reading > max)&&(reading != 0)) {
        /* Invalid input. Try again. */
        Serial.println();
        Serial.println("\r Invalid. Write again.");
      }
      else if ((ID && (getuserdata.length() > 0)) || (!ID && reading != 0)){
        /* Save */
        Serial.println();
        Serial.println("\rSaved parameter:");
        if (ID) {
          Serial.print((int)reading);
          Serial.println();
        }
        else {
          Serial.print(reading);
          Serial.println();
          Print_menu();
        }
        break;
      }
    }

  }
  return (int) multiplier_output * reading;
}

/**------------------------------------------------------------------------------------
  * @brief Secondary layer of the menu, which defines what to do
  * in each case of the Main Menu.
  * 
  * @param ident:   Case from the main menu.
  * 
  * @retval void
  */
void user_interface(int ident) {

  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

  if (ident == 1)
  {
    Serial.println("Standard = 1 [h].");
    float TIME = (float)TimeOut / (float)3600;
    Serial.println("\n\rCurrent value: ");
    Serial.print(TIME);
    Serial.println("\r\nDigit a value between 0.01 and 100 [hours] in X.XX format");
    TimeOut = Change_parameters_simple(0, TimeOut);
    Serial.println("\r\nSaved:");
    Serial.print((float)(TimeOut / (float)3600));
  }

  else if (ident == 2)
  {
    Serial.println("\rChoose int number (w -> UP, s-> DOWN, a-> LEFT, d-> RIGHT)");
    Serial.println(int_parameter);
    int_parameter = Change_parameters_int(int_parameter);
    Serial.println("\r\nSaved: INT PARAMETER = ");
    Serial.print(int_parameter);
  }

  else if (ident == 3)
  {
    Serial.println("\rChoose int number 0-255(w -> UP, s-> DOWN, a-> LEFT, d-> RIGHT)");
    Serial.println(smallint_parameter);
    smallint_parameter = Change_parameters_int(smallint_parameter);
    Serial.println("\r\nSaved: SMALL INT PARAMETER = ");
    Serial.print(smallint_parameter);
  }

  else if (ident == 4)
  {
    Serial.println("\rChoose float number (w -> UP, s-> DOWN, a-> LEFT, d-> RIGHT)");
    Serial.println(float_parameter, 3);
    float_parameter = Change_parameters_float(float_parameter);
    Serial.println("\r\nSaved: FLOAT PARAMETER = ");
    Serial.print(float_parameter, 3);
  }

  else if (ident == 5)
  {
    Serial.println("\rChoose int number 0-255(w -> UP, s-> DOWN, a-> LEFT, d-> RIGHT)");
    Serial.println("\r\nPress Shift + S to save");

    for (int index = 0; index < 4; index++)
    {
      int feedback = 1;
      Serial.println();
      Serial.printf("%d digit (0 - 255):", index + 1);
      feedback = Change_parameters_simple(0, int_array_parameter[index]);
      if (feedback < 0)
      {
        break;
      }
      int_array_parameter[index] = feedback;
    }
  }
}

/**------------------------------------------------------------------------------------
  * @brief Fill buffer to save in EEPROM (with CRC).
  * 
  * @param none
  * 
  * @retval String BUFFER_EEPROM
  */
String BufferToSave(){

  String BUFFER_EEPROM = "";
  BUFFER_EEPROM += string_parameter;
  BUFFER_EEPROM += ",";
  BUFFER_EEPROM += (String)int_array_parameter[0];
  BUFFER_EEPROM += ".";
  BUFFER_EEPROM += (String)int_array_parameter[1];
  BUFFER_EEPROM += ".";
  BUFFER_EEPROM += (String)int_array_parameter[2];
  BUFFER_EEPROM += ".";
  BUFFER_EEPROM += (String)int_array_parameter[3];
  BUFFER_EEPROM += ",";
  float auxerase = (float)TimeOut/3600;
  BUFFER_EEPROM += (String)auxerase;
  BUFFER_EEPROM += ",";
  BUFFER_EEPROM += (String)int_parameter;
  BUFFER_EEPROM += ",";
  BUFFER_EEPROM += (String)smallint_parameter;
  BUFFER_EEPROM += ",";
  BUFFER_EEPROM += (String)float_parameter;

  String CRC_put = CRC(getBitsFromString((char*) BUFFER_EEPROM.c_str()));
  uint8_t CRC_put_int = strbin_to_dec(CRC_put);
  String CRC_put_STR = String(CRC_put_int, HEX);
  CRC_put_STR.toUpperCase();

  BUFFER_EEPROM += "*";
  BUFFER_EEPROM += CRC_put_STR;
  BUFFER_EEPROM += "$";

  return BUFFER_EEPROM;
}