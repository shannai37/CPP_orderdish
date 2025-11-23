#ifndef CWATERWIN_H
#define CWATERWIN_H

#include "CWindow.h"

void CWaiterWin_init();
#include "CLoginWin.h"   // 因为要调用 CLoginWin_init()
#include "CStartWin.h"   // 因为要调用 CStartWin_init()
#endif
