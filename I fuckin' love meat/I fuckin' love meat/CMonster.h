#ifndef _CMONSTER_H
    #define _CMONSTER_H_
 
#include "CEntity.h"
 
class CMonster : public CEntity {
    public:
        CMonster();
 
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

		bool Invincible;

		float InvincibleCounter;

		float InvincibleTime;

		float Bump;

		float BumpCounter;

		float BumpTime;

		void StopWalk();

		bool	InvalidTile;

		bool     PosValid(int NewX, int NewY);
 
        bool     PosValidTile(CTile* Tile);
 
        bool     PosValidEntity(CEntity* Entity, int NewX, int NewY);

		void CMonster::OnMove(float MoveX, float MoveY);
};
 
#endif