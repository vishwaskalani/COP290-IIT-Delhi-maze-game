#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include "ltexture.h"

class Player2
{
    public:
		Player2();
		int getMap();
		int getXcord();
		int getYcord();
		int getHealth();
		int getAcad();
		int getEnjoy();
		int getMoney();
		void assign_param(char* mybuff);
		void render(SDL_Renderer* gRenderer,LTexture gPlayer2Texture);
		bool getwinAt();
		

    private:
		//The X and Y offsets of the player1
		float health_index,acadStatus,enjoyment_index,money;

		int mPosX, mPosY;

		int mMap;

		bool winAt;
		
		
};