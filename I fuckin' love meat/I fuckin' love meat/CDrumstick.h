#ifndef _CDrumStick_H_
	#define _CDrumStick_H_
 
#include "CEntity.h"
#include "CMeat.h"
 
class CDrumstick : public CMeat {
    public:
        CDrumstick();
 
        bool OnLoad(char* File, int Width, int Height, int MaxFrames);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* Entity);
};
 
#endif