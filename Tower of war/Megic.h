#pragma once
#include "Player.h"

class Megic
{
private:
	Vector2f Fireball_Position;
	Sprite Fireball_Shape;
	Sprite boomShape;
	float Fireball_speed = 1000;
	float Boomtime = 0;
	int BoomDelay = 5;

	bool Ball_InFlight = false;
	bool BoomActive = false;
	Vector2f ResolutionM;
	float Fireball_DistanceX;
	float Fireball_DistanceY;
	float distanceMaxX, distanceMaxY, distanceMinX, distanceMinY;

public:
	Megic();

	bool isInFlight();
	bool BoomIsActive();
	void Cast(float startX, float startY, float TargetX, float TargetY, Vector2i mousePosition);

	FloatRect getPosition();
	Sprite getShape();
	Sprite getBoomShape();
	void RecieveResolution(Vector2f resolutionM);

	void stop();
	void update(float elapsedTime);
	void stopBoom();
	void updateBoom(float elapsedTime);
	FloatRect getBoomPosition();
	void Boom();

};

