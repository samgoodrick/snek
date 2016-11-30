#include "SDL/SDL.h"
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <cassert>
#include "snek.hpp"
#include "wall.hpp"
#include "globals.hpp"
#include "util.hpp"
#include "timer.hpp"

Uint32 Respawn = 0;
int gScore = 0;

struct Food
{
    Food()
		:texture( SDL_LoadBMP( "../img/food.bmp" ) ), Active( true )
    {
		Randomize_Position();
    }
    ~Food()
    {
    	SDL_FreeSurface( texture );
		texture = nullptr;
    }
    void Render( SDL_Surface* screen )
    {
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface( texture, NULL, screen, &offset ); 
    }
    void Randomize_Position()
    {
		x = (rand() % 640);
		y = (rand() % 480);
		round_to_multiple<int>( x, 16 );
		round_to_multiple<int>( y, 16 );
		if( x < 16 )
			x += 32;
		if( x > 640 - 16 )
			x -= 32;
		if( y > 480 - 16 )
			y -= 32;
		if( y < 16 )
			y += 32;

		Collider.x = x;
		Collider.y = y;
		Collider.w = 16;
		Collider.h = 16;
		offset.w = 16;
		offset.h = 16;
		offset.x = x;
		offset.y = y;
    }
    int x;
    int y;
    SDL_Surface* texture;
    SDL_Rect Collider;
    SDL_Rect offset;
    bool Active;
};

bool Collision_With_Food( Snek& snek, Food* food )
{
    // int leftA, leftB;
    // int rightA, rightB;
    // int bottomA, bottomB;
    // int topA, topB;
    
    // leftA = snek.mCollider.x;
    // rightA = snek.mCollider.x + snek.mCollider.w;
    // topA = snek.mCollider.y;
    // bottomA = snek.mCollider.y + snek.mCollider.h;

    // leftB = food->Collider.x;
    // rightB = food->Collider.x + food->Collider.w;
    // topB = food->Collider.y;
    // bottomB = food->Collider.y + food->Collider.h;

    // if( bottomA <= topB ||
    // 	topA >= bottomB ||
    // 	rightA <= leftB ||
    // 	leftA >= rightB )
    // 	return false;
    
    return( snek.mCollider.x == food->Collider.x &&
			snek.mCollider.y == food->Collider.y );
}

template<typename T>
bool Collision( T Obj1, T Obj2 )
{
    return ( Obj1.y == Obj2.y && Obj1.x == Obj2.x );
}

int main( int argc, char** argv )
{
	constexpr int frames_per_second = 10;
	int frame = 0;
	bool cap = true;
	Timer fps;

    srand( time( NULL ) );
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_Surface* background = SDL_LoadBMP( "../img/background.bmp" );
    SDL_BlitSurface( background, NULL, screen, NULL );
    SDL_Flip( screen );
    SDL_Event e;
    bool quit = false;
    Snek snek;

    SDL_Surface* vert = SDL_LoadBMP( "../img/vert.bmp" );
    SDL_Surface* horiz = SDL_LoadBMP( "../img/horiz.bmp" );
    std::vector<Wall*> walls;
    walls.reserve( 2*( 640 / 16 ) + 2*( 480 / 16 ) );
    for( int i = 0; i < 640; i += 16 )
    {
		if( i < 480 )
		{
			walls.push_back( new Wall( 0, i ) );
			walls.push_back( new Wall( 640 - 16, i ) );
		}
		walls.push_back( new Wall( i, 0 ) );
		walls.push_back( new Wall( i, 480 - 16 ) );
    }
    
    bool is_food = true;
    auto food = new Food;

    while( !quit )
    {
		fps.start();
		if( !is_food )
		{
			if( SDL_GetTicks() - Respawn >= 25 )
			{
				food->Randomize_Position();
				is_food = true;
				Respawn = 0;
			}
		}
		SDL_BlitSurface( background, NULL, screen, NULL );

		snek.Render( screen );

		for( auto i : walls )
			i->Render( screen );
	
		if( is_food )
		{
			food->Render( screen );
			if( Collision_With_Food( snek, food ) && Respawn == 0 )
			{
				snek.Push();
				++gScore;
				is_food = false;
				Respawn = SDL_GetTicks();
		
			}		
		}

		for( auto i : walls )
		{
			if( Collision<SDL_Rect>( snek.mCollider, i->mCollider ) )
			{
				quit = true;
				std::cout << "Score: " << gScore << std::endl;
			}
		}

		if( snek.SelfCollide() )
		{
			quit = true;
			std::cout << "Score: " << gScore << std::endl;
		}
	
		snek.Move();

		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
				quit = true;
			if( e.type == SDL_KEYDOWN )
			{
				if( e.key.keysym.sym == SDLK_p )
					snek.Push();
				else if( e.key.keysym.sym == SDLK_w )
				{
					if( snek.mDir != SOUTH )
						snek.mDir = NORTH;
				}
				else if( e.key.keysym.sym == SDLK_s )
				{
					if( snek.mDir != NORTH )
						snek.mDir = SOUTH;
				}
				else if( e.key.keysym.sym == SDLK_d )
				{
					if( snek.mDir != WEST )
						snek.mDir = EAST;
				}
				else if( e.key.keysym.sym == SDLK_a )
				{
					if( snek.mDir != EAST )
						snek.mDir = WEST;
				}
				else if( e.key.keysym.sym == SDLK_ESCAPE )
					quit = true;
			}
	    
		}
		SDL_Flip( screen );
		++frame;

		if( cap && fps.get_ticks() < ( 1000 / frames_per_second ) )
		{
			SDL_Delay( ( 1000 / frames_per_second ) - fps.get_ticks() );
		}
    }

    delete food;
    SDL_Quit();
    return 0;
}
