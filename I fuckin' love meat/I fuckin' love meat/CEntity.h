#ifndef _CENTITY_H_
    #define _CENTITY_H_
 
#include <vector>
 
#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"
 
enum {
    ENTITY_TYPE_GENERIC = 0,
 
    ENTITY_TYPE_PLAYER = 1,
	ENTITY_TYPE_ITEM = 2,
	ENTITY_TYPE_MEAT = 3,
	ENTITY_TYPE_NPC = 4
};

 
enum {
    ENTITY_FLAG_NONE     = 0,
 
    ENTITY_FLAG_GRAVITY    = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY    = 0x00000004
};



	
 
class CEntity {
    public:
        static std::vector<CEntity*>    EntityList;
		static std::vector<int>        EntityIDList;
 
    protected:
 
        SDL_Surface*    Surf_Entity;

		SDL_Surface*	Surf_Hat;

		SDL_Surface* Surf_Wep;
 
    public:
		CAnimation      Anim_Control;

		int		ID;
        float           X;
        float           Y;
 
        int             Width;
        int             Height;
 
        bool        MoveLeft;
        bool        MoveRight;
		bool		MoveDown;
		bool		MoveUp;
 
    public:
        int        Type;
		bool		Attacking;
		int			AttackCounter;
        bool        Dead;
        int        Flags;
 
    public:
        float        SpeedX;
        float        SpeedY;
 
        float        AccelX;
        float        AccelY;
 
    public:
        float        MaxSpeedX;
        float        MaxSpeedY;
 
    protected:
        int             CurrentFrameCol;
        int             CurrentFrameRow;
 
    protected:
		
		bool		Wep;
		bool		Hat;
        int        Col_X;
        int        Col_Y;
        int        Col_Width;
        int        Col_Height;
 
    public:
        CEntity();
 
        virtual ~CEntity();
 
    public:
        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);
 
        virtual void OnLoop();
 
        virtual void OnRender(SDL_Surface* Surf_Display);
 
        virtual void OnCleanup();
 
        virtual void OnAnimate();
 
        virtual bool OnCollision(CEntity* Entity);
 
    public:
        void    OnMove(float MoveX, float MoveY);
 
        void     StopXMove();

		void	 StopYMove();
 
    public:
        bool    Collides(int oX, int oY, int oW, int oH);
 
    private:
        bool     PosValid(int NewX, int NewY);
 
        bool     PosValidTile(CTile* Tile);
 
        bool     PosValidEntity(CEntity* Entity, int NewX, int NewY);        
};
 
class CEntityCol {
    public:
        static std::vector<CEntityCol>    EntityColList;
 
    public:
        CEntity* EntityA;
        CEntity* EntityB;
 
    public:
        CEntityCol();
};
 
#endif