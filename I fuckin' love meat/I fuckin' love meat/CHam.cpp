#include "CHam.h"
#include "CMeat.h"
 
CHam::CHam() {
	Type = 3;
	meat = 3;
	//Col_Width = 20;
	//Col_X = 20;
}
 
bool CHam::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CMeat::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	
    return true;
}
 
void CHam::OnLoop() {
    CMeat::OnLoop();
}
 
void CHam::OnRender(SDL_Surface* Surf_Display) {
    CMeat::OnRender(Surf_Display);
}
 
void CHam::OnCleanup() {
    CMeat::OnCleanup();
}
 
void CHam::OnAnimate() {
    Anim_Control.MaxFrames = 8;
    CMeat::OnAnimate();
}
 
bool CHam::OnCollision(CEntity* Entity) {
	Dead = true;
	return true;
}