#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

enum GameState
{
	LOSE = -1,
	CONTINUE,
	WIN
};

class Game : public GameBase
{
	Input* input;
	Material* material;
	Material* matTexture;
	Player* player;
	list<Asteroid*>* asteroids;
	Tilemap* tilemap;
	Bullet* b;
	float speed;		// Speed

	const int totalAsteroids = 50;

	GameState gameState;

	void FillAsteroidsData();
	void Restart();

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	bool OnDraw() override;

public:
	Game();
	~Game();
};

