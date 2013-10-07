#include "CNpc.h"

 
CNpc::CNpc() {
	Col_Width = 20;
	Type = 4;
	AccelX = 1;
	AccelY = 1;
	HP = 3;
	//Col_Height = 50;
	//Col_Y = 50;
}
 
bool CNpc::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	isWalking = false;
	WalkTime = 750;
	Type = 4;
    return true;
}
 
void CNpc::OnLoop() {
	if (HP <= 0) {
		Dead = true;
	}
	int RunningTime = SDL_GetTicks() - StartTime;
	if (isWalking && RunningTime > WalkTime) {
		StopWalk();
	}
    CEntity::OnLoop();
}
 
void CNpc::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CNpc::OnCleanup() {
    CEntity::OnCleanup();
}
 
void CNpc::OnAnimate() {
    if(SpeedX != 0) {
        Anim_Control.MaxFrames = 8;
    } else if (SpeedY != 0) {
		Anim_Control.MaxFrames = 8;
	}
	
	else{
        Anim_Control.MaxFrames = 0;
    }
 
    CEntity::OnAnimate();
}
 
bool CNpc::OnCollision(CEntity* Entity) {
	if(Entity->Type == 3) {
		MaxSpeedX = 2.5;
		return true;
	}
	if (Entity->Type == 1) {
		

	if(Entity->X > X && (Entity->Y + 20 > Y) && (Entity->Y - 15 < Y)) { //Height - Col_Height = 15
		Walk(1); //Walk left
	} else if (Entity->X < X && (Entity->Y + 20 > Y) && (Entity->Y - 15 < Y)) {
		Walk(2); //Walk right
	} if (Entity->Y > Y) {
		Walk(3); //Walk up
	} else if (Entity -> Y < Y) {
		Walk(4); //Walk down
	}
	}
		return true;

}


void CNpc::Walk(int x) {
	switch (x) {
	case 1: {
		if (isWalking) return;
		MoveLeft = true;
		StartTime = SDL_GetTicks();
		SpeedX = -MaxSpeedX;
		isWalking = true;
			}
	case 2: {
		if (isWalking) return;
		MoveRight = true;
		StartTime = SDL_GetTicks();
		SpeedX = MaxSpeedX;
		isWalking = true;
			}
	case 3: {
		if (isWalking) return;
		MoveUp = true;
		StartTime = SDL_GetTicks();
		SpeedY = -MaxSpeedY;
		isWalking = true;
			}
	case 4: {
		if (isWalking) return;
		MoveDown = true;
		StartTime = SDL_GetTicks();
		SpeedY = MaxSpeedY;
		isWalking = true;
			}
	}
}


void CNpc::StopWalk() {
	isWalking = false;
	MoveUp = false;
	MoveDown = false;
	MoveLeft = false;
	MoveRight = false;
	SpeedX = 0;
	SpeedY = 0;
	StopXMove();
	StopYMove();
}

