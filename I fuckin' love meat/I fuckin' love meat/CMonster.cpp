#include "CMonster.h"
#include "CEntity.h"

 
CMonster::CMonster() {
	Col_Width = 20;
	Type = 4;
	AccelX = 2;
	AccelY = 1;
	MaxSpeedX = 15;
	HP = 3;
	Invincible = false;
	InvincibleTime = 1000;
	BumpTime = 1000;
	Bump = false;
	 

	//Col_Height = 50;
	//Col_Y = 50;
}
 
bool CMonster::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	isWalking = false;
	InvalidTile = false;
	WalkTime = 3000;
	Type = 4;
    return true;
}
 
void CMonster::OnLoop() {
	if (HP < 0) {
		Dead = true;
	}

	if (Invincible && SDL_GetTicks() - InvincibleCounter > InvincibleTime) {
		Invincible = false;
	}

	if(Bump && SDL_GetTicks() - BumpCounter > BumpTime) {
		Bump = false;
	}
	int RunningTime = SDL_GetTicks() - StartTime;
	if (isWalking && RunningTime > WalkTime) {
		StopWalk();
	}
    CTile* Tile = CArea::AreaControl.GetTile(X, Y);
	if(PosValidTile(Tile) == false) {
		X++;
	}

	if (isWalking && InvalidTile) {
		int walknumber = (rand()%4) + 1;
		if (CurrentFrameCol == 0) {
			StopWalk();
			MaxSpeedX = 2.5;
			MaxSpeedY = 2.5;
			
			while (walknumber == 2) {
				walknumber = (rand()%4) + 1;
			}
			

			Walk(walknumber);
		} else if (CurrentFrameCol == 1) {
			StopWalk();
			MaxSpeedX = 2.5;
			MaxSpeedY = 2.5;
			X++;
			while (walknumber == 1) {
				walknumber = (rand()%4) + 1;
			}
			
			Walk(walknumber);
		} else if (CurrentFrameCol == 2) {
			StopWalk();
			MaxSpeedX = 2.5;
			MaxSpeedY = 2.5;
			Y--;
			while (walknumber == 3) {
				walknumber = (rand()%4) + 1;
			}
			
			Walk(walknumber);
		} else if (CurrentFrameCol == 3) {
			StopWalk();
			MaxSpeedX = 2.5;
			MaxSpeedY = 2.5;
			Y++;
			while (walknumber == 4) {
				walknumber = (rand()%4) + 1;
			}
			
			Walk(walknumber);
		}
		InvalidTile = false;
		
	}

	if (!isWalking && SDL_GetTicks()%(1000 + (rand()%300)) == 0) {
		MaxSpeedX = 2.5;
		MaxSpeedY = 2.5;
		Walk((rand()%4)+1);
	}

	if(MoveLeft == false && MoveRight == false) {
        StopXMove();
    }
	
	if(MoveDown == false && MoveUp == false) {
		StopYMove();
	}

    if(MoveLeft) {
        AccelX = -0.25;
    }else
 
    if(MoveRight) {
        AccelX = 0.25;
    }

	if(MoveDown) {
		AccelY = 0.25;
	}

	if(MoveUp) {
		AccelY = -0.25;
	}
 
    if(Flags & ENTITY_FLAG_GRAVITY) {
        AccelY = 0.0f; //0.75f
    }
 
    SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
    SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();
 
    if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
    if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
    if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
    if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;
 
    OnAnimate();
    OnMove(SpeedX, SpeedY);
}




 
void CMonster::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CMonster::OnCleanup() {
    CEntity::OnCleanup();
}
 
