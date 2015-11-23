/*
 * Block.h
 *
 *  Created on: Nov 19, 2015
 *      Author: anis
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include <SDL2/SDL.h>

class Block {
private:
	int x;
	int y;
	SDL_Renderer *gRenderer;
	SDL_Color color;
public:
	static int Blocksize;
	Block(int xx, int yy,SDL_Renderer *Ren, SDL_Color col);
	virtual ~Block();
	const int GetX()const{return x;};
	const int GetY()const{return y;};
	void Move(int dx,int dy);
	void MoveTo(int x,int y);
	void Draw();
	bool operator<(Block const & R)const {
			if(y > R.GetY())
				return true;
			else if(y == R.GetY())
				return (x < R.GetX());
			else
				return false;
		}
};

#endif /* BLOCK_H_ */
