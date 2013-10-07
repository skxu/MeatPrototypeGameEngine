#include "CAppStateGame.h"
#include "CApp.h"
#include "CEvent.h"
#include "CMeatGen.h"
#include "Define.h"
#include "CMonsterGen.h"


CAppStateGame CAppStateGame::Instance;
 
CAppStateGame::CAppStateGame() {
	fullscreen = false;
	splat = 1;
}
 
void CAppStateGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            if (Player.MoveDown == false && Player.MoveUp == false) {
				Player.MoveLeft = true;
				break;
			 }
			break;
		}
 
        case SDLK_RIGHT: {
			 if (Player.MoveDown == false && Player.MoveUp == false) {
				Player.MoveRight = true;
				break;
			 }
            break;
        }
 
        case SDLK_DOWN: {
            if (Player.MoveRight == false && Player.MoveLeft == false) {
				Player.MoveDown = true;
				break;
			}
			break;
        }

		case SDLK_UP: {
			if (Player.MoveRight == false && Player.MoveLeft == false) {
				Player.MoveUp = true;
				break;
			}
			break;
	  }
		
		case SDLK_a: {
            if (Player.MoveDown == false && Player.MoveUp == false) {
				Player.MoveLeft = true;
				break;
			 }
			break;
		}
 
        case SDLK_d: {
			 if (Player.MoveDown == false && Player.MoveUp == false) {
				Player.MoveRight = true;
				break;
			 }
            break;
        }
 
        case SDLK_s: {
            if (Player.MoveRight == false && Player.MoveLeft == false) {
				Player.MoveDown = true;
				break;
			}
			break;
        }

		case SDLK_w: {
			if (Player.MoveRight == false && Player.MoveLeft == false) {
				Player.MoveUp = true;
				break;
			}
			break;
	  }

		case SDLK_LCTRL: {
			if (Player.Attacking == false) {
				CSoundBank::SoundControl.Play(splat, 0);
				Player.Anim_Control.SetCurrentFrame(0);
				Player.Attacking = true;
				break;
			}
			break;
					  }

		case SDLK_F2: {
			if (Player.Attacking == false) {
				CSoundBank::SoundControl.Play(splat, 0);
				Player.Anim_Control.SetCurrentFrame(0);
				Player.Attacking = true;
				break;
			}
			break;
					  }


		case SDLK_F3: {
			Player.X += 3;
			break;
			}

		case SDLK_F4: {
			CMeat* meatPiece = new CMeat();
			if (meatPiece->OnLoad("meat.png", 64, 64, 8) == false) {
				return;
			}
			CEntity::EntityList.push_back(meatPiece);
			meatPiece->X = Player.X + (SDL_GetTicks()%200);
			meatPiece->Y = Player.Y;
			break;
					  }

		case SDLK_F5: {
			CDrumstick* meatPiece = new CDrumstick();
			if (meatPiece->OnLoad("drumstick.png", 64, 50, 8) == false) {
				return;
			}
			CEntity::EntityList.push_back(meatPiece);
			meatPiece->X = Player.X + (SDL_GetTicks()%200);
			meatPiece->Y = Player.Y;
			break;
					  }

		case SDLK_F6: {
			CHam* meatPiece = new CHam();
			if (meatPiece->OnLoad("ham.png", 64, 64, 8) == false) {
				return;
			}
			CEntity::EntityList.push_back(meatPiece);
			meatPiece->X = Player.X + (SDL_GetTicks()%200);
			meatPiece->Y = Player.Y;
			break;
					  }

		case SDLK_F11: {
			if (fullscreen)  {
			fullscreen = false;
			}
			else {
			fullscreen = true;
			}
		}



        default: {
        }

	}
}
 
void CAppStateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            Player.MoveLeft = false;
            break;
        }
 
        case SDLK_RIGHT: {
            Player.MoveRight = false;
            break;
        }
		
		case SDLK_DOWN: {
			Player.MoveDown = false;
			break;
		}

		case SDLK_UP: {
			Player.MoveUp = false;
			break;
		}


		case SDLK_a: {
            Player.MoveLeft = false;
            break;
        }
 
        case SDLK_d: {
            Player.MoveRight = false;
            break;
        }
		
		case SDLK_s: {
			Player.MoveDown = false;
			break;
		}

		case SDLK_w: {
			Player.MoveUp = false;
			break;
		}

		case SDLK_F2: {
			break;
		}


        default: {
        }
    }
}
 
