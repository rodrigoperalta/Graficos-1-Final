#pragma once

#include "Input.h"
#include "Sprite.h"

class Bullet
{
	Input* input;
	Sprite* sprite;
	vec2 originalPosition; 
	vec2 spawnPosition;
	float speed;
	bool isAlive;
	float timeAlive;

public:
	void Update();
	void Draw();
	void Shoot();
	void Move();
	void ReturnToOriginalPosition();

	void SetSpeed(float speed) { this->speed = speed; };
	float GetSpeed() { return speed; };
	Sprite* GetSprite() { return sprite; };
	void GetCharacterPosition(float x, float y);
	void Die();
	void SetOriginalPosition(float x, float y);

	Bullet(
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
	);
	~Bullet();
};

