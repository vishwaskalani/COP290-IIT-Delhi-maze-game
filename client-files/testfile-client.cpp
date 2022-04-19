/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
// #include "client.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include "client.h"
#include "classfiles/player2.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
char* mybuff;

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
		int PLAYER1_VEL = 4;

		//Initializes the variables
		Player1();

		//Takes key presses and adjusts the player1's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player1
		void move(std::vector<SDL_Rect> wall_vec);
		void update_health(float amount);
		void update_acad(float amount);
		void update_enjoy(float amount);
		void update_vel();
		void update_money(float amount);

		//Shows the player1 on the screen
		void render();

		int getMap();
		int getXcord();
		int getYcord();
		int getHealth();
		int getAcad();
		int getEnjoy();
		int getMoney();
		bool getYulu();
		bool getsac_act();
		bool gethours();
		bool getwinAt();

		std::vector<SDL_Rect> get_walls();
		// std::vector<std::vector<int>> get_health_incr_areas();

    private:
		//The X and Y offsets of the player1
		float health_index,acadStatus,enjoyment_index,money;

		bool sac_act,hours;

		bool winAt;

		int mPosX, mPosY;

		//The velocity of the player1
		int mVelX, mVelY;

		int mMap;
		bool Yulu;
		//Dot's collision box
		SDL_Rect mCollider;
};


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
LTexture gPlayer2Texture;
//Map textures
LTexture gmap1Texture;
LTexture gminimartTexture;
LTexture glibraryTexture;
LTexture gdelhi16Texture;
LTexture gmap2Texture;
LTexture gmap3Texture;
LTexture gmap4Texture;
LTexture gmap5Texture;
LTexture gathelticsTexture;
LTexture gmaingroundTexture;
LTexture gamulTexture;
LTexture gsacTexture;
LTexture gsac1Texture;
LTexture gsac2Texture;
LTexture gsac3Texture;
LTexture glhcTexture;
LTexture ghospTexture;
LTexture gbankTexture;
LTexture gstartTexture;
LTexture gyuluTexture;
LTexture gbackTexture;
LTexture gloseTexture;
LTexture gmg1Texture;
LTexture gmg2Texture;
LTexture gmg3Texture;
//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

SDL_Color TextColor = { 255, 255, 255, 255}; // Red SDL color.
TTF_Font* Font; // The font to be loaded from the ttf file.
SDL_Surface* TextSurface; // The surface necessary to create the font texture.
SDL_Texture* TextTexture; // The font texture prepared for render.
SDL_Rect TextRect1; // Text rectangle area with the position for the texture text.
SDL_Rect TextRect2; // Text rectangle area with the position for the texture text.
SDL_Rect TextRect3; // Text rectangle area with the position for the texture text.

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

Player1::Player1()
{
    //Initialize the offsets
    mPosX = 44;
    mPosY = 63;
	health_index = 30.0;
	enjoyment_index = 20.0;
	acadStatus = 20.0;
	money = 100.0;
	Yulu = false;
	winAt = false;
	sac_act = false;
	hours = false;

	//Set collision box dimension
	mCollider.w = PLAYER1_WIDTH;
	mCollider.h = PLAYER1_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
	mMap = 0;		
}

Player2::Player2()
{
    //Initialize the offsets
    mPosX = 44;
    mPosY = 63;
	health_index = 30.0;
	enjoyment_index = 20.0;
	acadStatus = 20.0;
	money = 100.0;    //Initialize the velocity
	mMap = 0;		
	winAt = false;
}

