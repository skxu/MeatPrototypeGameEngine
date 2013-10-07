#ifndef _CAREA2_H_
    #define _CAREA2_H_
 
#include "CMap.h"
 
class CArea2 {
    public:
        static CArea2            AreaControl;
		static CArea2			AreaControl2;
 
    public:
        std::vector<CMap>       MapList;
		std::vector<CMap>		MapList2;
 
    private:
        int                     AreaSize;
 
        SDL_Surface*        Surf_Tileset;

		SDL_Surface*		Surf_Tileset2;
 
    public:
        CArea2();
 
        bool    OnLoad(char* File);
 
        void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
 
        void    OnCleanup();


	public:
    CMap*    GetMap(int X, int Y);
 
    CTile*    GetTile(int X, int Y);
};
 
#endif