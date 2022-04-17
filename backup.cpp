/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <vector>



//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

//The player1 that will move around on the screen
class Player1
{
    public:
		//The dimensions of the player1
		static const int PLAYER1_WIDTH = 20;
		static const int PLAYER1_HEIGHT = 15;

		//Maximum axis velocity of the player1
		static const int PLAYER1_VEL = 2;

		//Initializes the variables
		Player1();

		//Takes key presses and adjusts the player1's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player1
		void move(std::vector<SDL_Rect> wall_vec);

		//Shows the player1 on the screen
		void render();

		int getMap();

		std::vector<SDL_Rect> get_walls();

    private:
		//The X and Y offsets of the player1
		int mPosX, mPosY;

		//The velocity of the player1
		int mVelX, mVelY;

		int mMap;
		//Dot's collision box
		SDL_Rect mCollider;
};

//The player1 that will move around on the screen
// class Player2
// {
//     public:
// 		//The dimensions of the player1
// 		static const int PLAYER2_WIDTH = 20;
// 		static const int PLAYER2_HEIGHT = 15;

// 		//Maximum axis velocity of the player1
// 		static const int PLAYER2_VEL = 2;

// 		//Initializes the variables
// 		Player2();

// 		//Takes key presses and adjusts the player1's velocity
// 		void handleEvent( SDL_Event& e );

// 		//Moves the player1
// 		void move(std::vector<SDL_Rect>& wall_vec);

// 		//Shows the player1 on the screen
// 		void render();

//     private:
// 		//The X and Y offsets of the player1
// 		int mPosX, mPosY;

// 		//The velocity of the player1
// 		int mVelX, mVelY;

// 		//Dot's collision box
// 		SDL_Rect mCollider;
// };


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool checkCollision( SDL_Rect a, std::vector<SDL_Rect> wall_vec );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPlayer1Texture;
// LTexture gPlayer2Texture;
//Map textures
LTexture gmap1Texture;
LTexture gmap2Texture;
LTexture gmap3Texture;
LTexture gmap4Texture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else if (path=="map1.png" || path == "map2.png" || path == "map3.png" || path == "map4.png")
		{
			//Get image dimensions
			//Get image dimensions
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w/30;
			mHeight = loadedSurface->h/30;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

// #if defined(SDL_TTF_MAJOR_VERSION)
// bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
// {
// 	//Get rid of preexisting texture
// 	free();

// 	//Render text surface
// 	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
// 	if( textSurface != NULL )
// 	{
// 		//Create texture from surface pixels
//         mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
// 		if( mTexture == NULL )
// 		{
// 			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get image dimensions
// 			mWidth = textSurface->w;
// 			mHeight = textSurface->h;
// 		}

// 		//Get rid of old surface
// 		SDL_FreeSurface( textSurface );
// 	}
// 	else
// 	{
// 		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
// 	}

	
// 	//Return success
// 	return mTexture != NULL;
// }
// #endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


Player1::Player1()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

	//Set collision box dimension
	mCollider.w = PLAYER1_WIDTH;
	mCollider.h = PLAYER1_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

void Player1::handleEvent( SDL_Event& e )
{

	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && (abs(mPosX - ((409*10)/7)) < 5) && (abs(mPosY - (409*10)/7)) < 5)

        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PLAYER1_VEL; break;
            case SDLK_DOWN: mPosY = 0; mVelY = 0; break;
            case SDLK_LEFT: mVelX = 0; break;
            case SDLK_RIGHT: mVelX = 0; break;
			std::cout<<"hello"<<std::endl;
        }

	else if( e.type == SDL_KEYUP && e.key.repeat == 0 && (mPosX > 10) && (mPosY > 10))

        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PLAYER1_VEL; break;
            case SDLK_DOWN: mPosY = 0; mVelY = 0; mMap = 2; break;
            case SDLK_LEFT: mVelX = 0; break;
            case SDLK_RIGHT: mVelX = 0; break;
        }
    //If a key was pressed
	else if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PLAYER1_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER1_VEL; break;
            case SDLK_LEFT: mVelX -= PLAYER1_VEL; break;
            case SDLK_RIGHT: mVelX += PLAYER1_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PLAYER1_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER1_VEL; break;
            case SDLK_LEFT: mVelX += PLAYER1_VEL; break;
            case SDLK_RIGHT: mVelX -= PLAYER1_VEL; break;
        }
    }


}
// void Player2::handleEvent( SDL_Event& e )
// {
//     //If a key was pressed
// 	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
//     {
//         //Adjust the velocity
//         switch( e.key.keysym.sym )
//         {
//             case SDLK_w: mVelY -= PLAYER2_VEL; break;
//             case SDLK_s: mVelY += PLAYER2_VEL; break;
//             case SDLK_a: mVelX -= PLAYER2_VEL; break;
//             case SDLK_d: mVelX += PLAYER2_VEL; break;
//         }
//     }
//     //If a key was released
//     else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
//     {
//         //Adjust the velocity
//         switch( e.key.keysym.sym )
//         {
//             case SDLK_w: mVelY += PLAYER2_VEL; break;
//             case SDLK_s: mVelY -= PLAYER2_VEL; break;
//             case SDLK_a: mVelX += PLAYER2_VEL; break;
//             case SDLK_d: mVelX -= PLAYER2_VEL; break;
//         }
//     }
// }

