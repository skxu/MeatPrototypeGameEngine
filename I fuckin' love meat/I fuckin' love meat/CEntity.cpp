#include "CEntity.h"
 
std::vector<CEntity*> CEntity::EntityList;
std::vector<int> CEntity::EntityIDList;
 
CEntity::CEntity() {
    Surf_Entity = NULL;
	Surf_Wep = NULL;
	Surf_Hat = NULL;
 
    X =0;
	Y= 0;
 
    Width = Height = 0;
	MoveLeft  = false;
    MoveRight = false;
	MoveDown = false;
	MoveUp = false;
 
    Type = ENTITY_TYPE_GENERIC;
	Attacking = false;
	Wep = false;
	Hat = false;
    Dead = false;
    Flags = ENTITY_FLAG_NONE;
 
    SpeedX = 0;
    SpeedY = 0;
 
    AccelX = 0;
    AccelY = 0;
 
    MaxSpeedX = 2.5;
    MaxSpeedY = 2.5;
 
    CurrentFrameCol = 0;
    CurrentFrameRow = 0;
 
    Col_X = 0;
    Col_Y = 0;
 
    Col_Width  = 0;
    Col_Height = 0;
    //AnimState = 0;

}
 
CEntity::~CEntity() {
}
 
bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if (Surf_Hat == NULL && Hat == true) {
		if ((Surf_Hat = CSurface::OnLoad(File)) == NULL) {
			return false;
		}
	
	}	else if (Surf_Wep == NULL && Wep == true) {
		if ((Surf_Wep = CSurface::OnLoad(File)) == NULL) {
			return false;
		}

	}	else if (Surf_Entity == NULL) {
	
		if((Surf_Entity = CSurface::OnLoad(File)) == NULL) {
			return false;
		}
	}

	
    CSurface::Transparent(Surf_Entity, 255, 0, 255);
	if (Surf_Hat) {
		CSurface::Transparent(Surf_Hat, 255, 0, 255);
	}
	if (Surf_Wep) {
		CSurface::Transparent(Surf_Wep, 255, 0, 255);
	}

    this->Width = Width;
    this->Height = Height;
 
    Anim_Control.MaxFrames = MaxFrames;
 
    return true;
}
 
void CEntity::OnLoop() {
	if(Attacking) {
		if (Anim_Control.CurrentFrame == 0/*Anim_Control.MaxFrames*/) {
			if (AttackCounter == 1) {
				Attacking = false;
				CurrentFrameCol -= 4;
				AttackCounter = 0;
			}
		}
		else if (Anim_Control.CurrentFrame + 1 == Anim_Control.MaxFrames) {
			AttackCounter = 1;
		}
	}
    //We're not Moving
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
 
void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);

	if (Surf_Hat != NULL) {
	if (CurrentFrameCol == 1 || CurrentFrameCol == 5) {
		CSurface::OnDraw(Surf_Display, Surf_Hat, X - CCamera::CameraControl.GetX() + 22, Y - CCamera::CameraControl.GetY() - 22, 0, 0, 50, 50);
	}
	else if (CurrentFrameCol == 0 || CurrentFrameCol == 4) {
		CSurface::OnDraw(Surf_Display, Surf_Hat, X - CCamera::CameraControl.GetX() + 15, Y - CCamera::CameraControl.GetY() - 22, 0, 0, 50, 50);
	}
	else if (CurrentFrameCol == 2 || CurrentFrameCol == 3) {
		CSurface::OnDraw(Surf_Display, Surf_Hat, X - CCamera::CameraControl.GetX() + 15, Y - CCamera::CameraControl.GetY() - 24, 0, 0, 50, 50);
	}
	}

	if (Surf_Wep != NULL) {
		CSurface::OnDraw(Surf_Display, Surf_Wep, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
	}

}



void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

	if(Surf_Hat) {
		SDL_FreeSurface(Surf_Hat);
	}

	if(Surf_Wep) {
		SDL_FreeSurface(Surf_Wep);
	}

	Surf_Wep = NULL;
    Surf_Entity = NULL;
	Surf_Hat = NULL;
}


void CEntity::OnAnimate() {
	if(Attacking) {
		if (CurrentFrameCol == 1 || CurrentFrameCol == 0) {
			CurrentFrameCol += 4;
		}
	} else {

    if(MoveLeft) {
        CurrentFrameCol = 1;
    }else
 
    if(MoveRight) {
        CurrentFrameCol = 0;
    }

	if(MoveDown) {
		CurrentFrameCol = 2;
	}

	if(MoveUp) {
		CurrentFrameCol = 3;
	}
	}
 
    Anim_Control.OnAnimate();
}


bool CEntity::OnCollision(CEntity* Entity) {
	return true;
}





void CEntity::OnMove(float MoveX, float MoveY) {
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
                SpeedX = 0;
            }
 
            if(PosValid((int)(X), (int)(Y + NewY))) {
                Y += NewY;
            }else{
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




void CEntity::StopXMove() {
    if(SpeedX > 0) {
        AccelX = -0.25;
    }
 
    if(SpeedX < 0) {
        AccelX =  0.25;
    }

 
    if(SpeedX < 2.0f && SpeedX > -2.0f) {
        AccelX = 0;
        SpeedX = 0;
    }
}
void CEntity::StopYMove() {

	if (SpeedY > 0) {
		AccelY = -1;
	}

	if (SpeedY < 0) {
		AccelY = 1;
	}

	
	if(SpeedY < 2.0f && SpeedY > -2.0f) {
        AccelY = 0;
        SpeedY = 0;
    }
	
}



bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
 
    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;
 
    left1 = tX;
    left2 = oX;
 
    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;
 
    top1 = tY;
    top2 = oY;
 
    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;
 
 
    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;
 
    if (right1 < left2) return false;
    if (left1 > right2) return false;
 
    return true;
}




bool CEntity::PosValid(int NewX, int NewY) {
    bool Return = true;
 
    int StartX     = (NewX + Col_X) / TILE_SIZE;
    int StartY     = (NewY + Col_Y) / TILE_SIZE;
 
    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)         / TILE_SIZE;
    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;
 
    for(int iY = StartY;iY <= EndY;iY++) {
        for(int iX = StartX;iX <= EndX;iX++) {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
 
            if(PosValidTile(Tile) == false) {
                Return = false;
            }
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



bool CEntity::PosValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
 
    if(Tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }
 
    return true;
}



bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
        Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {
 
        CEntityCol EntityCol;
 
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
 
        CEntityCol::EntityColList.push_back(EntityCol);
 
        return false;
    }
 
    return true;
}