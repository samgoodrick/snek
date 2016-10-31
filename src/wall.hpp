#ifndef WALL_HPP
#define WALL_HPP

#include "SDL/SDL.h"

class Wall
{
public:
    Wall( int x, int y );
    ~Wall();
    void Render( SDL_Surface* screen );

    SDL_Rect mCollider;
private:
    SDL_Surface* mTexture;
    SDL_Rect mOffset;
};

#endif
