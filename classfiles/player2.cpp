#include "player2.h"

void Player2::render(SDL_Renderer* gRenderer,LTexture gPlayer2Texture)
{
    //Show the player1
	gPlayer2Texture.render(gRenderer, mPosX, mPosY );
}

int Player2::getMap()
{
	return mMap;
}

int Player2::getXcord()
{
	return mPosX;
}
int Player2::getYcord()
{
	return mPosY;
}
bool Player2::getwinAt()
{
	return winAt;
}
int Player2::getHealth()
{
	return health_index;
}
int Player2::getAcad()
{
	return acadStatus;
}
int Player2::getEnjoy()
{
	return enjoyment_index;
}
int Player2::getMoney()
{
	return money;
}
void Player2::assign_param(char* mybuff){
	std::string strp = std::string(mybuff);
	std::istringstream ss(strp);
	std::string word; 
	ss>>word;
	mMap = std::stoi(word);
	ss>>word;
	mPosX = std::stoi(word);
	ss>>word;
	mPosY = std::stoi(word);
	ss>>word;
	health_index = std::stoi(word);
	ss>>word;
	enjoyment_index = std::stoi(word);
	ss>>word;
	acadStatus = std::stoi(word);
	ss>>word;
	money = std::stoi(word);
}