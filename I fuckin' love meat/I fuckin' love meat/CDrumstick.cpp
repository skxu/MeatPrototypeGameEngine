#include "CDrumstick.h"
 
CDrumstick::CDrumstick() {
	Type = 3;
	meat = 2;
}
 
bool CDrumstick::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CMeat::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	
    return true;
}
 
void CDrumstick::OnLoop() {
    CMeat::OnLoop();
}
 
void CDrumstick::OnRender(SDL_Surface* Surf_Display) {
    CMeat::OnRender(Surf_Display);
}
 
void CDrumstick::OnCleanup() {
    CMeat::OnCleanup();
}
 
void CDrumstick::OnAnimate() {
    Anim_Control.MaxFrames = 8;
    CMeat::OnAnimate();
}
 
bool CDrumstick::OnCollision(CEntity* Entity) {
	Dead = true;
	return true;
}