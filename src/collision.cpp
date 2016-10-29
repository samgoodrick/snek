#include "collision.hpp"

bool Collision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int bottomA, bottomB;
    int topA, topB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.w;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.w;

    if( bottomA <= topB ||
	    topA >= bottomB ||
	    rightA <= leftB ||
	    leftA >= rightB )
	return false;
    return true;    
}
