/*
 * Piece.h
 *
 *  Created on: Nov 19, 2015
 *      Author: anis
 */

#ifndef PIECE_H_
#define PIECE_H_
#include <vector>
#include <iostream>
#include <algorithm>
#include "Block.h"

enum TetrisPieces{
	Tetris_I,Tetris_J,Tetris_L,Tetris_O,Tetris_S,Tetris_T,Tetris_Z
};

class Piece {
	int x;
	int y;
	SDL_Color color;
	SDL_Renderer *gRenderer;
	TetrisPieces type;
	std::vector<Block> blocks;
public:
	Piece(TetrisPieces typ, int xx, int yy,SDL_Renderer *Ren);
	~Piece();
	const int GetX()const{return x;};
	const int GetY()const{return y;};
	const std::vector<Block>& GetBlocks()const{return blocks;};
	void Draw();
	void Move(int dx,int dy);
	void Rotate();
};

#endif /* PIECE_H_ */
