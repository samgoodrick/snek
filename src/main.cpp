#include "SDL/SDL.h"
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include "snek.hpp"
#include "globals.hpp"

struct Food
{
    Food()
	:texture( SDL_LoadBMP( "../img/snek.bmp" ) )
    {
	x = (rand() % 640);
	y = (rand() % 480);

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
    ~Food()
    {
	SDL_FreeSurface( texture );
    }
    void Render( SDL_Surface* screen )
    {
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( texture, NULL, screen, &offset ); 
    }
    int x;
    int y;
    SDL_Surface* texture;
    SDL_Rect Collider;
    SDL_Rect offset;
};

bool Collision_With_Food( SnekList& snek, Food* food )
{
    int leftA, leftB;
    int rightA, rightB;
    int bottomA, bottomB;
    int topA, topB;

    leftA = snek.Collider.x;
    rightA = snek.Collider.x + snek.Collider.w;
    topA = snek.Collider.y;
    bottomA = snek.Collider.y + snek.Collider.w;

    leftB = food->Collider.x;
    rightB = food->Collider.x + food->Collider.w;
    topB = food->Collider.y;
    bottomB = food->Collider.y + food->Collider.w;

    if( bottomA <= topB ||
	    topA >= bottomB ||
	    rightA <= leftB ||
	    leftA >= rightB )
	return false;
    return true;
}


int main( int argc, char** argv )
{
    srand( time( NULL ) );
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_Surface* background = SDL_LoadBMP( "../img/background.bmp" );
    SDL_BlitSurface( background, NULL, screen, NULL );
    SDL_Flip( screen );
    SDL_Event e;
    bool quit = false;
    SnekList list;

    SDL_Surface* vert = SDL_LoadBMP( "../img/vert.bmp" );
    SDL_Surface* horiz = SDL_LoadBMP( "../img/horiz.bmp" );

    std::vector<SDL_Rect> vert_offsets;
    for( int i = 0; i < 480; i+=16 )
    {
	SDL_Rect offset;
	offset.x = 0;
	offset.y = i;
    }
    std::vector<SDL_Rect> horiz_offsets;
    for( int i = 0; i < 640; i+=16 )
    {
	SDL_Rect offset;
	offset.x = i;
	offset.y = 0;
    }
    
    bool is_food = true;
    auto food = new Food;

    while( !quit )
    {
	SDL_BlitSurface( background, NULL, screen, NULL );
	for( auto& i : vert_offsets )
	    SDL_BlitSurface( vert, NULL, screen, &i );
	for( auto& i : horiz_offsets )
	    SDL_BlitSurface( horiz, NULL, screen, &i );

	list.renderlist( screen );
	food->Render( screen );
	SDL_Flip( screen );
	list.move();

	if( !is_food )
	{
	    food = new Food;
	    is_food = true;
	}
	while( SDL_PollEvent( &e ) )
	{
	    if( e.type == SDL_QUIT )
		quit = true;
	    if( e.type == SDL_KEYDOWN )
	    {
		if( e.key.keysym.sym == SDLK_p )
		    list.push();
		else if( e.key.keysym.sym == SDLK_UP )
		    list.mDir = NORTH;
		else if( e.key.keysym.sym == SDLK_DOWN )
		    list.mDir = SOUTH;
		else if( e.key.keysym.sym == SDLK_RIGHT )
		    list.mDir = EAST;
		else if( e.key.keysym.sym == SDLK_LEFT )
		    list.mDir = WEST;
		else if( e.key.keysym.sym == SDLK_ESCAPE )
		    quit = true;
	    }
	    
	}
	if( Collision_With_Food( list, food ) )
	{
	    SDL_Delay( 1 );
	    delete food;
	    list.push();
	    is_food = false;
	}
	list.self_collision();
	SDL_Delay( 100 );
    }

    SDL_Quit();
    return 0;
}
