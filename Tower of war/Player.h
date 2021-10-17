#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Arena.h"
#include "TextureHolder.h"
using namespace sf;

class Player
{
private:
	const float startSpeed = 200;
	const float startHealth = 100;

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
	
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime, Vector2i mousePosition);

	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int getHealth();


};

