#include "snek.hpp"

Snek::Snek()
    :mDir( EAST ), mTexture( SDL_LoadBMP( "../img/snek.bmp" ) )
{
    Snake.emplace_back( new Node( 320, 240 ) );
    head = Snake[0];
    mCollider = head->mCollider;
}

Snek::~Snek()
{
    for( auto i : Snake )
	delete i;
}

void Snek::Push()
{
    Snake.emplace_back( new Node( Snake[Snake.size() - 1]->x+16, Snake[Snake.size()-1]->y ) );
}

void Snek::Render( SDL_Surface* screen )
{
    for( auto i : Snake )
	SDL_BlitSurface( mTexture, nullptr, screen, &(i->mOffset) );
}

SDL_Rect Snek::GetCollider()
{
    return head->mCollider;
}


void Snek::Move()
{
    std::vector<std::pair<int, int>> positions;
    positions.reserve(Snake.size());
    for( auto i : Snake )
    {
	positions.push_back( std::make_pair( i->x, i->y ) );
    }

    switch( mDir )
    {
    case NORTH:
	Snake[0]->y -= 16;
	mCollider.y = Snake[0]->mCollider.y = Snake[0]->y;
	Snake[0]->mOffset.y = Snake[0]->y;
	break;
    case SOUTH:
	Snake[0]->y += 16;
	mCollider.y = Snake[0]->mCollider.y = Snake[0]->y;
	Snake[0]->mOffset.y = Snake[0]->y;
	break;
    case EAST:
	Snake[0]->x += 16;
	mCollider.x = Snake[0]->mCollider.x = Snake[0]->x;
	Snake[0]->mOffset.x = Snake[0]->x;
	break;
    case WEST:
	Snake[0]->x -= 16;
	mCollider.x = Snake[0]->mCollider.x = Snake[0]->x;
	Snake[0]->mOffset.x = Snake[0]->x;
	break;
    }
    
    for( int i = 1; i < Snake.size(); ++i )
    {
    	Snake[i]->mCollider.x = Snake[i]->mOffset.x = Snake[i]->x = positions[i-1].first;
    	Snake[i]->mCollider.y = Snake[i]->mOffset.y = Snake[i]->y = positions[i-1].second;
    }

}

bool Snek::SelfCollide()
{
    for( auto i : Snake )
    {
	if( i != head && head->x == i->x && head->y == i->y )
	    return true;
    }
    return false;
}

Node::Node( int px, int py )
    :x( px ), y( py )
{
    mOffset.w = 16;
    mOffset.h = 16;
    mOffset.x = px;
    mOffset.y = py;
    mCollider.x = px;
    mCollider.y = py;
}
