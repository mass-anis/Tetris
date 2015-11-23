/*
 * Piece.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: anis
 */
#include "Piece.h"

Piece::Piece(TetrisPieces typ, int xx, int yy,SDL_Renderer *Ren):x(xx),y(yy),gRenderer(Ren){
	type=typ;
	switch(type)
	{
		case Tetris_I:
			color = {0x00,0xFF,0xFF,0xFF};
			blocks.push_back(Block(x,y,gRenderer,color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer,color));
			blocks.push_back(Block(x,y+2*Block::Blocksize,gRenderer,color));
			blocks.push_back(Block(x,y+3*Block::Blocksize,gRenderer,color));
			break;
		case Tetris_J:
			color = {0x00,0x00,0xFF,0xFF};
			blocks.push_back(Block(x+Block::Blocksize,y,gRenderer, color));
			blocks.push_back(Block(x,y,gRenderer, color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x,y+2*Block::Blocksize,gRenderer, color));
			break;
		case Tetris_L:
			color = {0xFF,0xA5,0x00,0xFF};
			blocks.push_back(Block(x-Block::Blocksize,y,gRenderer, color));
			blocks.push_back(Block(x,y,gRenderer, color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x,y+2*Block::Blocksize,gRenderer, color));
			break;
		case Tetris_O:
			color = {0x00,0xFF,0x00,0xFF};
			blocks.push_back(Block(x,y,gRenderer, color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y+Block::Blocksize,gRenderer, color));
			break;
		case Tetris_S:
			color = {0xAA,0x00,0xFF,0xFF};
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x+2*Block::Blocksize,y,gRenderer, color));
			break;
		case Tetris_T:
			color = {0x00,0xFF,0xFF,0xFF};
			blocks.push_back(Block(x,y,gRenderer, color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x,y+2*Block::Blocksize,gRenderer, color));
			break;
		case Tetris_Z:
			color = {0xFF,0x00,0x00,0xFF};
			blocks.push_back(Block(x+Block::Blocksize,y,gRenderer, color));
			blocks.push_back(Block(x,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x+Block::Blocksize,y+Block::Blocksize,gRenderer, color));
			blocks.push_back(Block(x,y+2*Block::Blocksize,gRenderer, color));
			break;
	}
}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

void Piece::Draw(){
	// call member function draw() for each element
    for_each (blocks.begin(), blocks.end(), std::mem_fun_ref(&Block::Draw));
}

void Piece::Move(int dx,int dy){
	x+=dx;
	y+=dy;
	// call member function Move() for each element
	for(unsigned int i=0;i<blocks.size();i++)
	{
		blocks[i].Move(dx,dy);
	}
}

void Piece::Rotate() {
	switch(type)
	{
		case Tetris_I:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -((Block::Blocksize*2)-(blocks[i].GetY()-y));
				y1 = (blocks[i].GetX()-x)+(Block::Blocksize*2);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;

		case Tetris_J:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -(blocks[i].GetY()-y-(Block::Blocksize));
				y1 = (blocks[i].GetX()-x)+(Block::Blocksize);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;

		case Tetris_L:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -(blocks[i].GetY()-y-(Block::Blocksize));
				y1 = (blocks[i].GetX()-x)+(Block::Blocksize);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;
		case Tetris_O:
			break;

		case Tetris_S:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -(blocks[i].GetY()-y-(2*Block::Blocksize));
				y1 = (blocks[i].GetX()-x);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;

		case Tetris_T:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -(blocks[i].GetY()-y-(Block::Blocksize));
				y1 = (blocks[i].GetX()-x)+(Block::Blocksize);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;

		case Tetris_Z:
			for(unsigned int i=0;i<blocks.size();i++)
			{
				int x1,y1;
				x1 = -(blocks[i].GetY()-y-(Block::Blocksize));
				y1 = (blocks[i].GetX()-x)+(Block::Blocksize);
				blocks[i].MoveTo(x+x1,y+y1);
			}
			break;
	}
}