void CMonster::OnAnimate() {
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
 
bool CMonster::OnCollision(CEntity* Entity) {
	if(Entity->Type == 3) {
		return true;
	}
	if(Entity->Type == 4) {
		if (Entity->X > X) {
			X--;
			return true;
		} else {
			X++;
			return true;
		}
	}
	if (Entity->Type == 1) {
		if (Entity->Attacking == true && Invincible == false) {
			HP -= 1;
			Invincible = true;
			InvincibleCounter = SDL_GetTicks();
		}
		if (!Bump) {
			Bump = true;
			BumpCounter = SDL_GetTicks();

		/*
		if (isWalking) {
			if (CurrentFrameCol == 0) {
			MaxSpeedX = 20;
			MaxSpeedY = 20;
			X -= 1;
			StopWalk();
			Walk((rand()%4)+1);
			return true;
		} else if (CurrentFrameCol == 1) {
			MaxSpeedX = 20;
			MaxSpeedY = 20;
			X += 1;
			StopWalk();
			Walk((rand()%4)+1);
			return true;
		} else if (CurrentFrameCol == 2) {
			MaxSpeedX = 20;
			MaxSpeedY = 20;
			StopWalk();
			Walk((rand()%4)+ 1);
			return true;
		} else if (CurrentFrameCol == 3) {
			MaxSpeedX = 20;
			MaxSpeedY = 20;
			StopWalk();
			Walk((rand()%4) +1);
			return true;
		}
		}
		*/

	if(Entity->X > X && (Entity->Y + 30 > Y) && (Entity->Y - 20 < Y)) { //Height - Col_Height = 15
		if(PosValid(X-1, Y)) {
			X--;
		}
		MaxSpeedX = 20;
		MaxSpeedY = 20;
		Anim_Control.FrameRate = 20;
		Walk(1); //Walk left
	} else if (Entity->X < X && (Entity->Y + 30 > Y) && (Entity->Y - 20 < Y)) {
		if(PosValid(X+1, Y)) {
			X++;
		}
		MaxSpeedX = 20;
		MaxSpeedY = 20;
		Anim_Control.FrameRate = 20;
		Walk(2); //Walk right
	} if (Entity->Y > Y) {
		if(PosValid(X,Y-1)) {
			//Y--;
		}
		MaxSpeedX = 20;
		MaxSpeedY = 20;
		Anim_Control.FrameRate = 20;
		Walk(3); //Walk up
	} else if (Entity -> Y < Y) {
		if(PosValid(X,Y+1)) {	
			//Y++;
		}
		MaxSpeedX = 20;
		MaxSpeedY = 20;
		Anim_Control.FrameRate = 20;
		Walk(4); //Walk down
		}
	}
	}
		return true;

}


void CMonster::Walk(int x) {
	switch (x) {
	case 1: {
		if (isWalking) return;
		//Anim_Control.FrameRate = 20;
		MoveLeft = true;
		StartTime = SDL_GetTicks();
		SpeedX = -MaxSpeedX;
		isWalking = true;
			}
	case 2: {
		if (isWalking) return;
		//Anim_Control.FrameRate = 20;
		MoveRight = true;
		StartTime = SDL_GetTicks();
		SpeedX = MaxSpeedX;
		isWalking = true;
			}
	case 3: {
		if (isWalking) return;
		//Anim_Control.FrameRate = 20;
		MoveUp = true;
		StartTime = SDL_GetTicks();
		SpeedY = -MaxSpeedY;
		isWalking = true;
			}
	case 4: {
		if (isWalking) return;
		//Anim_Control.FrameRate = 20;
		MoveDown = true;
		StartTime = SDL_GetTicks();
		SpeedY = MaxSpeedY;
		isWalking = true;
			}
	}
}


void CMonster::StopWalk() {
	Anim_Control.FrameRate = 100;
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




void CMonster::OnMove(float MoveX, float MoveY) {
    if(MoveX == 0 && MoveY == 0) return;
 
    double NewX = 0;
    double NewY = 0;
 
    MoveX *= CFPS::FPSControl.GetSpeedFactor();
    MoveY *= CFPS::FPSControl.GetSpeedFactor();
 
    if(MoveX != 0) {
        if(MoveX >= 0)     NewX =  CFPS::FPSControl.GetSpeedFactor();
        else             NewX = -CFPS::FPSControl.GetSpeedFactor();
    }
 
    if(MoveY != 0) {
        if(MoveY >= 0)     NewY =  CFPS::FPSControl.GetSpeedFactor();
        else             NewY = -CFPS::FPSControl.GetSpeedFactor();
    }
 
    while(true) {
        if(Flags & ENTITY_FLAG_GHOST) {
            PosValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities
 
            X += NewX;
            Y += NewY;
        }else{
            if(PosValid((int)(X + NewX), (int)(Y))) {
                X += NewX;
            }else{
				InvalidTile = true;
                SpeedX = 0;
            }
 
            if(PosValid((int)(X), (int)(Y + NewY))) {
                Y += NewY;
            }else{
				InvalidTile = true;
                SpeedY = 0;
            }
        }
 
        MoveX += -NewX;
        MoveY += -NewY;
 
        if(NewX > 0 && MoveX <= 0) NewX = 0;
        if(NewX < 0 && MoveX >= 0) NewX = 0;
 
        if(NewY > 0 && MoveY <= 0) NewY = 0;
        if(NewY < 0 && MoveY >= 0) NewY = 0;
 
        if(MoveX == 0) NewX = 0;
        if(MoveY == 0) NewY = 0;
 
        if(MoveX == 0 && MoveY     == 0)     break;
        if(NewX  == 0 && NewY     == 0)     break;
    }
}



bool CMonster::PosValid(int NewX, int NewY) {
    bool Return = true;
 
    int StartX     = (NewX + Col_X) / TILE_SIZE;
    int StartY     = (NewY + Col_Y) / TILE_SIZE;
 
    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)         / TILE_SIZE;
    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;
 
    for(int iY = StartY;iY <= EndY;iY++) {
        for(int iX = StartX;iX <= EndX;iX++) {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
 
            if(PosValidTile(Tile) == false) {
				InvalidTile = true;
                Return = false;
			}
				InvalidTile = false;
        }
    }
 
    if(Flags & ENTITY_FLAG_MAPONLY) {
    }else{
        for(int i = 0;i < EntityList.size();i++) {
            if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
                Return = false;
            }
        }
    }
 
    return Return;
}



bool CMonster::PosValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
 
    if(Tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }
 
    return true;
}



bool CMonster::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
        Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {
 
        CEntityCol EntityCol;
 
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
 
        CEntityCol::EntityColList.push_back(EntityCol);
		if (Bump) {
			return true;
		}
        return false;
    }
 
    return true;
}