#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include "CSurface.h"
#include "CEvent.h"
#include "CCamera.h"
#include "Define.h"
#include "CAppStateManager.h"
#include "CFPS.h"
#include "CSoundBank.h"

class CApp : public CEvent {
private:
		bool Running;

		


public:
		SDL_Surface* Surf_Display;
		CApp();
		int OnExecute();

public:
		
		bool OnInit();
		void OnEvent(SDL_Event* Event);
		void OnExit();
		void OnLoop();
		void OnRender();
		void OnCleanup();





};
#endif