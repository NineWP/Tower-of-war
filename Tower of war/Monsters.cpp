#include "Monsters.h"
#include "TextureHolder.h"
#include <ctime>
#include <cstdlib>

using namespace std;

void Monsters::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Org 
		Monster_Sprite = Sprite(TextureHolder::GetTexture("graphics/org.png"));
		Monster_Sprite.setOrigin(34, 26);
		Monster_Speed = Org_Speed;
		Monster_Health = Org_HP;
		break;
	case 1:
		// Goblin
		Monster_Sprite = Sprite(TextureHolder::GetTexture("graphics/goblin.png"));
		Monster_Sprite.setOrigin(25, 30);
		Monster_Speed = Goblin_Speed;
		Monster_Health = Goblin_HP;
		break;
	case 2:
		// Slime
		Monster_Sprite = Sprite(TextureHolder::GetTexture("graphics/slime.png"));
		Monster_Sprite.setOrigin(15, 13);
		Monster_Speed = Slime_Speed;
		Monster_Health = Slime_HP;
		break;
	}

	srand((int)time(0) * seed);
	float modifier = (rand() % Max_Varriance) + OffSet;

	modifier /= 100;
	Monster_Speed *= modifier;

	// Start position
	Monster_Position.x = startX;
	Monster_Position.y = startY;
	Monster_Sprite.setPosition(Monster_Position);
}

bool Monsters::hit()
{
	Monster_Health -= 1;

	if (Monster_Health < 0)
	{
		Monster_Alive = false;
		Monster_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}
	else
	{
		return false;
	}

}

bool Monsters::Alive()
{
	return Monster_Alive;
}

FloatRect Monsters::getPosition()
{
	return Monster_Sprite.getGlobalBounds();
}

Sprite Monsters::getSprite()
{
	return Monster_Sprite;
}

void Monsters::update(float elapsedTime, Vector2f playerLocation)
{
	float PlayerX = playerLocation.x;
	float PlayerY = playerLocation.y;

	// Monster follow the player /////////////////////////////////////////////////////////////
	if (PlayerX > Monster_Position.x)
	{
		Monster_Position.x = Monster_Position.x + Monster_Speed * elapsedTime;
	}
	if (PlayerY > Monster_Position.y)
	{
		Monster_Position.y = Monster_Position.y + Monster_Speed * elapsedTime;
	}
	if (PlayerX < Monster_Position.x)
	{
		Monster_Position.x = Monster_Position.x - Monster_Speed * elapsedTime;
	}
	if (PlayerY < Monster_Position.y)
	{
		Monster_Position.y = Monster_Position.y - Monster_Speed * elapsedTime;
	}

	Monster_Sprite.setPosition(Monster_Position);

	float angle = (atan2(PlayerY - Monster_Position.y, PlayerX - Monster_Position.x) * 180) / 3.141;

	Monster_Sprite.setRotation(angle);
}
