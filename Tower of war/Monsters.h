#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Monsters
{
private:

	// Monsters Speed ///////////////////////////////////////////
	const float Org_Speed = 40;
	const float Goblin_Speed = 80;
	const float Slime_Speed = 20;

	// Monster HP ///////////////////////////////////////////////
	const float Org_HP = 5000;
	const float Goblin_HP = 1500;
	const float Slime_HP = 3000;

	const int Max_Varriance = 30;
	const int OffSet = 101 - Max_Varriance;

	Vector2f Monster_Position;
	Sprite Monster_Sprite;
	float Monster_Speed;
	float Monster_Health;
	bool Monster_Alive;

public:

	bool hit();
	bool Alive();
	void spawn(float startX, float startY, int type, int seed);
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime, Vector2f playerLocation);

};

