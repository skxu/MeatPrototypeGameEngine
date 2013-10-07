#include "CAppStateIntro.h"
#include "CSoundBank.h"
#include "CAppStateManager.h"
#include "CApp.h"

#include "Define.h"

CAppStateIntro CAppStateIntro::Instance;
 
CAppStateIntro::CAppStateIntro() {
    Surf_Logo = NULL;
	Background = NULL;
	Done = false;
}
 
void CAppStateIntro::OnActivate() {
    // Load Simple Logo
    Surf_Logo = CSurface::OnLoad("splash3.png");
	Background = CSurface::OnLoad("background.png");
	
	splash.MaxFrames = 16;
	splash.FrameRate = 50;
	Time1 = SDL_GetTicks();
}
 
void CAppStateIntro::OnDeactivate() {
    if(Surf_Logo) {
        SDL_FreeSurface(Surf_Logo);
        Surf_Logo = NULL;
    }
	if(Background) {
		SDL_FreeSurface(Background);
		Background = NULL;
	}
}
 
void CAppStateIntro::OnLoop() {
	if(splash.GetCurrentFrame() <= 14 && Time1 + 2000 < SDL_GetTicks()) {
		splash.OnAnimate();
	} else if (splash.GetCurrentFrame() == 15 && Done == false) {
		StartTime = SDL_GetTicks();
		Done = true;
	}
	
    if(StartTime + 500 < SDL_GetTicks() && Done == true) {
        CAppStateManager::SetActiveAppState(APPSTATE_MENU);
		
    }
}
 
void CAppStateIntro::OnRender(SDL_Surface* Surf_Display) {
	if(Background) {
		CSurface::OnDraw(Surf_Display, Background, 0, 0, 0, 1, 1920, 1080);
	}

    if(Surf_Logo) {
		if (WWIDTH == 640) {
			CSurface::OnDraw(Surf_Display, Surf_Logo, 0, 0, 0, splash.GetCurrentFrame() * 480, 640, 480);
		}
		else {
       CSurface::OnDraw(Surf_Display, Surf_Logo, WWIDTH/4, WHEIGHT/3, 0, splash.GetCurrentFrame() * 480, 640, 480);
		}
    }
	
}
 
CAppStateIntro* CAppStateIntro::GetInstance() {
    return &Instance;
}