#include "CPlayer.h"
#include "CMeat.h"
 
CPlayer::CPlayer() {
	Col_Width = 20;
	Col_Height = 45;
	Col_Y = 45;
	Fat = 0;
	Hat = true;
	MaxFat = 15;
	
}
 
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames) {

    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	Type = ENTITY_TYPE_PLAYER;
    return true;
}
 
void CPlayer::OnLoop() {
    CEntity::OnLoop();
}
 
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
}
 
void CPlayer::OnAnimate() {
    if(SpeedX != 0) {
        Anim_Control.MaxFrames = 8;
    } else if (SpeedY != 0) {
		Anim_Control.MaxFrames = 8;
	} else if (Attacking) {
		Anim_Control.MaxFrames = 8;
	}
	
	else{
        Anim_Control.MaxFrames = 0;
    }
 
    CEntity::OnAnimate();
}
 
bool CPlayer::OnCollision(CEntity* Entity) {
	if(Entity->Type == 3) { //Meat
		if (Fat > MaxFat) {
			return true;
		}
		CMeat* A = reinterpret_cast<CMeat*>(Entity);
		if (A->meat == 3) {
			Fat++;
			MaxSpeedX = 10;
			AccelX = 2;
			return true;
		}
		else if (A->meat == 2) {
			if (Wep != true) {
				Wep = true;
				if(OnLoad("equip_drumstick.png", 64, 64, 8) == false) {
					return false;
				}
			}
			Fat++;
			MaxSpeedY = 10;
			MaxSpeedX += rand()%5;
			AccelY = 2;
			return true;
		}
		else if (A->meat == 0) {
			Fat++;
			MaxSpeedX++;
			AccelX = 5;
			if (Anim_Control.FrameRate < 20) {
			Anim_Control.FrameRate++;
				}
			return true;
		}
	}

	else if(Entity->Type == 1) { //Player
			SpeedX = -SpeedX;
			SpeedY = -SpeedY;
			return true;
	}
	else if (Entity->Type == 4) { //NPC
		return true;
	}
	


}