void Player1::handleEvent( SDL_Event& e )
{
	// if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && (mPosX <= 400) && (mPosY <= 500) && (mPosX>=300) && (mPosY>=400))
	// {
	// 	switch( e.key.keysym.sym ){
	// 		case SDLK_e: mMap = 2; break;
	// 	}
	// }

	//If a key was pressed
	if( e.type == SDL_KEYDOWN)
    {
		//starting the game
		if ((mMap == 0)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 1;
							break;
						}
			}
		//negative health to hospital
		if ((mMap != 0) && health_index < 0){
				switch( e.key.keysym.sym ){
							case SDLK_a: 
							mMap = 14;
							mPosX = 0;
							mPosY = 0;
							Yulu = false;
							PLAYER1_VEL =4;
							break;
						}
			}
		//hospital to out
		if ((mMap == 14) && (mPosX <= 812) && (mPosX>=731) && (mPosY>=490)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 3;
							mPosX = 648; 
							mPosY = 11; 
							break;
						}
			}
		//map1 to minimart
		if ((mPosX <= 400) && (mPosY <= 520) && (mPosX>=300) && (mPosY>=400) && (money>0) && (mMap == 1)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 6;
							mPosX = 950; 
							mPosY = 400; 
							break;
						}
			}
		//minimart to map1
		if ((mPosX >=900) && (mPosY <= 500) && (mPosY>=300) && (mMap == 6)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 1;
							mPosX = 359; 
							mPosY = 463; 
							break;
						}
			}
		//map2 to DELHI16
		if ((mPosX >=680) && (mPosX <= 790) && (mPosY<=100) && (money>0) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 8;
							mPosX = 754; 
							mPosY = 572; 
							break;
						}
			}
		//Delhi 16 to map 2
		if ((mPosX >=718) && (mPosX <= 790) && (mPosY>=500) && (mMap == 8)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 2;
							mPosX = 720; 
							mPosY = 40; 
							break;
						}
			}
		//map2 to SAC
		if ((mPosX >=525) && (mPosX <= 590) && (mPosY<=370) && (mPosY>=300) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 21;
							mPosX = 857; 
							mPosY = 580; 
							break;
						}
			}
		//chosing events
		if ((mMap == 21)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 9;
							sac_act = true;
							break;
							case SDLK_t: 
							mMap = 22;
							break;
							case SDLK_s: 
							mMap = 23;
							break;
						}
			}
		if ((mMap == 22)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 9;
							sac_act = true;
							break;
							case SDLK_r: 
							mMap = 21;
							break;
							case SDLK_s: 
							mMap = 23;
							break;
						}
			}
		if ((mMap == 23)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 9;
							sac_act = true;
							break;
							case SDLK_t: 
							mMap = 22;
							break;
							case SDLK_r: 
							mMap = 21;
							break;
						}
			}
		//SAC to map 2
		if ((mPosX >=800) && (mPosY>=500) && (mMap == 9)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 2;
							mPosX = 540; 
							mPosY = 327; 
							break;
						}
			}
		//map3 to main ground
		if ((mPosX >=588) && (mPosX<=664) && (mPosY>=112) && (mPosY<=162) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 18;
							mPosX = 920; 
							mPosY = 560; 
							break;
						}
			}
		//chosing choice of nss , ncc , nso
		if ((mMap == 18)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 11;
							hours = true;
							break;
							case SDLK_s: 
							mMap = 19;
							break;
							case SDLK_c: 
							mMap = 20;
							break;
							// case SDLK_LEFT: 
							// mMap = 20;
							// break;
						}
			}
		if ((mMap == 19)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 11;
							hours = true;
							break;
							case SDLK_c: 
							mMap = 20;
							break;
							case SDLK_o: 
							mMap = 18;
							break;
							// case SDLK_LEFT: 
							// mMap = 18;
							// break;
						}
			}
		if ((mMap == 20)){
				switch( e.key.keysym.sym ){
							case SDLK_RETURN: 
							mMap = 11;
							hours = true;
							break;
							case SDLK_o: 
							mMap = 18;
							break;
							case SDLK_s: 
							mMap = 19;
							break;
							// case SDLK_LEFT: 
							// mMap = 19;
							// break;
						}
			}
		//main ground to map3
		if ((mPosX >=900) && (mPosY>=550) && (mMap == 11)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 3;
							mPosX = 633; 
							mPosY = 138; 
							break;
						}
			}
		//map3 to atheletic ground
		if ((mPosX >=588) && (mPosX<=664) && (mPosY>=387) && (mPosY<=420) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 12;
							mPosX = 920; 
							mPosY = 560; 
							break;
						}
			}
		//atheletic ground to map3 
		if ((mPosX >=900) && (mPosY>=550) && (mMap == 12)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 3;
							mPosX = 633; 
							mPosY = 407; 
							break;
						}
			}
		//map3 to amul
		if ((mPosX >=588) && (mPosX<=664) && (mPosY>=432) && (mPosY<=470) && (money>0) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 10;
							mPosX = 511; 
							mPosY = 563; 
							break;
						}
			}
		//amul to map3 
		if ((mPosX >=462) && (mPosY>=520) && (mPosX<=567) && (mMap == 10)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 3;
							mPosX = 640; 
							mPosY = 451; 
							break;
						}
			}
		//map3 to library
		if ((mPosX >=620) && (mPosX<=700) && (mPosY>=528) && (mPosY<=573) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 7;
							mPosX = 434; 
							mPosY = 570; 
							break;
						}
			}
		//library to map3 
		if ((mPosX >=392) && (mPosY>=520) && (mPosX<=490) && (mMap == 7)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 3;
							mPosX = 656; 
							mPosY = 554; 
							break;
						}
			}
		//map4 to bank
		if ((mPosX >=675) && (mPosX<=710) && (mPosY>=150) && (mPosY<=216) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 15;
							mPosX = 750; 
							mPosY = 578; 
							break;
						}
			}
		//bank to map4 
		if ((mPosX >=700) && (mPosY>=448) && (mPosX<=826) && (mMap == 15)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 4;
							mPosX = 680; 
							mPosY = 166; 
							break;
						}
			}
		//map4 to lhc
		if ((mPosX >=572) && (mPosX<=612) && (mPosY>=173) && (mPosY<=244) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_e: 
							mMap = 13;
							mPosX = 930; 
							mPosY = 578; 
							break;
						}
			}
		//lhc to map4 
		if ((mPosX >=850) && (mPosY>=515)  && (mMap == 13)){
				switch( e.key.keysym.sym ){
							case SDLK_o: 
							mMap = 4;
							mPosX = 580; 
							mPosY = 224; 
							break;
						}
			}
		//map 1 to map 2
		if ((mPosX >=550) && (mPosX <= 598) &&(mPosY <= 600) && (mPosY>=540) && (mMap == 1)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 2;
							mPosX = 614; 
							mPosY = 21; 
							break;
						}
			}
		//map 2 to map 1
		if ((mPosX >=578) && (mPosX <= 660) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 1;
							mPosX = 572; 
							mPosY = 555; 
							break;
						}
			}
		// map2 to map3
		if ((mPosX >=412) && (mPosX <= 461) &&(mPosY <= 600) && (mPosY>=540) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 3;
							mPosX = 450; 
							mPosY = 14; 
							break;
						}
			}
		if ((mPosX >=592) && (mPosX <= 655) &&(mPosY <= 600) && (mPosY>=540) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 3;
							mPosX = 630; 
							mPosY = 5; 
							break;
						}
			}
		if ((mPosX >=920) && (mPosX <= 1000) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 2)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 3;
							mPosX = 965; 
							mPosY = 14; 
							break;
						}
			}
		//map 3 to map 2
		if ((mPosX >=427) && (mPosX <= 500) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 2;
							mPosX = 430; 
							mPosY = 580; 
							break;
						}
			}
		if ((mPosX >=610) && (mPosX <= 680) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 2;
							mPosX = 610; 
							mPosY = 580; 
							break;
						}
			}
		if ((mPosX >=928) && (mPosX <= 1000) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 2;
							mPosX = 944; 
							mPosY = 580; 
							break;
						}
			}
		//map 3 to map 4
		if ((mPosX >=420) && (mPosX <= 496) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 4;
							mPosX = 416; 
							mPosY = 14; 
							break;
						}
			}
		if ((mPosX >=635) && (mPosX <= 723) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 4;
							mPosX = 550; 
							mPosY = 8; 
							break;
						}
			}
		if ((mPosX >=920) && (mPosX <= 1000) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 3)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 4;
							mPosX = 945; 
							mPosY = 14; 
							break;
						}
			}
		//map 4 to map 3
		if ((mPosX >=400) && (mPosX <= 463) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 3;
							mPosX = 445; 
							mPosY = 589; 
							break;
						}
			}
		if ((mPosX >=510) && (mPosX <= 600) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 3;
							mPosX = 662; 
							mPosY = 589; 
							break;
						}
			}
		if ((mPosX >=918) && (mPosX <= 1000) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 3;
							mPosX = 961; 
							mPosY = 589; 
							break;
						}
			}
		//map4 to map5
		if ((mPosX >=467) && (mPosX <= 545) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 5;
							mPosX = 461; 
							mPosY = 11; 
							break;
						}
			}
		if ((mPosX >=720) && (mPosX <= 830) &&(mPosY <= 600) && (mPosY>=550) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 5;
							mPosX = 710; 
							mPosY = 11; 
							break;
						}
			}
		if ((mPosX >=900) && (mPosX <= 1000) &&(mPosY <= 600) && (mPosY>=547) && (mMap == 4)){
				switch( e.key.keysym.sym ){
							case SDLK_DOWN: 
							mMap = 5;
							mPosX = 925; 
							mPosY = 11; 
							break;
						}
			}
		//map 5 to 4
		if ((mPosX >=440) && (mPosX <= 510) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 5)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 4;
							mPosX = 493; 
							mPosY = 580; 
							break;
						}
			}
		if ((mPosX >=684) && (mPosX <= 761) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 5)){
				switch( e.key.keysym.sym ){
							case SDLK_UP:
							mMap = 4;
							mPosX = 766; 
							mPosY = 580; 
							break;
						}
			}
		if ((mPosX >=900) && (mPosX <= 1000) &&(mPosY <= 50) && (mPosY>=0) && (mMap == 5)){
				switch( e.key.keysym.sym ){
							case SDLK_UP: 
							mMap = 4;
							mPosX = 951; 
							mPosY = 580; 
							break;
						}
			}

		//Map 4 to Yulu ride 
		if ((mPosX >=940) && (mPosX <= 980) &&(mPosY <= 465) && (mPosY>=417) && (mMap == 4) && (money>0) && (Yulu == false)){
				switch( e.key.keysym.sym ){
							case SDLK_r: 
							Yulu = true;
							PLAYER1_VEL = 8;
							break;
						}
			}
		//Map 4 to Yulu stop
		if ((mPosX >=940) && (mPosX <= 980) &&(mPosY <= 465) && (mPosY>=417) && (mMap == 4) && (Yulu == true)){
				switch( e.key.keysym.sym ){
							case SDLK_s: 
							Yulu = false;
							PLAYER1_VEL = 4;
							break;
						}
			}
		//Map 4 to Yulu ride
		if ((mPosX >=408) && (mPosX <= 450) &&(mPosY <= 367) && (mPosY>=300) && (mMap == 4) && (money>0) && (Yulu == false)){
				switch( e.key.keysym.sym ){
							case SDLK_r: 
							Yulu = true;
							PLAYER1_VEL = 8;
							break; 
						}
			}
		//Map 4 to Yulu stop
		if ((mPosX >=408) && (mPosX <= 450) &&(mPosY <= 367) && (mPosY>=300) && (mMap == 4) &&(Yulu == true)){
				switch( e.key.keysym.sym ){
							case SDLK_s: 
							Yulu = false;
							PLAYER1_VEL = 4;
							break; 
						}
			}
		//Map 1 to Yulu ride
		if ((mPosX >=14) && (mPosX <= 60) &&(mPosY <= 486) && (mPosY>=414) && (mMap == 1) && (money>0) && (Yulu == false)){
				switch( e.key.keysym.sym ){
							case SDLK_r: 
							Yulu = true;
							PLAYER1_VEL = 8;
							break; 
						}
			}
		//Map 1 to Yulu stop
		if ((mPosX >=14) && (mPosX <= 60) &&(mPosY <= 486) && (mPosY>=414) && (mMap == 1) &&(Yulu == true)){
				switch( e.key.keysym.sym ){
							case SDLK_s: 
							Yulu = false;
							PLAYER1_VEL = 4;
							break; 
						}
			}
		//Map 5 to Yulu ride
		if ((mPosX >=420) && (mPosX <= 502) &&(mPosY <= 405) && (mPosY>=367) && (mMap == 5) && (money>0) && (Yulu == false)){
				switch( e.key.keysym.sym ){
							case SDLK_r: 
							Yulu = true;
							PLAYER1_VEL = 8;
							break; 
						}
			}
		//Map 5 to Yulu stop
		if ((mPosX >=420) && (mPosX <= 502) &&(mPosY <= 405) && (mPosY>=367) && (mMap == 5) &&(Yulu == true)){
				switch( e.key.keysym.sym ){
							case SDLK_s: 
							Yulu = false;
							PLAYER1_VEL = 4;
							break; 
						}
			}
		//Map 5 to exit win
		if ((mPosX >=358) && (mPosX <= 412) && (mPosY>=570) && ( acadStatus>=50) && ( enjoyment_index>=35) && ( health_index>=45) && ( sac_act==true) && ( hours==true) && ( money>=100) && (mMap == 5)){
				switch( e.key.keysym.sym ){
							case SDLK_w: 
							winAt = true;
							mMap = 16;
							break; 
						}
			}
		//Map 5 to exit win
		if ((mPosX >=700) && (mPosX <= 746) && (mPosY>=570) && ( acadStatus>=50) && ( enjoyment_index>=35) && ( health_index>=45) && ( sac_act==true) && ( hours==true) && ( money>=100) && (mMap == 5)){
				switch( e.key.keysym.sym ){
							case SDLK_w: 
							winAt = true;
							mMap = 16;
							break; 
						}
			}

        if(e.key.repeat == 0 ){
			switch( e.key.keysym.sym )
			{
				case SDLK_UP: mVelY -= PLAYER1_VEL; break;
				case SDLK_DOWN: mVelY += PLAYER1_VEL; break;
				case SDLK_LEFT: mVelX -= PLAYER1_VEL; break;
				case SDLK_RIGHT: mVelX += PLAYER1_VEL; break;
			}
		}
        
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
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
	if(Yulu == false){
		gPlayer1Texture.render(gRenderer, mPosX, mPosY );
	}else{
		gyuluTexture.render(gRenderer, mPosX, mPosY );
	}
	
}

