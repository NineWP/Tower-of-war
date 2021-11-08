#pragma once
#include "Player.h"

class Megic
{
private:
	Vector2f Fireball_Position;
	CircleShape Fireball_Shape;
	CircleShape BoomShape;
	float Fireball_speed = 1000;
	float Boomtime = 0;

	bool Ball_InFlight = false;
	bool BoomActive = false;

	float Fireball_DistanceX;
	float Fireball_DistanceY;
	float distanceMaxX, distanceMaxY, distanceMinX, distanceMinY;

public:
	Megic();

	bool isInFlight();
	bool BoomIsActive();
	void Cast(float startX, float startY, float TargetX, float TargetY);

	FloatRect getPosition();
	CircleShape getShape();
	CircleShape getBoomShape();

	void stop();
	void update(float elapsedTime);
	void stopBoom();
	void updateBoom(float elapsedTime);
	FloatRect getBoomPosition();
	void Boom();

};

