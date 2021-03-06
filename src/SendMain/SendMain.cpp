#include <stdio.h>
#include "Display.h"
#include "Shader.h"
#include "Player.h"
#include "Background.h"
#include "EnemyManager.h"

#define NUM_ENEMIES 13

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

int main()
{
	/*
		DONE:
				-rotatie pe Z
				-(un fel de) health bar enemies
				-coliziuni de toate
				-health bar player
		TODO:
				-animatie nava
				-scor
				-miscare mai realista
				-proiectile adversari
				-(optional):
							- meniu
							- respawn adversari
							- parallax
							- upgraded sound and BGM
							- matrice ortografica si pentru camera
							- power-ups
							- AI avansat
		BUG:
				-Not yet
	*/

	Display* display = new Display(800, 600, "Joc");
	Shader* shader = new Shader("../data/Shader");
	EnemyManager* enemyManager = new EnemyManager(shader, NUM_ENEMIES);
	Player* player = new Player(display, shader, "../data/Textures/player.png", enemyManager);
	Background* background = new Background(shader, "../data/Textures/Background.png");

	while (display->IsRunning())
	{
		display->Clear();
		shader->Bind();

		background->Update();
		background->Draw();

		enemyManager->Update();
		enemyManager->Draw();

		player->Update();
		player->Draw();

		display->Update();
	}

	delete display;
	delete shader;
	delete player;
	delete background;
	delete enemyManager;

	_CrtDumpMemoryLeaks();
	return 0;
}

