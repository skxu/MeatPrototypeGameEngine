#include "CSurface.h"
#include "CSoundBank.h"
#include "CApp.h"

bool CApp::OnInit() {

	//Initialize everything SDL has
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	
	SDL_WM_SetCaption("I fuckin' love meat", NULL);

	//Initializing Surf_Display
	if ((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}


	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		return false;
	}

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);	

	CAppStateManager::SetActiveAppState(APPSTATE_INTRO);

	return true; 
}