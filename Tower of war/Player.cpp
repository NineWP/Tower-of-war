#include "Player.h"

Player::Player()
{
	Player_Speed = startSpeed;
	Player_Health = startHealth;
	Player_MaxHealth = startHealth;

	Player_Texture.loadFromFile("graphics/player.png");
	Player_Sprite.setTexture(Player_Texture);

	Player_Sprite.setOrigin(25, 25);

	Attack_Sprite = Sprite(TextureHolder::GetTexture("graphics/Attack.png"));
	Attack_Sprite.setOrigin(25, 25);
		
}

void Player::Spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	Player_Position.x = arena.width / 2;
	Player_Position.y = arena.height / 2;

	Arena.left = arena.left;
	Arena.width = arena.width;
	Arena.top = arena.top;
	Arena.height = arena.height;

	TileSize = tileSize;

	Resolution.x = resolution.x;
	Resolution.y = resolution.y;

}

void Player::resetPlayerState()
{
	Player_Health = startHealth;
	Player_Speed = startSpeed;
	Player_MaxHealth = startHealth;
}

Time Player::getLastHitTime()
{
	return Last_Hit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - Last_Hit.asMilliseconds() > 200)
	{
		Last_Hit = timeHit;
		Player_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return Player_Sprite.getGlobalBounds();
}

Vector2f Player::getPlayerCenter()
{
	return Player_Position;
}

float Player::getRotation()
{
	return Player_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return Player_Sprite;
}

void Player::moveLeft()
{
	pressedLeft = true;
}

void Player::moveRight()
{
	pressedRight = true;
}

void Player::moveUp()
{
	pressedUp = true;
}

void Player::moveDown()
{
	pressedDown = true;
}

void Player::moveDash()
{
	dash = true;
}

bool Player::InAction()
{
	return Attack_Inaction;
}

void Player::attack(float startX, float startY, float TargetX, float TargetY, Vector2i mousePosition)
{
	Attack_Inaction = true;
	Attack_Position.x = startX;
	Attack_Position.y = startY;

	float gradient = (startX - TargetX) / (startY - TargetY);

	if (gradient < 0)
	{
		gradient *= -1;
	}

	float ratioXY = Action_speed / (1 + gradient);

	Attack_DistanceX = ratioXY * gradient;
	Attack_DistanceY = ratioXY;

	if (TargetX < startX)
	{
		Attack_DistanceX *= -1;
	}

	if (TargetY < startY)
	{
		Attack_DistanceY *= -1;
	}

	float range = 50;
	distanceMaxX = startX + range;
	distanceMaxY = startY + range;
	distanceMinX = startX - range;
	distanceMinY = startY - range;

	Attack_Sprite.setPosition(Attack_Position);
	float angle = (atan2(mousePosition.y - Resolution.y / 2, mousePosition.x - Resolution.x / 2) * 180) / 3.141;

	Attack_Sprite.setRotation(angle);
}

FloatRect Player::getAttackPosition()
{
	return Attack_Sprite.getGlobalBounds();
}

Sprite Player::getAttackSprite()
{
	return Attack_Sprite;
}

void Player::stopAttack()
{
	Attack_Inaction = false;
}

void Player::updateAttack(float elapsedTime)
{
	Attack_Position.x += Attack_DistanceX * elapsedTime;
	Attack_Position.y += Attack_DistanceY * elapsedTime;

	Attack_Sprite.setPosition(Attack_Position);

	if (Attack_Position.x < distanceMinX || Attack_Position.x > distanceMaxX ||
		Attack_Position.y < distanceMinY || Attack_Position.y > distanceMaxY)
	{
		Attack_Inaction = false;
	}
}

void Player::stopLeft()
{
	pressedLeft = false;
}

void Player::stopRight()
{
	pressedRight = false;
}

void Player::stopUp()
{
	pressedUp = false;
}

void Player::stopDown()
{
	pressedDown = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (pressedUp)
	{
		Player_Position.y -= Player_Speed * elapsedTime;
	}
	if (pressedDown)
	{
		Player_Position.y += Player_Speed * elapsedTime;
	}
	if (pressedLeft)
	{
		Player_Position.x -= Player_Speed * elapsedTime;
	}
	if (pressedRight)
	{
		Player_Position.x += Player_Speed * elapsedTime;
	}
	if (dash && !dashcount)
	{
		Player_Speed *= dashSpeed;
		dashcount = true;
	}

	if (dashcount)
	{
		timeSinceDash += elapsedTime;
	}

	if (timeSinceDash > dashTime && dashcount && dash)
	{
		timeSinceDash = 0;
		Player_Speed /= dashSpeed;
		dashcount = false;
		dash = false;
	}

	Player_Sprite.setPosition(Player_Position);

	if (Player_Position.x > Arena.width - TileSize)
	{
		Player_Position.x = Arena.width - TileSize;
	}

	if (Player_Position.x < Arena.left + TileSize)
	{
		Player_Position.x = Arena.left + TileSize;
	}

	if (Player_Position.y > Arena.height - TileSize)
	{
		Player_Position.y = Arena.height - TileSize;
	}

	if (Player_Position.y < Arena.top + TileSize)
	{
		Player_Position.y = Arena.top + TileSize;
	}

	// Calculate the angle the player is facing 
	float angle = (atan2(mousePosition.y - Resolution.y / 2, mousePosition.x - Resolution.x / 2) * 180) / 3.141;

	Player_Sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	Player_Speed += startSpeed * .2;
}

void Player::upgradeHealth()
{
	Player_MaxHealth += startHealth * .2;
}

void Player::increaseHealthLevel(int amount) // Healing the Player
{
	Player_Health += amount;

	if (Player_Health > Player_MaxHealth)
	{
		Player_Health = Player_MaxHealth;
	}
}

int Player::getHealth()
{
	return Player_Health;
}

Vector2f Player::getResolution()
{
	return Resolution;
}

