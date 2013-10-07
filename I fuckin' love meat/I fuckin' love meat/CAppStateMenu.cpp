#include "CAppStateMenu.h"
 
#include "CAppStateManager.h"
#include "Define.h"
#include "CApp.h"
#include "CSoundBank.h"

CAppStateMenu CAppStateMenu::Instance;
 
CAppStateMenu::CAppStateMenu() {
    Surf_Logo = NULL;
	Background = NULL;
	Play = NULL;
	inBox = false;
}
 
void CAppStateMenu::OnActivate() {
    // Load Simple Logo
    Surf_Logo = CSurface::OnLoad("splash3.png");
	Background = CSurface::OnLoad("background.png");
	Play = CSurface::OnLoad("play.png");
	Soundtrack = CSoundBank::SoundControl.OnLoad("Soliloquy.ogg");
	//splat = CSoundBank::SoundControl.OnLoad("splat.ogg");
	splash.MaxFrames = 16;
	splash.CurrentFrame = 15;
	StartTime = SDL_GetTicks();
	menu.MaxFrames = 4;
	menu.CurrentFrame = 0;
	inBox = false;
	click = false;
	CSoundBank::SoundControl.Play(Soundtrack, -1);

}
 
void CAppStateMenu::OnDeactivate() {
    if(Surf_Logo) {
        SDL_FreeSurface(Surf_Logo);
        Surf_Logo = NULL;
    }
	if(Background) {
		SDL_FreeSurface(Background);
		Background = NULL;
	}

	if(Play) {
		SDL_FreeSurface(Play);
		Play = NULL;
	}

	
}

void CAppStateMenu::OnEvent(SDL_Event* Event) {
if (Event->type == SDL_MOUSEMOTION) {
	
	if (WWIDTH == 640) {
		if (Collides(Event->button.x, Event->button.y, 280, 123, 207, 55)) {
			inBox = true;
		}
	}
	else {
		if (Collides(Event->button.x, Event->button.y, ((WWIDTH/4) + 280), ((WHEIGHT/3) + 123), 207, 55)) {
			inBox = true;
		}
	}
	inBox = false;
}


else if (Event->type == SDL_MOUSEBUTTONDOWN) {
	int x = Event->button.x;
	int y = Event->button.y;
	if (WWIDTH == 640) {
		if (Collides(x,y, 280, 123, 207, 55) == true) {
			click = true;
			inBox = true;
		}
	}
	else {
		if (Collides(x,y,((WWIDTH/4) + 280), ((WHEIGHT/3) + 123), 207, 55) == true) {
			click = true;
			inBox = true;
		}
	}
	if(inBox == true) {
				click = true;
			}
}


else if (Event->type == SDL_MOUSEBUTTONUP) {
	click = false;
}

}


void CAppStateMenu::OnKeyDown (SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_RETURN: {
		inBox = true;
		click = true;
					  }
	case SDLK_SPACE: {
		inBox = true;
		click = true;
					 }
	}
}


void CAppStateMenu::OnLoop() {
	int MouseX, MouseY;
	SDL_GetMouseState(&MouseX, &MouseY);
	  if (inBox) {
		menu.CurrentFrame = 1;
		if(click) {
			CAppStateManager::SetActiveAppState(APPSTATE_GAME);
			}
	}
	menu.CurrentFrame = 0;

}
 
void CAppStateMenu::OnRender(SDL_Surface* Surf_Display) {
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

	if(Play) {
		if (WWIDTH == 640) {
			CSurface::OnDraw(Surf_Display, Play, 280, 123, 0, menu.GetCurrentFrame() * 64, 207, 55);
		}
		else {
			CSurface::OnDraw(Surf_Display, Play, WWIDTH/4 + 280, WHEIGHT/3 + 123, 0, menu.GetCurrentFrame() * 64, 207, 55);
		}
	}
	
}
 


bool CAppStateMenu::Collides(int MouseX, int MouseY, int x, int y, int width, int height) {
	if ((MouseX >= x && MouseX <= x + width) && (MouseY >= y && MouseY <= y + height)) {
		return true;
	}
	return false;
}
CAppStateMenu* CAppStateMenu::GetInstance() {
    return &Instance;
}