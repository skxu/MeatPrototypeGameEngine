#include "CMeat.h"
 
CMeat::CMeat() {
	Type = 3;
	meat = MEAT_TYPE_GENERIC;
}
 
bool CMeat::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	
    return true;
}
 
void CMeat::OnLoop() {
    CEntity::OnLoop();
}
 
void CMeat::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CMeat::OnCleanup() {
    CEntity::OnCleanup();
}
 
void CMeat::OnAnimate() {
    Anim_Control.MaxFrames = 8;
    CEntity::OnAnimate();
}
 
bool CMeat::OnCollision(CEntity* Entity) {
	Dead = true;

	return true;
}