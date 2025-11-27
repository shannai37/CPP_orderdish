#ifndef CADMINWIN_PM
#define CADMINWIN_PM

#include "CWindow.h"
#include "CButton.h"
#include "CLabel.h"
#include "CUserManager.h"  
#include "CTool.h"
#include "CAdminWin.h" 
class CAdminWin_PM : public CWindow { 
private:
    int currentPage;
    int pageSize;
    int allPage;
	void drawTable();
public:
    CAdminWin_PM();   
    ~CAdminWin_PM();
    
    
    void show();
    virtual void handle();
};

#endif
