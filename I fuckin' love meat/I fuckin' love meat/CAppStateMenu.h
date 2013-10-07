#ifndef __CAPPSTATEMENU_H__
    #define __CAPPSTATEMENU_H__
 
#include "CAppState.h"
#include "CSurface.h"
#include "CAnimation.h"
#include "CSoundBank.h"
 
class CAppStateMenu : public CAppState {
    private:
        static CAppStateMenu Instance;
 
        SDL_Surface* Surf_Logo;

		SDL_Surface* Background;

		SDL_Surface* Play;
 
        int StartTime;

		int Time1;
		
		bool inBox;

		bool click;

		int Soundtrack;

		int splat;

		CAnimation menu;

		CAnimation splash;
 
    private:
        CAppStateMenu();

		bool Collides(int MouseX, int MouseY, int X, int Y, int Width, int Height);


 
    public:
		void OnEvent(SDL_Event* Event);

        void OnActivate();
 
        void OnDeactivate();

		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
    public:
        static CAppStateMenu* GetInstance();
};
 
#endif