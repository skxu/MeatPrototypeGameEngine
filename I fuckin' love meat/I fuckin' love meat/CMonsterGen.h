#ifndef _CMONSTERGEN_H_
    #define _CMONSTERGEN_H_

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

class CMonsterGen {

public:
	CMonsterGen();
	int rate;
	int oldTime;
	int runningTime;
	int monsterCount;
	int monsterType;
	int monsterMax;
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