void CAppStateGame::OnActivate() {
    if(CArea::AreaControl.OnLoad("./maps/1.area") == false) {
        return;
    }

	if (CArea2::AreaControl.OnLoad("./maps/2.area") == false) {
		return;
	}
	
	splat = CSoundBank::SoundControl.OnLoad("splat.ogg");

	if(Player.OnLoad("hat.png", 30, 30, 1) == false) {
        return;
    }

    if(Player.OnLoad("Pudge_White.png", 64, 64, 8) == false) {
        return;
    }

	if(Monster.OnLoad("monster.png", 64, 64, 8) == false) {
		return;
	}
 
    if(Npc1.OnLoad("Pudge_White.png", 64, 64, 8) == false) {
        return;
    }

	if(Meat.OnLoad("meat.png", 64, 64, 8) == false) {
			return;
	}

	if(Ham.OnLoad("ham.png", 64, 64, 8) == false) {
		return;
	}

	if(Drumstick.OnLoad("drumstick.png", 64, 50, 8) == false) {
		return;
	}


	CEntity::EntityList.push_back(&Player);
	//MeatGenerator.OnActivation();
	//CMeatGen* MGen = new CMeatGen();
	MonsterGenerator.OnActivation();
	//MGen->OnActivation();
	Monster.X = 600;
	Monster.Y = 250;
	Player.X = 100;
	Player.Y = 500;
	Player.ID = 0;
	//Player.MaxFat = 20;
    Npc1.X = 100;
	Npc1.Y = 250;
	Npc1.ID = 1;
	Meat.ID = 3;
	Meat.X = 300;
	Meat.Y = 300;
	Ham.X = 100;
	Ham.Y = 450;
	Drumstick.X = 200;
	Drumstick.Y = 200;
    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Npc1);
	CEntity::EntityList.push_back(&Monster);
	CEntity::EntityList.push_back(&Meat);
	CEntity::EntityList.push_back(&Ham);
	CEntity::EntityList.push_back(&Drumstick);
 
    CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
}
 
void CAppStateGame::OnDeactivate() {
    CArea::AreaControl.OnCleanup();
 
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
 
        CEntity::EntityList[i]->OnCleanup();
    }
 
    CEntity::EntityList.clear();
}
 
void CAppStateGame::OnLoop() {
	CFPS::FPSControl.OnLoop();
	if (CEntity::EntityList.size() != 0) {
		MeatGenerator.OnLoop();
		
		
	}
	MonsterGenerator.OnLoop();
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
		
		if(CEntity::EntityList[i]->Dead == true) {
			CEntity::EntityList[i]->OnCleanup();
			//CEntity::EntityList.erase(CEntity::EntityList.begin() + i - 1);
			continue;
		}
        CEntity::EntityList[i]->OnLoop();
    }
 
    //Collision Events
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;
 
        if(EntityA == NULL || EntityB == NULL) continue;
 
        if(EntityA->OnCollision(EntityB)) {
            EntityB->OnCollision(EntityA);
        }
    }
 
    CEntityCol::EntityColList.clear();
}
 
void CAppStateGame::OnRender(SDL_Surface* Surf_Display) {
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WWIDTH;
    Rect.h = WHEIGHT;
 
    SDL_FillRect(Surf_Display, &Rect, 0);

	if (Surf_Display->flags & SDL_FULLSCREEN) {
		if(fullscreen == false) {
			if ((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
				return;
			}
		}
	} else if (fullscreen == true) {

		if ((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL) {
		return;
	}
	}
 
    CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	CArea2::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
 
        CEntity::EntityList[i]->OnRender(Surf_Display);
    }
	CEntity::EntityList[0] -> OnRender(Surf_Display);
}
 
CAppStateGame* CAppStateGame::GetInstance() {
    return &Instance;
}