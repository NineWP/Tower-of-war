#pragma once
#include "Player.h"
class pickUp
{
private:
	const int Health_Potion_Value = 50;
	const int Mana_Potion_Value = 5;
	const int Start_Wait_Time = 10;
	const int Start_Second_To_Live = 5;

	Sprite Potion_Sprite;

	IntRect Arena;

	int Value;

	int Potion_Type; // 1 Health, 2 Mana 

	bool Potion_Spawn;
	float Potion_SecondSinceSpawn;
	float Potion_SecondSinceDisappear;
	float Potion_SecondToLive;
	float Potion_SecondToWait;

public:

	pickUp(int type);

	void setArena(IntRect arena);
	void spawn();
	bool isSpawned();

	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime);

	int gotIt();
	void upgrade();
};

