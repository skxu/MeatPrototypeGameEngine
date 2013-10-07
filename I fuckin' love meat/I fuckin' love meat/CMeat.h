#ifndef _CMEAT_H_
	#define _CMEAT_H_
 
#include "CEntity.h"
 
class CMeat : public CEntity {

	enum {
    MEAT_TYPE_GENERIC = 0,
 
    MEAT_TYPE_STEAK = 1,
	MEAT_TYPE_DRUMSTICK = 2,
	MEAT_TYPE_HAM = 3
	};


    public:
        CMeat();
		
		int meat;
 
        bool OnLoad(char* File, int Width, int Height, int MaxFrames);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* Entity);
};
 
#endif