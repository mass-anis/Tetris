/*
 * Block.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: anis
 */

#include "Block.h"

int Block::Blocksize=20;

Block::Block(int xx, int yy,SDL_Renderer *Ren, SDL_Color col):x(xx),y(yy),gRenderer(Ren),color(col){

}

Block::~Block() {

}

void Block::Draw(){
	//Render filled square
	SDL_Rect fillRect = { x+1, y+1, Blocksize-1, Blocksize-1 };
	SDL_SetRenderDrawColor( gRenderer, color.r,color.g,color.b,color.a);
	SDL_RenderFillRect( gRenderer, &fillRect );

	//Render outline square
	SDL_Rect outlineRect = { x, y, Blocksize, Blocksize };
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( gRenderer, &outlineRect );
}

void Block::Move(int dx,int dy){
	x+=dx;
	y+=dy;
}

void Block::MoveTo(int x,int y)
{
	this->x=x;
	this->y=y;
}
