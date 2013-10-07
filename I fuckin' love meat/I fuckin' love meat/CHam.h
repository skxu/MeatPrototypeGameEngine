#ifndef _CHam_H_
	#define _CHam_H_
 
#include "CEntity.h"
#include "CMeat.h"
 
class CHam : public CMeat {
    public:
        CHam();
 
        bool OnLoad(char* File, int Width, int Height, int MaxFrames);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* Entity);
};
 
#endif