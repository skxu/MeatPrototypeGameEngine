#include "CMonsterGen.h"
#include "CApp.h"
#include "CEvent.h"
#include "CMonster.h"

CMonsterGen::CMonsterGen() {
	monsterType = 2;
	meatID = 10;
}

void CMonsterGen::OnActivation() {
	oldTime = SDL_GetTicks();
	monsterCount = 0;
	monsterMax = 100;
	rate = 60;
}

bool CMonsterGen::MeatGen(int rate) {
	if (rate == 0) {
		return false;
	}
	runningTime = SDL_GetTicks() - oldTime; 
	int rateminute = 60000/rate;
	if (runningTime%rateminute == 0) {
		return true;
	}
	return false;
}


void CMonsterGen::OnLoop() {
	if(MeatGen(rate) && monsterCount < monsterMax) {
		CMonster* monsterPiece = new CMonster();
		if (monsterPiece->OnLoad("monster.png", 64, 64, 8) == false) {
			return;
		}
		monsterPiece->X = SDL_GetTicks()%624 + (rand()%500);
		monsterPiece->Y = SDL_GetTicks()%300 +  (rand()%400);
		monsterPiece->ID = 1337*(monsterType) + meatID;
		meatID++;
		monsterCount++;
		CEntity::EntityList.push_back(monsterPiece);
	}
}


char* CMonsterGen::getMeat() {
	int random = (rand() + SDL_GetTicks())%3;
	switch(monsterType) {
	case 0: {
		//meatType = 1;
		std::string l = "meat.png";
		char* p = new char[l.length() + 1];
		strcpy(p, l.c_str());
		return p;
			}
	case 1: {
		//meatType = 3;
		std::string l = "ham.png";
		char* p = new char[l.length() + 1];
		strcpy(p, l.c_str());
		return p;
			}
	case 2: {
		//meatType = 2;
		std::string l = "drumstick.png";
		char* p = new char[l.length() + 1];
		strcpy(p, l.c_str());
		return p;
			}
	default: {
		//meatType = 1;
	std::string l = "meat.png";
	char* p = new char[l.length() + 1];
		strcpy(p, l.c_str());
		return p;
			 }
	}
}

int CMonsterGen::getWidth() {
	switch(monsterType) {
	case 1: {
		return 64;
			}
	case 2: {
		return 64;
			}
	case 3: {
		return 64;
			}
	default: {
		return 64;
			 }
	}
}

int CMonsterGen::getHeight() {
	switch(monsterType) {
case 1: {
	return 64;
		}
case 2: {
	return 50;
		}
case 3: {
	return 64;
		}
default: {
	return 64;
		 }
	}
}


int CMonsterGen::getFrames() {
	return 8;
}

