#include "CApp.h"

CApp::CApp() {
	Running = true;
	Surf_Display = NULL;
}

int CApp::OnExecute() {
	//Attempt to initialize game; failure returns -1
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;
	while (Running) {
		//Check for events one at a time via PollEvent and pass them to OnEvent
		while (SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();
	}

	OnCleanup();
	return 0;
}



int main(int argc, char* argv[]) {
	CApp MeatGame;

	return MeatGame.OnExecute();
}
