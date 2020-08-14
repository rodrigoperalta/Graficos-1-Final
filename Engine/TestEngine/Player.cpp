#include "Player.h"

Player::Player(
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
	sprite = new Sprite(renderer, material, layer, imagePath, isAnimated, sColumns, sRows, colliderWidth, colliderHeight, isInteractable, tilemap);

	unsigned int frames[6] = { 0, 1, 2, 3, 4, 5 };
	sprite->GetAnimation()->SetNewAnimation(frames);

	hit = Background;

	input = Input::getInstance();
}
Player::~Player()
{
}

void Player::GetBullet(Bullet* _b)
{
	b = _b;
}

void Player::Update()
{
	sprite->Update();
}

void Player::Draw()
{
	sprite->Draw();
}

void Player::Move()
{	
	vec2 move = vec2(speed * Defs::getInstance()->deltaTime, 0.0f);

	if (input->isInput(GLFW_KEY_W))
	{
		move.y += speed * Defs::getInstance()->deltaTime;
		this->SetActualPosition(0, move.y);
	}

	if (input->isInput(GLFW_KEY_S))
	{
		move.y -= speed * Defs::getInstance()->deltaTime;
		this->SetActualPosition(0, move.y);
	}

	/*if (input->isInput(GLFW_KEY_D))
	{
		move.x += speed * Defs::getInstance()->deltaTime;
		this->SetActualPosition(move.x, 0);
	}
	if (input->isInput(GLFW_KEY_A))
	{
		move.x -= speed * Defs::getInstance()->deltaTime;	
		this->SetActualPosition(move.x, 0);
	}*/
	//this->SetActualPosition(move.x, 0);
	
	
	if (input->isInput(GLFW_KEY_SPACE))
	{		
		b->GetCharacterPosition(actualPosition.x, actualPosition.y);
		b->Shoot();
		//printf("Im shooting weeee");
	}


	hit = sprite->Move(move.x, move.y, 0.0f);
}
void Player::SetActualPosition(float x, float y)
{
	actualPosition.x = actualPosition.x + x;
	actualPosition.y = actualPosition.y + y;
}

void Player::Die()
{
	unsigned int frames[6] = { 6, 7, 8, 9, 10, 11 };
	sprite->GetAnimation()->SetNewAnimation(frames);
	sprite->GetAnimation()->SetIsLoop(false);
}

void Player::SetOriginalPosition(float x, float y)
{
	originalPosition.x = x;
	originalPosition.y = y;
	actualPosition = originalPosition;
	sprite->Teleport(originalPosition.x, originalPosition.y, 0.0f);
}

void Player::ReturnToOriginalPosition()
{
	sprite->Teleport(
		originalPosition.x,
		originalPosition.y,
		0.0f);
	actualPosition = originalPosition;
	unsigned int frames[6] = { 0, 1, 2, 3, 4, 5 };
	sprite->GetAnimation()->SetNewAnimation(frames);
	sprite->GetAnimation()->SetIsLoop(true);
}