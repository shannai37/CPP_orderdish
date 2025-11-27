#ifndef CLOGINWIN_H
#define CLOGINWIN_H

#include "CWindow.h"
#include <string.h>
#include "CStartWin.h"  // 因为要调用 CStartWin_init()
#include "CAdminWin.h"      
#include "CManagerWin.h"   
#include "CWaiterWin.h"     
#include "document.h"       

void CLoginWin_init();
int loginCheck(char username[], char password[]) ; 
#endif
