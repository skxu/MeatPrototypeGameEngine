#ifndef __CAPPSTATEGAME_H__
    #define __CAPPSTATEGAME_H__
 
#include "CAppState.h"
 
#include "CArea.h"
#include "CArea2.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CSurface.h"
#include "CMeat.h"
#include "CDrumstick.h"
#include "CPlayer.h"
#include "CNpc.h"
#include "CHam.h"
#include "CMeatGen.h"
#include "CMonster.h"
#include "CMonsterGen.h"

class CAppStateGame : public CAppState {
    private:
        static CAppStateGame Instance;
		CMonster	Monster;
        CPlayer    Player;
        CNpc	    Npc1;
		CMeat	   Meat;
		CDrumstick	Drumstick;
		CHam Ham;
		CMeatGen MeatGenerator;
		CMonsterGen MonsterGenerator;
 
    private:
		bool fullscreen;

        CAppStateGame();
 
    public:
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
 
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		int splat;
 
    public:
        void OnActivate();
 
        void OnDeactivate();
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
    public:
        static CAppStateGame* GetInstance();
};
 
#endif