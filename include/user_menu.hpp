#include <sys_def.h>

///////////////////////////////////////////////////////////////////////////////////////
/* /////////////// USER MENU PROTOTYPES FOR PARAMETER CONFIGURATION /////////////////*/

void reset_data(void);
void Set_initial_config(void);
void Print_menu(void);
void Print_parameters(void);
void Menu(void);
float Change_parameters_float(float var);
int Change_parameters_int(int variable);
String Change_parameters_char(String enter);
int32_t Change_parameters_simple(int ID, int STANDARD);
void user_interface(int ident);
String BufferToSave(void);