int Player1::getMap()
{
	return mMap;
}

int Player1::getXcord()
{
	return mPosX;
}
int Player1::getYcord()
{
	return mPosY;
}
bool Player1::getYulu()
{
	return Yulu;
}
bool Player1::getsac_act()
{
	return sac_act;
}
bool Player1::gethours()
{
	return hours;
}
bool Player1::getwinAt()
{
	return winAt;
}
// int Player1::getVel()
// {
// 	return PLAYER1_VEL;
// }

void Player1::update_health(float amount){
	health_index+=amount;
	}
// void Player1::decrease_health(){
// 	if(mMap!=14){
// 		health_index-=0.01;
// 		}	
// 	else{
// 		health_index+=0.01;
// 		}
// 	}
void Player1::update_acad(float amount){
	if(amount<0){
		if(acadStatus>0){
		acadStatus+=amount;
		}
	}	
	else{
		acadStatus+=amount;	
		}
	}
void Player1::update_enjoy(float amount){
	if(amount<0){
		if(enjoyment_index>0){
		enjoyment_index+=amount;
		}
	}	
	else{
		enjoyment_index+=amount;	
		}
	}
void Player1::update_money(float amount){
	if(amount<0){
		if(money>0){
		money+=amount;
		}
	}	
	else{
		money+=amount;	
		}
	}

