#include "wall.hpp"

Wall::Wall( int x, int y )
    :mTexture( SDL_LoadBMP( "../img/wall.bmp" ) )
{
    mOffset.w = mOffset.h = mCollider.w = mCollider.h = 16;
    mOffset.x = mCollider.x = x;
    mOffset.y = mCollider.y = y;
}

Wall::~Wall()
{
    SDL_FreeSurface( mTexture );
}

void Wall::Render( SDL_Surface* screen )
{
    SDL_BlitSurface( mTexture, nullptr, screen, &mOffset );
}
	       
