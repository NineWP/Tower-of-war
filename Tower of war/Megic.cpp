#include "Megic.h"

Megic::Megic()
{
	Fireball_Shape = Sprite(TextureHolder::GetTexture("graphics/fire_ball.png"));
	Fireball_Shape.setOrigin(20, 10);
	BoomShape.setRadius(100.f);
	BoomShape.setOrigin(100, 100);
	BoomShape.setFillColor(Color::Red);
}

bool Megic::isInFlight()
{
	return Ball_InFlight;
}

bool Megic::BoomIsActive()
{
	return BoomActive;
}

void Megic::Cast(float startX, float startY, float TargetX, float TargetY, Vector2i mousePosition)
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
	float angle = (atan2(mousePosition.y - ResolutionM.y / 2, mousePosition.x - ResolutionM.x / 2) * 180) / 3.141;
	Fireball_Shape.setRotation(angle);

	Fireball_Shape.setPosition(Fireball_Position);
}

FloatRect Megic::getPosition()
{
	return Fireball_Shape.getGlobalBounds();
}

Sprite Megic::getShape()
{
	return Fireball_Shape;
}

CircleShape Megic::getBoomShape()
{
	return BoomShape;
}

void Megic::RecieveResolution(Vector2f resolutionM)
{
	ResolutionM.x = resolutionM.x;
	ResolutionM.y = resolutionM.y;
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

void Megic::stopBoom()
{
	BoomActive = false;
}

void Megic::updateBoom(float elapsedTime)
{
	if (BoomActive)
	{
		Boomtime += elapsedTime;
	}

	if (Boomtime >= BoomDelay)
	{
		BoomActive = false;
		Boomtime = 0;
	}
}

FloatRect Megic::getBoomPosition()
{
	return BoomShape.getGlobalBounds();
}

void Megic::Boom()
{
	BoomActive = true;
	BoomShape.setPosition(Fireball_Position);
}