int Player1::getHealth()
{
	return health_index;
}
int Player1::getAcad()
{
	return acadStatus;
}
int Player1::getEnjoy()
{
	return enjoyment_index;
}
int Player1::getMoney()
{
	return money;
}

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
		gWindow = SDL_CreateWindow( "Tour De La IIT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
	if( !gPlayer1Texture.loadFromFile(gRenderer, "Resources/parti1.png" ) )
	{
		printf( "Failed to load player1 texture!\n" );
		success = false;
	}
	if( !gPlayer2Texture.loadFromFile(gRenderer, "Resources/parti2.png" ) )
	{
		printf( "Failed to load player2 texture!\n" );
		success = false;
	}
	// if( !gPlayer2Texture.loadFromFile(gRenderer, "Resources/player2.png" ) )
	// {
	// 	printf( "Failed to load player2 texture!\n" );
	// 	success = false;
	// }

	if( !gmap1Texture.loadFromFile(gRenderer, "Resources/map1.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gminimartTexture.loadFromFile(gRenderer, "Resources/minimart.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !glibraryTexture.loadFromFile(gRenderer, "Resources/library.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gdelhi16Texture.loadFromFile(gRenderer, "Resources/delhi16.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap2Texture.loadFromFile(gRenderer, "Resources/map2.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap3Texture.loadFromFile(gRenderer, "Resources/map3.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap4Texture.loadFromFile(gRenderer, "Resources/map4.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if( !gmap5Texture.loadFromFile(gRenderer, "Resources/map5.png" ) )
	{
		printf( "Failed to load map1 texture!\n" );
		success = false;
	}
	if (!gmaingroundTexture.loadFromFile(gRenderer, "Resources/mainground.png")){
		printf("Failed to load mainground texture!\n");
		success = false;
	}
	if (!gathelticsTexture.loadFromFile(gRenderer, "Resources/atheltics.png")){
		printf("Failed to load atheltics texture!\n");
		success = false;
	}
	if (!gamulTexture.loadFromFile(gRenderer, "Resources/amul.png")){
		printf("Failed to load amul texture!\n");
		success = false;
	}
	if (!gsacTexture.loadFromFile(gRenderer, "Resources/sac.png")){
		printf("Failed to load sac texture!\n");
		success = false;
	}
	if (!glhcTexture.loadFromFile(gRenderer, "Resources/lhc.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!ghospTexture.loadFromFile(gRenderer, "Resources/hosp.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gbankTexture.loadFromFile(gRenderer, "Resources/bank.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gstartTexture.loadFromFile(gRenderer, "Resources/start.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gyuluTexture.loadFromFile(gRenderer, "Resources/yuluparti1.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gbackTexture.loadFromFile(gRenderer, "Resources/winback.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gloseTexture.loadFromFile(gRenderer, "Resources/loose.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gmg1Texture.loadFromFile(gRenderer, "Resources/mg1.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gmg2Texture.loadFromFile(gRenderer, "Resources/mg2.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gmg3Texture.loadFromFile(gRenderer, "Resources/mg3.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gsac1Texture.loadFromFile(gRenderer, "Resources/sac1.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gsac2Texture.loadFromFile(gRenderer, "Resources/sac2.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	if (!gsac3Texture.loadFromFile(gRenderer, "Resources/sac3.png")){
		printf("Failed to load lhc texture!\n");
		success = false;
	}
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile(gRenderer, "Resources/foo.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;

		gSpriteClips[ 1 ].x =  64;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  64;
		gSpriteClips[ 1 ].h = 205;
		
		gSpriteClips[ 2 ].x = 128;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  64;
		gSpriteClips[ 2 ].h = 205;

		gSpriteClips[ 3 ].x = 192;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  64;
		gSpriteClips[ 3 ].h = 205;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPlayer1Texture.free();
	gPlayer2Texture.free();

	// gPlayer2Texture.free();
	gmap1Texture.free();
	gminimartTexture.free();
	glibraryTexture.free();
	gdelhi16Texture.free();
	gmap2Texture.free();
	gmap3Texture.free();
	gmap4Texture.free();
	gmap5Texture.free();
	gsacTexture.free();
	gamulTexture.free();
	gmaingroundTexture.free();
	gathelticsTexture.free();
	glhcTexture.free();
	ghospTexture.free();
	gbankTexture.free();
	gstartTexture.free();
	gyuluTexture.free();
	gbackTexture.free();
	gloseTexture.free();
	gmg1Texture.free();
	gmg2Texture.free();
	gmg3Texture.free();
	gsac1Texture.free();
	gsac2Texture.free();
	gsac3Texture.free();
	//Free loaded images
	gSpriteSheetTexture.free();

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


// std::vector<std::vector<int>> Player1::get_health_incr_areas()
// {
// 	std::vector<std::vector<int>> vec(0);
// 	return vec;
// }
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
		SDL_Rect wall13 = wall_form(5,5,695,22);
		wall_vec.push_back(wall13);
		SDL_Rect wall14 = wall_form(343,215,634,337);
		wall_vec.push_back(wall14);
		SDL_Rect wall15 = wall_form(269,265,336,336);
		wall_vec.push_back(wall15);
		SDL_Rect wall16 = wall_form(179,261,248,355);
		wall_vec.push_back(wall16);
		return wall_vec;
	}
	else if(mMap==2){
		//St the wall
		std::vector<SDL_Rect> wall_vec;
		SDL_Rect wall1 = wall_form(1,0,418,22);
		wall_vec.push_back(wall1);
		SDL_Rect wall2 = wall_form(444,0,700,24);
		wall_vec.push_back(wall2);
		SDL_Rect wall3 = wall_form(0,27,24,221);
		wall_vec.push_back(wall3);
		SDL_Rect wall4 = wall_form(0,221,197,420);
		wall_vec.push_back(wall4);
		SDL_Rect wall5 = wall_form(46,42,197,238);
		wall_vec.push_back(wall5);
		SDL_Rect wall6 = wall_form(204,294,231,420);
		wall_vec.push_back(wall6);
		SDL_Rect wall7 = wall_form(244,328,300,420);
		wall_vec.push_back(wall7);
		SDL_Rect wall8 = wall_form(215,43,240,271);
		wall_vec.push_back(wall8);
		SDL_Rect wall9 = wall_form(256,40,340,306);
		wall_vec.push_back(wall9);
		SDL_Rect wall10 = wall_form(340,149,376,306);
		wall_vec.push_back(wall10);
		SDL_Rect wall11 = wall_form(376,251,425,306);
		wall_vec.push_back(wall11);
		SDL_Rect wall12 = wall_form(397,180,425,251);
		wall_vec.push_back(wall12);
		SDL_Rect wall13 = wall_form(316,329,425,420);
		wall_vec.push_back(wall13);
		SDL_Rect wall14 = wall_form(357,42,425,133);
		wall_vec.push_back(wall14);
		SDL_Rect wall15 = wall_form(403,133,425,153);
		wall_vec.push_back(wall15);
		SDL_Rect wall16 = wall_form(443,44,568,151);
		wall_vec.push_back(wall16);
		SDL_Rect wall17 = wall_form(456,179,545,247);
		wall_vec.push_back(wall17);
		SDL_Rect wall18 = wall_form(545,229,593,248);
		wall_vec.push_back(wall18);
		SDL_Rect wall19 = wall_form(446,251,498,307);
		wall_vec.push_back(wall19);
		SDL_Rect wall20 = wall_form(596,47,653,213);
		wall_vec.push_back(wall20);
		SDL_Rect wall21 = wall_form(572,169,595,213);
		wall_vec.push_back(wall21);
		SDL_Rect wall22 = wall_form(609,213,651,248);
		wall_vec.push_back(wall22);
		SDL_Rect wall23 = wall_form(677,0,700,420);
		wall_vec.push_back(wall23);
		SDL_Rect wall24 = wall_form(514,278,633,349);
		wall_vec.push_back(wall24);
		SDL_Rect wall25 = wall_form(514,365,633,420);
		wall_vec.push_back(wall25);
		SDL_Rect wall26 = wall_form(446,328,514,420);
		wall_vec.push_back(wall26);
		return wall_vec;
	}
	else if(mMap==3){
		//St the wall
		std::vector<SDL_Rect> wall_vec;
		SDL_Rect wall1 = wall_form(1,1,291,417);
		wall_vec.push_back(wall1);
		SDL_Rect wall2 = wall_form(331,6,421,237);
		wall_vec.push_back(wall2);
		SDL_Rect wall3 = wall_form(344,246,436,277);
		wall_vec.push_back(wall3);
		SDL_Rect wall4 = wall_form(335,297,430,414);
		wall_vec.push_back(wall4);
		SDL_Rect wall5 = wall_form(436,404,460,416);
		wall_vec.push_back(wall5);
		SDL_Rect wall6 = wall_form(459,29,512,234);
		wall_vec.push_back(wall6);
		SDL_Rect wall7 = wall_form(519,5,665,337);
		wall_vec.push_back(wall7);
		SDL_Rect wall8 = wall_form(459,260,514,308);
		wall_vec.push_back(wall8);
		SDL_Rect wall9 = wall_form(469,311,512,371);
		wall_vec.push_back(wall9);
		SDL_Rect wall10 = wall_form(517,348,556,417);
		wall_vec.push_back(wall10);
		SDL_Rect wall11 = wall_form(483,377,512,416);
		wall_vec.push_back(wall11);
		SDL_Rect wall12 = wall_form(561,341,636,419);
		wall_vec.push_back(wall12);
		SDL_Rect wall13 = wall_form(640,367,666,416);
		wall_vec.push_back(wall13);
		return wall_vec;
	}
	else if(mMap==4){
		//St the wall
		std::vector<SDL_Rect> wall_vec;
		SDL_Rect wall1 = wall_form(682,1,700,418);
		wall_vec.push_back(wall1);
		SDL_Rect wall2 = wall_form(570,198,654,276);
		wall_vec.push_back(wall2);
		SDL_Rect wall3 = wall_form(557,277,654,414);
		wall_vec.push_back(wall3);
		SDL_Rect wall4 = wall_form(403,1,654,79);
		wall_vec.push_back(wall4);
		SDL_Rect wall5 = wall_form(404,83,502,99);
		wall_vec.push_back(wall5);
		SDL_Rect wall6 = wall_form(522,85,654,101);
		wall_vec.push_back(wall6);
		SDL_Rect wall7 = wall_form(532,106,652,151);
		wall_vec.push_back(wall7);
		SDL_Rect wall8 = wall_form(535,157,620,176);
		wall_vec.push_back(wall8);
		SDL_Rect wall9 = wall_form(638,159,652,178);
		wall_vec.push_back(wall9);
		SDL_Rect wall10 = wall_form(312,3,375,35);
		wall_vec.push_back(wall10);
		SDL_Rect wall11 = wall_form(327,37,381,54);
		wall_vec.push_back(wall11);
		SDL_Rect wall12 = wall_form(311,58,383,305);
		wall_vec.push_back(wall12);
		SDL_Rect wall13 = wall_form(385,126,405,168);
		wall_vec.push_back(wall13);
		SDL_Rect wall14 = wall_form(424,129,474,164);
		wall_vec.push_back(wall14);
		SDL_Rect wall15 = wall_form(494,129,514,166);
		wall_vec.push_back(wall15);
		SDL_Rect wall16 = wall_form(389,174,514,230);
		wall_vec.push_back(wall16);
		SDL_Rect wall17 = wall_form(389,233,510,306);
		wall_vec.push_back(wall17);
		SDL_Rect wall18 = wall_form(512,234,533,286);
		wall_vec.push_back(wall18);
		SDL_Rect wall19 = wall_form(323,311,360,378);
		wall_vec.push_back(wall19);
		SDL_Rect wall20 = wall_form(362,309,531,418);
		wall_vec.push_back(wall20);
		SDL_Rect wall21 = wall_form(288,405,340,416);
		wall_vec.push_back(wall21);
		SDL_Rect wall22 = wall_form(1,1,287,415);
		wall_vec.push_back(wall22);
		return wall_vec;
	}
	else if(mMap==5){
		//St the wall
		std::vector<SDL_Rect> wall_vec;
		SDL_Rect wall1 = wall_form(1,2,255,417);
		wall_vec.push_back(wall1);
		SDL_Rect wall2 = wall_form(278,41,317,254);
		wall_vec.push_back(wall2);
		SDL_Rect wall3 = wall_form(322,104,359,125);
		wall_vec.push_back(wall3);
		SDL_Rect wall4 = wall_form(322,145,359,254);
		wall_vec.push_back(wall4);
		SDL_Rect wall5 = wall_form(342,2,491,75);
		wall_vec.push_back(wall5);
		SDL_Rect wall6 = wall_form(379,104,404,184);
		wall_vec.push_back(wall6);
		SDL_Rect wall7 = wall_form(389,187,404,201);
		wall_vec.push_back(wall7);
		SDL_Rect wall8 = wall_form(380,203,404,257);
		wall_vec.push_back(wall8);
		SDL_Rect wall9 = wall_form(427,106,489,143);
		wall_vec.push_back(wall9);
		SDL_Rect wall10 = wall_form(427,176,491,205);
		wall_vec.push_back(wall10);
		SDL_Rect wall11 = wall_form(448,214,491,238);
		wall_vec.push_back(wall11);
		SDL_Rect wall12 = wall_form(428,228,443,256);
		wall_vec.push_back(wall12);
		SDL_Rect wall13 = wall_form(461,243,491,253);
		wall_vec.push_back(wall13);
		SDL_Rect wall14 = wall_form(278,283,493,379);
		wall_vec.push_back(wall14);
		SDL_Rect wall15 = wall_form(278,412,493,417);
		wall_vec.push_back(wall15);
		SDL_Rect wall16 = wall_form(518,410,700,420);
		wall_vec.push_back(wall16);
		SDL_Rect wall17 = wall_form(667,1,697,407);
		wall_vec.push_back(wall17);
		SDL_Rect wall18 = wall_form(515,284,641,378);
		wall_vec.push_back(wall18);
		SDL_Rect wall19 = wall_form(576,145,639,253);
		wall_vec.push_back(wall19);
		SDL_Rect wall20 = wall_form(515,233,545,253);
		wall_vec.push_back(wall20);
		SDL_Rect wall21 = wall_form(515,90,571,229);
		wall_vec.push_back(wall21);
		SDL_Rect wall22 = wall_form(604,90,640,141);
		wall_vec.push_back(wall22);
		SDL_Rect wall23 = wall_form(517,3,641,48);
		wall_vec.push_back(wall23);
		return wall_vec;
	}
	else{
		std::vector<SDL_Rect> wall_vec(0);
		return wall_vec;
	}
}

void rect_text1(const char* Message,int pos1,int pos2){
	TTF_Init();
    TTF_Font *font = TTF_OpenFont("caviar.ttf", 12);
    if (!font)
        std::cout << "Couldn't find ttf font." << std::endl;
    TextSurface = TTF_RenderText_Blended_Wrapped(font, Message, TextColor, 200);
    TextTexture = SDL_CreateTextureFromSurface(gRenderer, TextSurface);
    TextRect1.x = pos1; // Center horizontaly
    TextRect1.y = pos2; // Center verticaly
    TextRect1.w = TextSurface->w;
    TextRect1.h = TextSurface->h;
    // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
    SDL_FreeSurface(TextSurface);
    TTF_Quit();
	SDL_RenderCopy(gRenderer, TextTexture, NULL, &TextRect1); // Add text to render queue.
    SDL_RenderPresent(gRenderer); // Render everything that's on the queue.

}
void rect_text2(const char* Message,int pos1,int pos2){
	TTF_Init();
    TTF_Font *font = TTF_OpenFont("caviar.ttf", 12);
    if (!font)
        std::cout << "Couldn't find ttf font." << std::endl;
    TextSurface = TTF_RenderText_Blended_Wrapped(font, Message, TextColor, 200);
    TextTexture = SDL_CreateTextureFromSurface(gRenderer, TextSurface);
    TextRect2.x = pos1; // Center horizontaly
    TextRect2.y = pos2; // Center verticaly
    TextRect2.w = TextSurface->w;
    TextRect2.h = TextSurface->h;
    // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
    SDL_FreeSurface(TextSurface);
    TTF_Quit();
	SDL_RenderCopy(gRenderer, TextTexture, NULL, &TextRect2); // Add text to render queue.
    SDL_RenderPresent(gRenderer); // Render everything that's on the queue.
	// SDL_RenderClear( gRenderer );

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
			Player2 player2;
			// Player2 player2;			

			//While application is running
			clientsetup();
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

				if(player1.getHealth()>0){
					player1.move(player1.get_walls());
				}
				//Move the player1
				
				// player1.update_health(player1.get_health_incr_areas());
				// player2.move(wall_vec);

				if(player1.getMap()!=16){
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 102,0,51, 255 );
					SDL_RenderClear( gRenderer );

					//Render wall
					SDL_SetRenderDrawColor( gRenderer, 102,0,51, 255 );	
					//Render objects
				}
				if(player1.getYulu() == true){
						player1.update_money(-0.05);
					}
				
				if(player1.getMap() == 0)
				{
					gstartTexture.render(gRenderer, 0, 0 );
				}
				else if(player1.getMap() == 1)
				{
					gmap1Texture.render(gRenderer, 0, 0 );
					if(player1.getYulu() == false){
						player1.update_health(-0.01);
					}
					
				}
				else if(player1.getMap() == 6)
				{
					gminimartTexture.render(gRenderer, 0, 0 );
					if(player1.getMoney() > 0){
					player1.update_money(-0.1);
					player1.update_health(0.01);}
				}
				else if(player1.getMap() == 7)
				{
					glibraryTexture.render(gRenderer, 0, 0 );
					player1.update_acad(0.02);
					player1.update_enjoy(-0.01);
				}
				else if(player1.getMap() == 8)
				{
					gdelhi16Texture.render(gRenderer, 0, 0 );
					if(player1.getMoney() > 0){
					player1.update_health(0.02);
					player1.update_money(-0.1);}
				}
				else if(player1.getMap() == 2)
				{
					gmap2Texture.render(gRenderer, 0, 0 );
					if(player1.getYulu() == false){
						player1.update_health(-0.01);
					}
				}
				else if(player1.getMap() == 3)
				{
					gmap3Texture.render(gRenderer, 0, 0 );
					if(player1.getYulu() == false){
						player1.update_health(-0.01);
					}
				}
				else if(player1.getMap() == 4)
				{
					gmap4Texture.render(gRenderer, 0, 0 );
					if(player1.getYulu() == false){
						player1.update_health(-0.01);
					}
				}
				else if(player1.getMap() == 5)
				{
					gmap5Texture.render(gRenderer, 0, 0 );
					if(player1.getYulu() == false){
						player1.update_health(-0.01);
					}
				}
				else if(player1.getMap() == 9)
				{
					gsacTexture.render(gRenderer, 0, 0 );
					player1.update_health(-0.01);
					player1.update_enjoy(0.02);
				}
				else if(player1.getMap() == 10)
				{
					gamulTexture.render(gRenderer, 0, 0 );
					if(player1.getMoney() > 0){player1.update_health(0.02);
					player1.update_enjoy(0.01);
					player1.update_money(-0.1);}
				}
				else if(player1.getMap() == 11)
				{
					gmaingroundTexture.render(gRenderer, 0, 0 );
					player1.update_enjoy(0.02);
					player1.update_health(-0.01);
					player1.update_acad(-0.01);
				}
				else if(player1.getMap() == 12)
				{
					gathelticsTexture.render(gRenderer, 0, 0 );
					player1.update_enjoy(0.02);
					player1.update_health(-0.01);
					player1.update_acad(-0.01);
				}
				else if(player1.getMap() == 13)
				{
					glhcTexture.render(gRenderer, 0, 0 );
					player1.update_enjoy(-0.01);
					player1.update_health(-0.01);
					player1.update_acad(0.02);
				}
				else if(player1.getMap() == 14)
				{
					ghospTexture.render(gRenderer, 0, 0 );
					player1.update_health(0.01);
				}
				else if(player1.getMap() == 15)
				{
					gbankTexture.render(gRenderer, 0, 0 );
					player1.update_money(0.5);
					player1.update_enjoy(-0.01);
				}
				else if(player1.getMap() == 18)
				{
					gmg1Texture.render(gRenderer, 0, 0 );
					player1.update_enjoy(0.02);
					player1.update_health(-0.01);
					player1.update_acad(-0.01);
				}
				else if(player1.getMap() == 19)
				{
					gmg2Texture.render(gRenderer, 0, 0 );
					player1.update_enjoy(0.02);
					player1.update_health(-0.01);
					player1.update_acad(-0.01);
				}
				else if(player1.getMap() == 20)
				{
					gmg3Texture.render(gRenderer, 0, 0 );		
					player1.update_enjoy(0.02);
					player1.update_health(-0.01);
					player1.update_acad(-0.01);			
				}
				else if(player1.getMap() == 21)
				{
					gsac1Texture.render(gRenderer, 0, 0 );	
					player1.update_health(-0.01);
					player1.update_enjoy(0.02);						
				}
				else if(player1.getMap() == 22)
				{
					gsac2Texture.render(gRenderer, 0, 0 );
					player1.update_health(-0.01);
					player1.update_enjoy(0.02);				
				}
				else if(player1.getMap() == 23)
				{
					gsac3Texture.render(gRenderer, 0, 0 );
					player1.update_health(-0.01);
					player1.update_enjoy(0.02);				
				}
				else if(player1.getMap() == 16){
						
						
						int stop = 0;
						//Current animation frame
						int frame = 0;
						//While application is running
						while( stop < 20 )
						{
							

							//Clear screen
							
							SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
							SDL_RenderClear( gRenderer );
							gbackTexture.render(gRenderer,0,0);
							

							//Render current frame
							
							SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
							gSpriteSheetTexture.render(gRenderer, ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

							//Update screen
							SDL_RenderPresent( gRenderer );

							//Go to next frame
							++frame;

							//Cycle animation
							if( frame / 4 >= WALKING_ANIMATION_FRAMES )
							{
								frame = 0;
							}
							stop ++;
							
						}
				}
				if(player2.getwinAt() == true)
				{
					gloseTexture.render(gRenderer, 0, 0 );
				}
				
				if (player2.getwinAt() == false && player1.getMap()!=0 && player1.getMap()!=16)
				{
					player1.render();
				}

				if (player2.getwinAt() == false && player1.getMap()==player2.getMap() && player1.getMap()!=0 && player1.getMap()!=16)
				{
					gPlayer2Texture.render(gRenderer, player2.getXcord(), player2.getYcord() );					
				}
				if(player2.getwinAt() == false && player1.getMap()!=0 && player1.getMap()!=16)
					{int a = SDL_RenderFillRect(gRenderer,&TextRect1);
					// std::cout<<player1.PLAYER1_VEL<<std::endl;
					std::string str1= "[H1 = "+std::to_string(player1.getHealth())+"] "+"[H2 = "+std::to_string(player2.getHealth())+"] \n"+
					"[E1 = "+std::to_string(player1.getEnjoy())+"] "+"[E2 = "+std::to_string(player2.getEnjoy())+"] \n"+
					"[A1 = "+std::to_string(player1.getAcad())+"] "+"[A2 = "+std::to_string(player2.getAcad())+"] \n"+
					"[M1 = "+std::to_string(player1.getMoney())+"]"+"[M2= "+std::to_string(player2.getMoney())+"]";
					char* c1 = const_cast<char*>(str1.c_str());
					// player2.render(gRenderer,);
					if ( player1.getMap()!=16 && player2.getwinAt() == false)
					{
						rect_text1(c1,0,537);
					}
				}
				SDL_SetRenderDrawColor( gRenderer, 51,0,102, 255 );	
				// int b = SDL_RenderFillRect(gRenderer,&TextRect2);
				// std::string str2= "[Health_index = "+std::to_string(player2.getHealth())+"] "+"[Enjoyment_index = "+std::to_string(player2.getEnjoy())+"] "+"[AcadStatus = "+std::to_string(player2.getAcad())+"] \n"+"[Money = "+std::to_string(player2.getMoney())+"]";
				// char* c2 = const_cast<char*>(str2.c_str());
				// // player2.render(gRenderer,);
				// if (player2.getMap()!=0)
				// {
				// 	rect_text2(c2,0,200);
				// }

				//Update screen
				SDL_RenderPresent( gRenderer );
				std::string temp;				
				if(player1.getwinAt() == true)
				{
					temp = std::to_string(player1.getMap()) + " " + std::to_string(player1.getXcord()) + " " + std::to_string(player1.getYcord()) + " " + std::to_string(player1.getHealth()) + " " + std::to_string(player1.getEnjoy()) + " " + std::to_string(player1.getAcad())+" "+std::to_string(player1.getMoney())+" "+std::to_string(1)+" ";
				}
				else if (player1.getwinAt() == false){
					temp = std::to_string(player1.getMap()) + " " + std::to_string(player1.getXcord()) + " " + std::to_string(player1.getYcord()) + " " + std::to_string(player1.getHealth()) + " " + std::to_string(player1.getEnjoy()) + " " + std::to_string(player1.getAcad())+" "+std::to_string(player1.getMoney())+" "+std::to_string(0)+" ";
				}
				
				char* c = const_cast<char*>(temp.c_str());
				mybuff = clientreadbuffer();	
				clientsendmessage(c);
				player2.assign_param(mybuff);	
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
