#ifndef _CMEATGEN_H_
    #define _CMEATGEN_H_

#include "CAppState.h"
 
#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CSurface.h"
#include "CMeat.h"
#include "CDrumstick.h"
#include "CPlayer.h"
#include "CNpc.h"
#include "CHam.h"

class CMeatGen {

public:
	CMeatGen();
	int rate;
	int oldTime;
	int runningTime;
	int meatCount;
	int meatType;
	int meatMax;
	int meatID;


private:
	bool MeatGen(int rate);
	char* getMeat();
	int getFrames();
	int getWidth();
	int getHeight();

public:
	virtual void OnActivation();
	virtual void OnLoop();



};
#endif
