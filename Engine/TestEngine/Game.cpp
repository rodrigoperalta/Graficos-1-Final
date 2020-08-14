#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	input = Input::getInstance();
	input->SetWindowContext(GetWindow());

	CollisionManager* cmgr = CollisionManager::getInstance();
	
	cmgr->SetRelation(Character, Enemy);
	cmgr->SetRelation(Character, Wall);
	cmgr->SetRelation(Enemy, Wall);
	cmgr->SetRelation(Enemy, Ammo);

	speed = 100.0f;
	gameState = CONTINUE;

	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	matTexture = new Material();
	matTexture->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
						, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);
	//																									 4800  960
	tilemap = new Tilemap(GetRenderer(), matTexture, Default, "SpaceTiles.bmp", 3, 4, "SpaceLevel3.csv", 4800, 960);
	tilemap->SetOriginalPosition(0.0f, 64.0f);
	GetRenderer()->MoveCamera(glm::vec3(0.0f, 64.0f, 0.0f));

	tilemap->SetTileProperty(0, Obstacle);
	tilemap->SetTileProperty(1, Obstacle);
	tilemap->SetTileProperty(2, Obstacle);
	tilemap->SetTileProperty(3, Obstacle);
	tilemap->SetTileProperty(4, Background);
	tilemap->SetTileProperty(5, Background);
	tilemap->SetTileProperty(6, Death_Trigger);
	tilemap->SetTileProperty(7, Death_Trigger);
	tilemap->SetTileProperty(8, Death_Trigger);
	tilemap->SetTileProperty(9, Death_Trigger);
	tilemap->SetTileProperty(10,Win_Trigger);

	player = new Player(GetRenderer(), matTexture, Character, "Ship3.bmp", true, 2, 6, 40.0f, 20.0f, true, tilemap);
	player->SetSpeed(100.0f);
	b = new Bullet(GetRenderer(), matTexture, Ammo, "Bullet.bmp", false, 1, 1, 24.0f, 24.0f, false, tilemap);
	b->SetSpeed(1000.0f);
	b->SetOriginalPosition(0.0f, 0.0f);
	player->GetBullet(b);
	asteroids = new list<Asteroid*>;
	for (int i = 0; i < totalAsteroids; i++)
		asteroids->push_back(new Asteroid(GetRenderer(), matTexture, Enemy, "Asteroid.bmp", false, 1, 1, 32.0f, 32.0f, false, tilemap));
	cmgr->AddEntity(b->GetSprite()->GetEntity());
	cmgr->AddEntity(player->GetSprite()->GetEntity());
	for (list<Asteroid*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
	{
		(*ast)->SetSpeed(100.0f);
		cmgr->AddEntity((*ast)->GetSprite()->GetEntity());
	}

	player->SetOriginalPosition(100.0f, 400.0f);

	FillAsteroidsData();

	return true;
}

