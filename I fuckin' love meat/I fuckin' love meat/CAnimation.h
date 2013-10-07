#ifndef _CANIMATION_H_
    #define _CANIMATION_H_
 
#include <SDL.h>
 
class CAnimation {
    protected:
        
 
        int     FrameInc;
 
    public:
        int     FrameRate; //Milliseconds
 
        long    OldTime;

		int    CurrentFrame;
 
    public:
        int    MaxFrames;
 
        bool    Oscillate;
 
    public:
        CAnimation();
 
        void OnAnimate();
 
    public:
        void SetFrameRate(int Rate);
 
        void SetCurrentFrame(int Frame);
 
        int GetCurrentFrame();
};
 
#endif