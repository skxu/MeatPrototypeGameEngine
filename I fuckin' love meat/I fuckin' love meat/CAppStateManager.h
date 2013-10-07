#ifndef __CAPPSTATEMANAGER_H__
    #define __CAPPSTATEMANAGER_H__
 
#include "CAppState.h"
 
enum {
    
    APPSTATE_NONE,
    APPSTATE_INTRO,
	APPSTATE_MENU,
    APPSTATE_GAME
};
 
class CAppStateManager {
    private:
        static CAppState* ActiveAppState;
 
    public:
        static void OnEvent(SDL_Event* Event);
 
        static void OnLoop();
 
        static void OnRender(SDL_Surface* Surf_Display);
 
    public:
        static void SetActiveAppState(int AppStateID);
 
        static CAppState* GetActiveAppState();
};
 
#endif