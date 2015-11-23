/****************************************************************************************
    Copyright (c) 2015 Mohamed Anis Messaoud



    Author: Messaoud Mohamed Anis
    Email: medanis.messaoud@gmail.com
*****************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <cmath>
#include "Block.h"
#include "Piece.h"
#include <time.h>       /* time */
#include <SDL/SDL_ttf.h>


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
//Timer callback function
Uint32 callback( Uint32 interval, void* param );
int score=0;
bool checkBlockCollision( const Block &B1, const Block &B2);
bool checkEdgeCollision();
bool CheckCollision();
void DisplayText( std::string textureText,int x,int y,SDL_Color textColor );

Piece *CurPiece;
std::vector<Block> blocks; //blocks available on the map
SDL_Renderer *gRenderer;
SDL_Rect outlineRect = { Block::Blocksize-1, Block::Blocksize-1, Block::Blocksize*10+1, Block::Blocksize*30+1 };
TTF_Font* Sans;

int main ( int argc, char** argv )
{
	/* initialize random seed: */
	  srand (time(NULL));

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    /*//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return 1;
	}

	 Sans = TTF_OpenFont("lazy.ttf", 28);
	if( Sans == NULL )
	{
		printf( "Unable to open Font! SDL Error: %s\n", SDL_GetError() );
	}*/

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    // create a new window
    SDL_Window *win = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    gRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool quit = false;	//Main loop flag
    SDL_Event e;	//Event handler

    CurPiece= new Piece(static_cast<TetrisPieces>(rand()%7),80,Block::Blocksize,gRenderer); //currently existing piece
    //blocks.push_back(Block(Block::Blocksize*5,Block::Blocksize*10,gRenderer,{100,80,70,0xFF}));

    //Set callback
    SDL_TimerID timerID = SDL_AddTimer( 1000, callback,NULL);

    while( !quit )	//While application is running
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ))
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }//User presses a key
            else if( e.type == SDL_KEYDOWN )
            {
				if(e.key.keysym.sym == SDLK_LEFT)
				{
					CurPiece->Move(-Block::Blocksize,0);
					if(checkEdgeCollision()||CheckCollision())
						CurPiece->Move(Block::Blocksize,0);
				}
				if(e.key.keysym.sym == SDLK_RIGHT)
				{
					CurPiece->Move(Block::Blocksize,0);
					if(checkEdgeCollision()||CheckCollision())
						CurPiece->Move(-Block::Blocksize,0);
				}
				if(e.key.keysym.sym == SDLK_DOWN)
				{
					CurPiece->Move(0,Block::Blocksize);
					if(checkEdgeCollision()||CheckCollision())
						CurPiece->Move(0,-Block::Blocksize);
				}
				if(e.key.keysym.sym == SDLK_SPACE)
				{
					CurPiece->Rotate();
				}
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //DisplayText("score:",outlineRect.w+outlineRect.x+20,50,{0x00,0x00,0x00,0xFF});
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( gRenderer, &outlineRect );

		for_each (blocks.begin(), blocks.end(), std::mem_fun_ref(&Block::Draw));
		CurPiece->Draw();
        //Update screen
        SDL_RenderPresent( gRenderer );
        //SDL_Delay(100);
    }

    delete CurPiece;

    //Free global font
	TTF_CloseFont( Sans );

    //Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( win );

	SDL_RemoveTimer( timerID );
	//Quit SDL subsystems
	SDL_Quit();
    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}


Uint32 callback( Uint32 interval, void* param )
{

	CurPiece->Move(0,Block::Blocksize);
	//check collision
	bool Collision =CheckCollision();

	if(Collision)
	{
		CurPiece->Move(0,-Block::Blocksize);
		blocks.insert(blocks.end(),CurPiece->GetBlocks().begin(),CurPiece->GetBlocks().end());
		delete CurPiece;
		CurPiece= new Piece(static_cast<TetrisPieces>(rand()%7),80,Block::Blocksize,gRenderer);
		//check for complete lines
		std::sort(blocks.begin(),blocks.end());
		int Line=1,y=blocks[0].GetY();
		bool done = false;
		int Mul=0;//score multiplier
		while(!done)
		{
			done =true;
			Mul++;
			for(unsigned int i=1;i<blocks.size();i++)
			{
				if(blocks[i].GetY()== y)
				{
					Line++;
					if(Line == outlineRect.w/Block::Blocksize)//full line
					{
						blocks.erase(blocks.begin()+i-9,blocks.begin()+i+1);
						score +=10*Mul;
						if(blocks.size()==0)
							score+=100;
						for(unsigned int j=i-9;j<blocks.size();j++)
							blocks[j].Move(0,Block::Blocksize);
						done = false;
						std::cout << score <<std::endl;
						break;
					}
				}
				else
				{
					y = blocks[i].GetY();
					Line =1;
				}
			}
		}
	}
    return 300;//next period
}



//check collision between blocks and bottom edges
bool CheckCollision()
{
	bool Collision=false;
	for(unsigned int i=0; i< CurPiece->GetBlocks().size();i++ )
	{
		Block B1 = CurPiece->GetBlocks()[i];
		Collision |= (B1.GetY() >= (outlineRect.y+outlineRect.h));
		for(unsigned int j=0; j< blocks.size();j++ )
		{
			if(checkBlockCollision(B1,blocks[j]))
			{
				Collision = true;
				break;
			}
			if(Collision)
				break;
		}
	}
	return Collision;
}

//check collision between two blocks
bool checkBlockCollision( const Block &B1, const Block &B2)
{
	bool Collision=false;
	Collision = (abs(B1.GetX()-B2.GetX())<Block::Blocksize) && (abs(B1.GetY()-B2.GetY())<Block::Blocksize);
	return Collision;
}

//check left and right edge collision
bool checkEdgeCollision()
{
	bool Collision=false;
	for(unsigned int i=0; i< CurPiece->GetBlocks().size();i++ )
	{
		Block B1 = CurPiece->GetBlocks()[i];
		Collision |= (B1.GetX()<= outlineRect.x) || (B1.GetX()>=(outlineRect.x+outlineRect.w));
		//Collision |= (B1.GetY() >= (outlineRect.y+outlineRect.h));
	}
	return Collision;
}

void DisplayText( std::string textureText,int x, int y, SDL_Color textColor )
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( Sans, "aabbc", textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
    	SDL_Texture* Message = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( Message == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
        	SDL_Rect Message_rect; //create a rect
        	Message_rect.x = x;  //controls the rect's x coordinate
        	Message_rect.y = y; // controls the rect's y coordinte
        	Message_rect.w = x+textSurface->w; // controls the width of the rect
        	Message_rect.h = y+textSurface->h; // controls the height of the rect

        	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

}