void Player1::move(std::vector<SDL_Rect> wall_vec )
{
	//Collision with a wall
    //Move the player1 left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

    //If the player1 went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PLAYER1_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall_vec ))
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    //Move the player1 up or down
    mPosY += mVelY;
	mCollider.y = mPosY;

    //If the player1 went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PLAYER1_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall_vec ))
    {
        //Move back
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
}	

// void Player2::move(std::vector<SDL_Rect>& wall_vec )
// {
// 	//Move the player2 left or right
// 	mPosX += mVelX;
// 	mCollider.x = mPosX;

// 	//If the player2 went too far to the left or right
// 	if( ( mPosX < 0 ) || ( mPosX + PLAYER2_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall_vec ))
// 	{
// 		//Move back
// 		mPosX -= mVelX;
// 		mCollider.x = mPosX;
// 	}

// 	//Move the player2 up or down
// 	mPosY += mVelY;
// 	mCollider.y = mPosY;

// 	//If the player2 went too far up or down
// 	if( ( mPosY < 0 ) || ( mPosY + PLAYER2_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall_vec ))
// 	{
// 		//Move back
// 		mPosY -= mVelY;
// 		mCollider.y = mPosY;
// 	}
// }

void Player1::render()
{
    //Show the player1
	gPlayer1Texture.render( mPosX, mPosY );
}

int Player1::getMap()
{
	return mMap;
}
// void Player2::render()
// {
//     //Show the player2
// 	gPlayer2Texture.render( mPosX, mPosY );
// }

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load player1 texture
	if( !gPlayer1Texture.loadFromFile( "player1.png" ) )
	{
		printf( "Failed to load player1 texture!\n" );
		success = false;
	}
	// if( !gPlayer2Texture.loadFromFile( "player2.png" ) )
	// {
	// 	printf( "Failed to load player2 texture!\n" );
	// 	success = false;
	// }

	if( !gmap1Texture.loadFromFile( "map1.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap2Texture.loadFromFile( "map2.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap3Texture.loadFromFile( "map3.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap4Texture.loadFromFile( "map4.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPlayer1Texture.free();

	// gPlayer2Texture.free();
	gmap1Texture.free();
	gmap2Texture.free();
	gmap3Texture.free();
	gmap4Texture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, std::vector<SDL_Rect> wall_vec )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the AABB of player1
	for( int i = 0; i < wall_vec.size(); ++i )
	{
		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = wall_vec[i].x;
		rightB = wall_vec[i].x + wall_vec[i].w;
		topB = wall_vec[i].y;
		bottomB = wall_vec[i].y + wall_vec[i].h;

		//If any of the sides from A are outside of B
		if( bottomA <= topB )
		{
			continue;
		}

		if( topA >= bottomB )
		{
			continue;
		}

		if( rightA <= leftB )
		{
			continue;
		}

		if( leftA >= rightB )
		{
			continue;
		}

		//If none of the sides from A are outside B
		return true;
	}

	//If no collision occurred
	return false;
}


SDL_Rect wall_form( int a,int b,int c,int d )
{
	SDL_Rect wall;
	wall.x = (a*10)/7;
	wall.y = (b*10)/7;
	wall.w = ((c-a)*10)/7;
	wall.h = ((d-b)*10)/7;
	return wall;
}

std::vector<SDL_Rect> Player1::get_walls(){
	if(mMap==1){
		//St the wall
		std::vector<SDL_Rect> wall_vec;
		SDL_Rect wall1 = wall_form(35,61,173,184);
		wall_vec.push_back(wall1);
		SDL_Rect wall2 = wall_form(35,187,138,199);
		wall_vec.push_back(wall2);
		SDL_Rect wall3 = wall_form(35,199,143,244);
		wall_vec.push_back(wall3);
		SDL_Rect wall4 = wall_form(193,61,326,244);
		wall_vec.push_back(wall4);
		SDL_Rect wall5 = wall_form(326,61,336,215);
		wall_vec.push_back(wall5);
		SDL_Rect wall6 = wall_form(336,61,648,215);
		wall_vec.push_back(wall6);
		SDL_Rect wall7 = wall_form(671,28,700,420);
		wall_vec.push_back(wall7);
		SDL_Rect wall8 = wall_form(659,276,671,375);
		wall_vec.push_back(wall8);
		SDL_Rect wall9 = wall_form(418,378,700,420);
		wall_vec.push_back(wall9);
		SDL_Rect wall10 = wall_form(1,378,399,417);
		wall_vec.push_back(wall10);
		SDL_Rect wall11 = wall_form(1,28,17,378);
		wall_vec.push_back(wall11);
		SDL_Rect wall12 = wall_form(35,260,162,359);
		wall_vec.push_back(wall12);
		return wall_vec;
	}
	else{
		std::vector<SDL_Rect> wall_vec(0);
		return wall_vec;
	}
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The player1 that will be moving around on the screen
			Player1 player1;
			// Player2 player2;			

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the player1
					player1.handleEvent( e );
					// player2.handleEvent( e );
				}

				//Move the player1
				player1.move(player1.get_walls());
				// player2.move(wall_vec);

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );	
				//Render objects
				if(player1.getMap() == 1)
				{
					gmap1Texture.render( 0, 0 );
				}
				else if(player1.getMap() == 2)
				{
					gmap2Texture.render( 0, 0 );
				}
				else if(player1.getMap() == 3)
				{
					gmap3Texture.render( 0, 0 );
				}
				else if(player1.getMap() == 4)
				{
					gmap4Texture.render( 0, 0 );
				}
				
				player1.render();
				// player2.render();

				//Update screen
				SDL_RenderPresent( gRenderer );
				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
