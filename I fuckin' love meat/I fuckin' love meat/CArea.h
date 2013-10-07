#ifndef _CAREA_H_
    #define _CAREA_H_
 
#include "CMap.h"
 
class CArea {
    public:
        static CArea            AreaControl;
		static CArea			AreaControl2;
 
    public:
        std::vector<CMap>       MapList;
		std::vector<CMap>		MapList2;
 
    private:
        int                     AreaSize;
 
        SDL_Surface*        Surf_Tileset;

		SDL_Surface*		Surf_Tileset2;
 
    public:
        CArea();
 
        bool    OnLoad(char* File);
 
        void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
 
        void    OnCleanup();


	public:
    CMap*    GetMap(int X, int Y);
 
    CTile*    GetTile(int X, int Y);
};
 
#endif