#ifndef CManagerWIN_H
#define CManagerWIN_H

#include "CWindow.h"
#include "CLoginWin.h"   // 因为要调用 CLoginWin_init()
#include "CStartWin.h"   // 因为要调用 CStartWin_init()
#include "CWindowManager.h"
#include <string.h> 
void CManagerWin_init();

#endif
