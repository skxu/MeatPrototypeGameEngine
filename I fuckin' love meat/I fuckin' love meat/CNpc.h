#ifndef _CNPC_H_
    #define _CNPC_H_
 
#include "CEntity.h"
 
class CNpc : public CEntity {

    public:
        CNpc();
 
        bool OnLoad(char* File, int Width, int Height, int MaxFrames);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* Entity);

		void Walk(int x);

		bool isWalking;

		int StartTime;

		int WalkTime;

		int HP;

		void StopWalk();
};
 
#endif