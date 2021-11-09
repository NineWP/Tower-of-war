#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "Arena.h"
#include "TextureHolder.h"
#include "Megic.h"
#include "pickUp.h"
using namespace sf;

class Player
{
private:
	const float startSpeed = 200;
	const float startHealth = 100;
	const float dashSpeed = 4;

	Vector2f Player_Position;
	Sprite Player_Sprite;
	Texture Player_Texture;

	Vector2f Resolution;

	IntRect Arena;
	int TileSize;

	bool pressedUp, pressedDown, pressedLeft, pressedRight ;

	// Player Status ////////////////////////////////////////////////////////////////////////////////////////////
	int Player_Health;
	int Player_MaxHealth;
	Time Last_Hit;
	float Player_Speed;
	bool dash = false;
	bool dashcount = false;
	float timeSinceDash = 0;
	float dashTime = 0.1;

	//  Player Attack
	Vector2f Attack_Position;
	Sprite Attack_Sprite;
	float Action_speed = 1000;

	bool Attack_Inaction = false;

	float Attack_DistanceX;
	float Attack_DistanceY;
	float distanceMaxX, distanceMaxY, distanceMinX, distanceMinY;

public:
	Player();

	void Spawn(IntRect arena, Vector2f resolution, int tileSize);

	void resetPlayerState();

	bool hit(Time hit);
	Time getLastHitTime();
	FloatRect getPosition();
	Vector2f getPlayerCenter();

	float getRotation();

	Sprite getSprite();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveDash();

	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime, Vector2i mousePosition);

	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int getHealth();

	Vector2f getResolution();

	// Attack Function
	bool InAction();
	void attack(float startX, float startY, float TargetX, float TargetY, Vector2i mousePosition);
	FloatRect getAttackPosition();
	Sprite getAttackSprite();

	void stopAttack();
	void updateAttack(float elapsedTime);
};