void Game::FillAsteroidsData()
{
	list<Asteroid*>::iterator ast = asteroids->begin();
	(*ast)->SetOriginalPosition(500.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(830.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 300.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(1600.0f, 350.0f);
	ast++;
	(*ast)->SetOriginalPosition(1750.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(1900.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(2300.0f, 520.0f);
	ast++;
	(*ast)->SetOriginalPosition(2500.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(2700.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(3000.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(3050.0f, 518.0f);
	ast++;
	(*ast)->SetOriginalPosition(3100.0f, 486.0f);
	ast++;
	(*ast)->SetOriginalPosition(3200.0f, 454.0f);
	ast++;
	(*ast)->SetOriginalPosition(3700.0f, 605.0f);
	ast++;
	(*ast)->SetOriginalPosition(3900.0f, 410.0f);
	ast++;
	(*ast)->SetOriginalPosition(4200.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(4500.0f, 470.0f);
	ast++;
	(*ast)->SetOriginalPosition(4600.0f, 502.0f);
	ast++;
	(*ast)->SetOriginalPosition(4700.0f, 534.0f);
	ast++;
	(*ast)->SetOriginalPosition(4750.0f, 566.0f);
	ast++;
	(*ast)->SetOriginalPosition(5000.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(5200.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(5500.0f, 500.0f);

	(*ast)->SetOriginalPosition(550.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(880.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(1100.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(1100.0f, 350.0f);
	ast++;
	(*ast)->SetOriginalPosition(1100.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(1650.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(1800.0f, 650.0f);
	ast++;
	(*ast)->SetOriginalPosition(1950.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(2350.0f, 570.0f);
	ast++;
	(*ast)->SetOriginalPosition(2550.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(2750.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(3050.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(3100.0f, 568.0f);
	ast++;
	(*ast)->SetOriginalPosition(3150.0f, 536.0f);
	ast++;
	(*ast)->SetOriginalPosition(3250.0f, 504.0f);
	ast++;
	(*ast)->SetOriginalPosition(3750.0f, 655.0f);
	ast++;
	(*ast)->SetOriginalPosition(3950.0f, 460.0f);
	ast++;
	(*ast)->SetOriginalPosition(4250.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(4550.0f, 520.0f);
	ast++;
	(*ast)->SetOriginalPosition(4650.0f, 552.0f);
	ast++;
	(*ast)->SetOriginalPosition(4750.0f, 584.0f);
	ast++;
	(*ast)->SetOriginalPosition(4800.0f, 616.0f);
	ast++;
	(*ast)->SetOriginalPosition(5050.0f, 650.0f);
	ast++;
	(*ast)->SetOriginalPosition(5250.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(5550.0f, 550.0f);
}

bool Game::OnStop()
{
	delete material;
	delete matTexture;
	delete player;
	delete asteroids;
	delete tilemap;

	return true;
}

bool Game::OnUpdate()
{
	switch (gameState)
	{
	case CONTINUE:
	{
		vec2 move = vec2(speed * Defs::getInstance()->deltaTime, 0.0f);		
		GetRenderer()->MoveCamera(glm::vec3(move.x, 0.0f, 0.0f));
		player->SetActualPosition(move.x, 0.0f);
		//b->Move();
		tilemap->Translate(glm::vec3(move.x, 0.0f, 0.0f));
		//tilemap->Move(move.x, 0.0f);
		
		player->Move();
		

		switch (player->GetHit())
		{
		case Win_Trigger:
		{
			gameState = WIN;
			cout << "You won this fantastic game! Good job!" << endl;
		}
			break;
		case Death_Trigger:
		{
			gameState = LOSE;
			player->Die();
		}
			break;
		}

		Entity* col = player->GetSprite()->OnCollisionEnter();
		if (col)
			if (col->GetTag() == Enemy)
			{
				gameState = LOSE;
				player->Die();
			}
		Entity* col2 = b->GetSprite()->OnCollisionEnter();
		if (col2)
			if (col2->GetTag() == Enemy)
			{			
				//printf("bullet hits enemy");				
				col2->Teleport(100.0f, 100.0f, 0.0f);
				b->Die();
			}		
	}
		break;
	case WIN:
	{

	}
		break;
	case LOSE:
	{
		if (player->GetSprite()->GetAnimation()->IsFinished())
			Restart();
	}
		break;
	}

	for (list<Asteroid*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Move();	
	tilemap->UpdateUV();
	player->Update();
	b->Update();

	for (list<Asteroid*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Update();

	if (gameState == 0)
		CollisionManager::getInstance()->DetectCollisions();

	input->PollEvents();

	return true;
}

bool Game::OnDraw()
{
	b->Draw();
	player->Draw();
	for (list<Asteroid*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Draw();

	tilemap->Draw();

	return true;
}

void Game::Restart()
{
	tilemap->Teleport(0.0f, 64.0f, 0.0f);
	GetRenderer()->ResetCamera(0.0f, 64.0f);
	player->ReturnToOriginalPosition();
	for (list<Asteroid*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->ReturnToOriginalPosition();

	gameState = CONTINUE;
}