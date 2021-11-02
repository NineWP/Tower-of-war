#include "pickUp.h"

pickUp::pickUp(int type)
{
	Potion_Type = type;

	if (Potion_Type == 1)
	{
		Potion_Sprite = Sprite(TextureHolder::GetTexture("graphics/health_potion.png"));
		Value = Health_Potion_Value;
	}
	else
	{
		Potion_Sprite = Sprite(TextureHolder::GetTexture("graphics/mana_potion.png"));
		Value = Mana_Potion_Value;
	}

	Potion_Sprite.setOrigin(25, 25);

	Potion_SecondToLive = Start_Second_To_Live;
	Potion_SecondToWait = Start_Wait_Time;

}

void pickUp::setArena(IntRect arena)
{
	Arena.left = arena.left + 50;
	Arena.width = arena.width - 50;
	Arena.top = arena.top + 50;
	Arena.height = arena.height - 50;

	spawn();
}

void pickUp::spawn()
{
	srand((int)time(0) / Potion_Type);
	int x = (rand() % Arena.width);

	srand((int)time(0) * Potion_Type);
	int y = (rand() % Arena.height);

	Potion_SecondSinceSpawn = 0;
	Potion_Spawn = true;

	Potion_Sprite.setPosition(x, y);
}

FloatRect pickUp::getPosition()
{
	return Potion_Sprite.getGlobalBounds();
}

bool pickUp::isSpawned()
{
	return Potion_Spawn;
}

Sprite pickUp::getSprite()
{
	return Potion_Sprite;
}

void pickUp::update(float elapsedTime)
{
	if (Potion_Spawn)
	{
		Potion_SecondSinceSpawn += elapsedTime;
	}
	else
	{
		Potion_SecondSinceDisappear += elapsedTime;
	}

	if (Potion_SecondSinceSpawn > Potion_SecondToLive && Potion_Spawn)
	{
		Potion_Spawn = false;
		Potion_SecondSinceDisappear = 0;
	}

	if (Potion_SecondSinceDisappear > Potion_SecondToWait && !Potion_Spawn)
	{
		spawn();
	}

}

int pickUp::gotIt()
{
	Potion_Spawn = false;
	Potion_SecondSinceDisappear = 0;
	return Value;
}

void pickUp::upgrade()
{
	if (Potion_Type == 1)
	{
		Value += Health_Potion_Value * .5;
	}
	else
	{
		Value += Mana_Potion_Value * .5;
	}

	Potion_SecondToLive += Start_Second_To_Live / 10;
	Potion_SecondToWait -= Start_Wait_Time / 10; 
}
