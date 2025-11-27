#ifndef CREGISTER_H
#define CREGISTER_H

#include "CWindow.h"
#include "CLoginWin.h"
void CRegisterWin_init();

int registerUser(char account[], char password[], char repassword[], char role[]); 
#endif
