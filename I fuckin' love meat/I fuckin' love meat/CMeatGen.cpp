#include "CMeatGen.h"
#include "CApp.h"
#include "CEvent.h"
#include "CMeat.h"

CMeatGen::CMeatGen() {
	meatType = 2;
	meatID = 10;
}

void CMeatGen::OnActivation() {
	oldTime = SDL_GetTicks();
	meatCount = 0;
	meatMax = 100;
	rate = 60;
}

bool CMeatGen::MeatGen(int rate) {
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


void CMeatGen::OnLoop() {
	if(MeatGen(rate) && meatCount < meatMax) {
		CMeat* meatPiece = new CMeat();
		if (meatPiece->OnLoad(getMeat(), getWidth(), getHeight(), getFrames()) == false) {
			return;
		}
		meatPiece->X = SDL_GetTicks()%600 + (rand()%200);
		meatPiece->Y = SDL_GetTicks()%300 +  (rand()%250);
		meatPiece->ID = 1337*(meatType) + meatID;
		meatID++;
		meatCount++;
		CEntity::EntityList.push_back(meatPiece);
	}
}


char* CMeatGen::getMeat() {
	int random = (rand() + SDL_GetTicks())%3;
	switch(meatType) {
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

int CMeatGen::getWidth() {
	switch(meatType) {
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

int CMeatGen::getHeight() {
	switch(meatType) {
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


int CMeatGen::getFrames() {
	return 8;
}

