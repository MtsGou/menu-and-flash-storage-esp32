#include <data_transmission.hpp>
#include <user_menu.hpp>

///////////////////////////////////////////////////////////////////////////////////////
/* ////////////////// FUNCOES DE TRANSMISSAO DE DADOS ///////////////////////////////*/

/**------------------------------------------------------------------------------------
  * @brief Calculate 8-bit checksum of the data.
  *
  * @OBS Returns hexadecimal value in Upper Case.
  *
  * @param BUFFER:  Data [string].
  * 
  * @retval String checksum.
  */
String Checksum(String BUFFER)
{
  int checksum_arrived = 0;
  for (int index = 0; index < BUFFER.length(); index++)
  {
    checksum_arrived = checksum_arrived ^ BUFFER[index];
  }
  String checksum = String(checksum_arrived, HEX);
  checksum.toUpperCase();
  return checksum;
}

/**------------------------------------------------------------------------------------
  * @brief Captures data between dividers or separators.
  *
  * @OBS divisor must be char
  *
  * @param data:        Data [string]
  * @param separator:   Divisor
  * @param index:       Index to capture
  * 
  * @retval String data
  */
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


/**------------------------------------------------------------------------------------
  * @brief CRC 8 bits of the message in bit string.
  *
  * @OBS CRC divisor polynomial [100110001]. Returns CRC result in hexadecimal.
  *
  * @param BitString: string of bits of data.
  * 
  * @retval String Res
  */
String CRC(String BitString){
   String Res; // store CRC result
   char CRC[8];
   int  i;
   char DoInvert;
   char *getbitstring = (char *) BitString.c_str();
   char res[9];
   
   for (i=0; i<8; ++i)  CRC[i] = 0;
   
   for (i=0; i<strlen(getbitstring); ++i)
      {
      DoInvert = ('1'==getbitstring[i]) ^ CRC[7]; // XOR operation

      CRC[7] = CRC[6];
      CRC[6] = CRC[5];
      CRC[5] = CRC[4] ^ DoInvert;
      CRC[4] = CRC[3] ^ DoInvert;
      CRC[3] = CRC[2];
      CRC[2] = CRC[1];
      CRC[1] = CRC[0];
      CRC[0] = DoInvert;
      }
      
   for (i=0; i<8; ++i)  res[7-i] = CRC[i] ? '1' : '0'; // convert bin to ASCII
   res[8] = 0; // end of string

   Res = String(res);
   return Res;
}

/**------------------------------------------------------------------------------------
  * @brief Receives a binary string and returns the corresponding integer.
  *
  * @param str: string of bits from data.
  * 
  * @retval int result
  */
int strbin_to_dec(String str) {
    uint result = 0;
    for (int i = str.length() - 1, j = 0; i >= 0; i--, j++) {
       //assume ASCII coding
        byte k = str[i] - '0'; 
        k <<= j;
        result += k;
    }
    return result;
}

/**------------------------------------------------------------------------------------
  * @brief Captures a char* string and returns the corresponding string
  * in binary (ASCII).
  *
  * @param bitString: String ASCII
  * 
  * @retval String Resultado
  */
String getBitsFromString(char* bitString){

    String Resultado;

    char *ptr = bitString;
    int i;

    for(; *ptr != 0; ++ptr)
    {

        /* perform bitwise AND for every bit of the character */
        for(i = 7; i >= 0; --i) 
            (*ptr & 1 << i) ? Resultado += "1": Resultado += "0";
            

    }
    return Resultado;
}