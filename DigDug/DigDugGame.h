#pragma once
#include "Game.h"
#include  "MainScene.h"
#include "Locator.h"
#include "SceneManager.h"

class DigDugGame : public Game {

public:

	void LoadGame() override {

		MainScene* main = new MainScene{};

		SCENEMANAGER.AddScene(main);
		SCENEMANAGER.SetSceneActive("Main");
	}
};