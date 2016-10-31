#ifndef SNEK_HPP
#define SNEK_HPP

#include "SDL/SDL.h"
#include "collision.hpp"
#include "globals.hpp"
#include <cassert>
#include <cmath>
#include <vector>

class Node
{
public:
    Node( int px, int py );
    SDL_Rect mCollider;
    SDL_Rect mOffset;
    int x, y;
};

class Snek
{
public:
    Snek();
    ~Snek();
    void Push();
    void Render( SDL_Surface* screen );
    void Move();
    SDL_Rect GetCollider();
    bool SelfCollide();
    
    DIRECTION mDir;
    SDL_Rect mCollider;
private:
    std::vector<Node*> Snake;
    SDL_Surface* mTexture;
    Node* head;
};


struct SnekNode
{
    SnekNode()
	:next(), prev(), x(), y(), texture( SDL_LoadBMP( "../img/snek.bmp" ) )
    {
	offset.w = offset.h = 16;
	Collider.x = Collider.y = 0;
	Collider.w = Collider.h = 16;
    }
    ~SnekNode()
    {
	SDL_FreeSurface( texture );
    }
    void Render( SDL_Surface* screen )
    {
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( texture, NULL, screen, &offset ); 
    }
    SnekNode* next;
    SnekNode* prev;
    SDL_Surface* texture;
    int x;
    int y;
    SDL_Rect offset;
    SDL_Rect Collider;
};

// class SnekList
// {
// public:
//     SnekNode* head;
//     SnekNode* tail;
//     SnekList()
// 	:head( new SnekNode ), tail( head ), mDir( EAST )
//     {
// 	head->x = tail->x = 640/2 - floor(log2(640));
// 	head->y = tail->y = 480/2 - floor(log2(640));
// 	Collider.x = head->x;
// 	Collider.y = head->y;
// 	Collider.w = 16;
// 	Collider.h = 16;
//     }
//     ~SnekList()
//     {
// 	while( tail )
// 	{
// 	    SnekNode* newtail = tail->prev;
// 	    pop();
// 	    tail = newtail;
// 	}
//     }
//     void push()
//     {
// 	SnekNode* temptail = new SnekNode;
// 	temptail->prev = tail;
// 	tail->next = temptail;
// 	tail = temptail;

// 	tail->x = tail->prev->x + 16;
// 	tail->y = tail->prev->y;
// 	tail->Collider.x = tail->x;
// 	tail->Collider.y = tail->y;
//     }
//     void move()
//     {
// 	SnekNode* visitor = head;
// 	std::vector<std::pair<int,int>> positions;
// 	while( visitor )
// 	{
// 	    positions.push_back( std::make_pair( visitor->x, visitor->y ) );
// 	    visitor = visitor->next;
// 	}
// 	visitor = head->next;
// 	switch( mDir )
// 	{
// 	case NORTH:
// 	    head->y -= 16;
// 	    break;
// 	case SOUTH:
// 	    head->y += 16;
// 	    break;
// 	case EAST:
// 	    head->x += 16;
// 	    break;
// 	case WEST:
// 	    head->x -= 16;
// 	    break;
// 	}
// ]
// 	for( int i = 0; visitor; ++i )
// 	{
// 	    visitor->x = positions[i].first;
// 	    visitor->y = positions[i].second;
// 	    visitor = visitor->next;
// 	}
// 	Collider.x = head->x;
// 	Collider.y = head->y;

//     }
//     void pop()
//     {
// 	SnekNode* tempnext = nullptr;
// 	if( head != tail )
// 	{
// 	    tempnext = tail->prev;
// 	}
// 	delete tail;
// 	tail = tempnext;
	
//     }
//     void renderlist( SDL_Surface* screen )
//     {
// 	SnekNode* visitor = head;
// 	while( visitor )
// 	{
// 	    visitor->Render( screen );
// 	    visitor = visitor->next;
// 	}
//     }
//     void updatepositions()
//     {
// 	SnekNode* visitor = tail;
// 	while( visitor )
// 	{
// 	    visitor->y += 16;
// 	    visitor = visitor->prev;
// 	}
//     }
//     void self_collision()
//     {
// 	SnekNode* visitor = head->next;
// 	while( visitor )
// 	{
// 	    if( Collision( head->Collider, visitor->Collider ) )
// 		assert( true );
// 	    visitor = visitor->next;
// 	}
//     }

//     DIRECTION mDir;
//     SDL_Rect Collider;
// };


#endif
