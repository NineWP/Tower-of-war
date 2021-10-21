#pragma once
#include "Player.h"

class Megic
{
private:
	Vector2f Fireball_Position;
	CircleShape Fireball_Shape;
	float Fireball_speed = 1000;

	bool Ball_InFlight = false;

	float Fireball_DistanceX;
	float Fireball_DistanceY;
	float distanceMaxX, distanceMaxY, distanceMinX, distanceMinY;

public:
	Megic();

	bool isInFlight();
	void Cast(float startX, float startY, float TargetX, float TargetY);

	FloatRect getPosition();
	CircleShape getShape();

	void stop();
	void update(float elapsedTime);

};

