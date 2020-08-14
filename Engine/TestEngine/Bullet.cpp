#include "Bullet.h"

Bullet::Bullet(
	Renderer* renderer,			// Renderer reference
	Material* material,			// Material reference
	Layers layer,				// Layer of the Entity
	const char* imagePath,		// Path of the image
	bool isAnimated,			// Is animated? Yes/No
	const unsigned int sColumns,// Columns of the spritesheet
	const unsigned int sRows,	// Rows of the spritesheet
	const float colliderWidth,	// Width of the collider
	const float colliderHeight,	// Height of the collider
	bool isInteractable,		// Does the Sprite collide with the Tilemap? Yes/No
	Tilemap* tilemap			// Tilemap reference
)
{
	input = Input::getInstance();
	isAlive = false;
	sprite = new Sprite(renderer, material, layer, imagePath, isAnimated, sColumns, sRows, colliderWidth, colliderHeight, isInteractable, tilemap);

}
Bullet::~Bullet()
{
}

void Bullet::Update()
{
	sprite->Update();
	if (isAlive)
	{
		timeAlive++;
		if (timeAlive > 30)		
			this->Die();
	}
	this->Move();
}

void Bullet::Draw()
{
	sprite->Draw();
}
void Bullet::Move()
{
	if (isAlive)	
		sprite->Translate(speed * Defs::getInstance()->deltaTime / 2, 0.0f, 0.0f);	
}

void Bullet::Shoot()
{
	if (!isAlive)
	{
		timeAlive = 0;
		isAlive = true;		
		sprite->Teleport(spawnPosition.x, spawnPosition.y, 0.0f);
	}
	
}

void Bullet::GetCharacterPosition(float x, float y)
{
	spawnPosition.x = x;
	spawnPosition.y = y;
}

void Bullet::SetOriginalPosition(float x, float y)
{
	originalPosition.x = x;
	originalPosition.y = y;	
}

void Bullet::ReturnToOriginalPosition()
{
	sprite->Teleport(
		originalPosition.x,
		originalPosition.y,
		0.0f);
}

void Bullet::Die()
{
	isAlive = false;
	ReturnToOriginalPosition();
}