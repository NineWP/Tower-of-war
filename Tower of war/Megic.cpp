#include "Megic.h"

Megic::Megic()
{
	Fireball_Shape.setRadius(10.f);
	Fireball_Shape.setOrigin(5, 5);
}

bool Megic::isInFlight()
{
	return Ball_InFlight;
}

void Megic::Cast(float startX, float startY, float TargetX, float TargetY)
{
	Ball_InFlight = true;
	Fireball_Position.x = startX;
	Fireball_Position.y = startY;

	// gradient of the flight path
	float gradient = (startX - TargetX) / (startY - TargetY);

	if (gradient < 0)
	{
		gradient *= -1;
	}

	float ratioXY = Fireball_speed / (1 + gradient);

	// set speed horizontally and vertically 
	Fireball_DistanceX = ratioXY * gradient;
	Fireball_DistanceY = ratioXY;

	// Point fireball in the right direction
	if (TargetX < startX)
	{
		Fireball_DistanceX *= -1;
	}

	if (TargetY < startY)
	{
		Fireball_DistanceY *= -1;
	}

	// set max range of pixel
	float range = 1000;
	distanceMaxX = startX + range;
	distanceMaxY = startY + range;
	distanceMinX = startX - range;
	distanceMinY = startY - range;

	// position fireball ready to be draw
	Fireball_Shape.setPosition(Fireball_Position);
}

FloatRect Megic::getPosition()
{
	return Fireball_Shape.getGlobalBounds();
}

CircleShape Megic::getShape()
{
	return Fireball_Shape;
}

void Megic::stop()
{
	Ball_InFlight = false;
}

void Megic::update(float elapsedTime)
{
	// Update fireball position
	Fireball_Position.x += Fireball_DistanceX * elapsedTime;
	Fireball_Position.y += Fireball_DistanceY * elapsedTime;

	// Move fireball
	Fireball_Shape.setPosition(Fireball_Position);

	//check if bullet out of arena
	if (Fireball_Position.x < distanceMinX || Fireball_Position.x > distanceMaxX ||
		Fireball_Position.y < distanceMinY || Fireball_Position.y > distanceMaxY)
	{
		Ball_InFlight = false;
	}
}
