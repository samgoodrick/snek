#include "SDL/SDL.h"
#include <vector>
#include <utility>

enum DIRECTION {
    NORTH,
    WEST,
    SOUTH,
    EAST
};

struct SnekNode
{
    SnekNode()
	:next(), prev(), x(), y(), texture( SDL_LoadBMP( "../img/snek.bmp" ) )
    {
    }
    void Render( SDL_Surface* screen )
    {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( texture, NULL, screen, &offset ); 
    }
    SnekNode* next;
    SnekNode* prev;
    SDL_Surface* texture;
    int x;
    int y;
};

class SnekList
{
    SnekNode* head;
    SnekNode* tail;
public:
    SnekList()
	:head( new SnekNode ), tail( head ), mDir( EAST )
    {
	head->x = tail->x = 640/2;
	head->y = tail->y = 480/2;
    }
    ~SnekList()
    {
	while( tail )
	{
	    SnekNode* newtail = tail->prev;
	    pop();
	    tail = newtail;
	}
    }
    void push()
    {
	SnekNode* temptail = new SnekNode;
	temptail->prev = tail;
	tail->next = temptail;
	tail = temptail;

	tail->x = tail->prev->x + 16;
	tail->y = tail->prev->y;
    }
    void move()
    {
	SnekNode* visitor = head;
	std::vector<std::pair<int,int>> positions;
	while( visitor )
	{
	    positions.push_back( std::make_pair( visitor->x, visitor->y ) );
	    visitor = visitor->next;
	}
	visitor = head->next;
	switch( mDir )
	{
	case NORTH:
	    head->y -= 16;
	    break;
	case SOUTH:
	    head->y += 16;
	    break;
	case EAST:
	    head->x += 16;
	    break;
	case WEST:
	    head->x -= 16;
	    break;
	}

	for( int i = 0; visitor; ++i )
	{
	    visitor->x = positions[i].first;
	    visitor->y = positions[i].second;
	    visitor = visitor->next;
	}

    }
    void pop()
    {
	SnekNode* tempnext = nullptr;
	if( head != tail )
	{
	    tempnext = tail->prev;
	}
	delete tail;
	tail = tempnext;
	
    }
    void renderlist( SDL_Surface* screen )
    {
	SnekNode* visitor = head;
	while( visitor )
	{
	    visitor->Render( screen );
	    visitor = visitor->next;
	}
    }
    void updatepositions()
    {
	SnekNode* visitor = tail;
	while( visitor )
	{
	    visitor->y += 16;
	    visitor = visitor->prev;
	}
    }

    DIRECTION mDir;
};

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_Surface* background = SDL_LoadBMP( "../img/background.bmp" );
    SDL_BlitSurface( background, NULL, screen, NULL );
    SDL_Flip( screen );
    SDL_Event e;
    bool quit = false;
    SnekList list;
    for( int i = 0; i < 5; ++i )
	list.push();

    while( !quit )
    {
	SDL_BlitSurface( background, NULL, screen, NULL );
	list.renderlist( screen );
	SDL_Flip( screen );
	list.move();
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
	SDL_Delay( 100 );
    }

    SDL_Quit();
    return 0;
}
